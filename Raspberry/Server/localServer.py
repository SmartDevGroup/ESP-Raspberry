import json
import requests
import time
import threading
# import os
# import main.py as server


def thread(my_func):
    def wrapper(*args, **kwargs):
        my_thread = threading.Thread(target=my_func, args=args, kwargs=kwargs)
        my_thread.start()
    return wrapper


def load_json(query):
    if query == "setting":
        with open('setting.json', 'r', encoding='utf-8') as fh:
            data = json.load(fh)
    elif query == "poll":
        with open('poll.json', 'r', encoding='utf-8') as fh:
            data = json.load(fh)
    elif query == "data":
        with open('data.json', 'r', encoding='utf-8') as fh:
            data = json.load(fh)
    return data


# ----------- load parametres
setting = load_json("setting")
# ----------- end load parametres


def write_json(data, query):
    if query == "setting":
        with open('setting.json', 'w', encoding='utf-8') as fh:
            json.dump(data, fh, indent=3)
    if query == "poll":
        with open('poll.json', 'w', encoding='utf-8') as fh:
            json.dump(data, fh, indent=3)
    if query == "data":
        with open('data.json', 'w', encoding='utf-8') as fh:
            json.dump(data, fh, indent=3)


@thread
def internet():
    print("start thread internet")
    global internet_status
    while True:
        try:
            requests.get(
                setting["domain"], timeout=1)
            internet_status = True
        except requests.exceptions.RequestException:
            internet_status = False
        time.sleep(5)
    print("close thread")


@thread
def pool_sensors():
    print("start thread polling")
    timer = time.time()
    while True:
        t = time.time()
        if(t - timer >= 2.0):
            timer = t
            print("polling sensors")
            data_devices = load_json("data")
            data = {"user": setting["accId"]}
            for key in data_devices.keys():
                try:
                    reqToESP = requests.get("http://" +
                                            data_devices[key]["ip"] +
                                            setting["urlToSensors"],
                                            timeout=1).text
                    data.update(
                        {str(key): {"temp": reqToESP, "connection": 1}})
                except requests.exceptions.RequestException:
                    pass
                    data.update(
                        {str(key): {"temp": "null", "connection": "null"}})
                    print("error connection from ", data_devices[key]["id"])
            write_json(data, "poll")


@thread
def send_temp():
    print("start thread sending to server")
    timer = time.time()
    while True:
        t = time.time()
        if(t - timer >= 5.0):
            timer = t
            print("normal send data of sensors to server")
            data = load_json("poll")
            data = json.dumps(data)
            print(data)
            try:
                reqToServer = requests.post(setting["domain"] +
                                            setting["urlToSendTemp"],
                                            data)
            except requests.exceptions.RequestException:
                print("error to send data of sensors to server")
            print(reqToServer)


# ----------------- loop ---------------------------

internet()
time.sleep(1)


while setting["first_connection"] == "True":
    print("in while")

    url = setting["domain"] + \
        setting["urlFirstConnection"] + setting["serial"]
    data = requests.get(url).text
    print("data is :")
    print(data)
    if(data == ""):
        time.sleep(1)
        data = requests.get(url).text
        print("data is :")
        print(data + "--")
    if(data == "repeat"):
        print("data = 'repeat'")
        while data == "repeat":
            print("data = 'repeat in loop'")
            data = requests.get(url).text
            time.sleep(3)
        setting.update({"accId": data, "first_connection": "False"})
        write_json(setting, "setting")
        print(setting["accId"])

global internet_status

if internet_status and setting["accId"] != "NULL":
    pool_sensors()
    send_temp()
    data_old = requests.get(
        setting["domain"] + setting["urlToData"] + setting["accId"] +
        setting["urlToDataOld"]).json()
    write_json(data_old, "data")
    print(data_old)


while True:
    print("internet_status is", internet_status)

    if internet_status and setting["accId"] != "NULL":
        try:
            data = requests.get(setting["domain"] +
                                setting["urlToData"] +
                                setting["accId"], timeout=40).json()
            for key in data.keys():
                if data[key]["value"] != data_old[key]["value"]:
                    data_old[key].update({'value': data[key]["value"]})
                    url = "http://"
                    url += data[key]["ip"]
                    url += "/LED?status="
                    url += data[key]["value"]
                    try:
                        reqToESP = requests.get(url)
                    except requests.exceptions.RequestException:
                        print("error to send request to esp")
                    print(url)
                    print(data[key]["name"])

        except requests.exceptions.RequestException:
            data = "time out"
            print("time out or ather error")
        print(data)
        time.sleep(1)
    else:
        print("you have not connection to server")
        # p = server.runserver()
        time.sleep(5)
        # os.kill(p.pid)
