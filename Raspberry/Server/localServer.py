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
    if query == "":
        pass
    return data


def write_json(data, query):
    if query == "setting":
        with open('setting.json', 'w', encoding='utf-8') as fh:
            json.dump(data, fh, indent=3)
    if query == "":
        pass
    return data


@thread
def internet():

    global internet_status
    while True:
        try:
            requests.get(
                'http://smartdevgroup.hopto.org', timeout=1)
            internet_status = True
        except requests.exceptions.RequestException:
            internet_status = False
        time.sleep(5)
    print("close thread")


# ----------------- loop ---------------------------
setting = load_json("setting")
internet()
time.sleep(2)

while setting["first_connection"] == "True":
    print("in while")

    url = setting["domain"] + \
        setting["urlFirstConnection"] + setting["serial"]
    data = requests.get(url).text
    print("data is :")
    print(data)
    if(data == ""):
        print("data = ' '")
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
    data_old = requests.get(
        setting["domain"] + setting["urlToData"] + setting["accId"] +
        setting["urlToDataOld"]).json()
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
                    # reqToESP = requests.get(url)
                    print(url)

        except requests.exceptions.RequestException:
            data = "time out"
            print("time out or ather error")
        # print(data)
        time.sleep(1)
    else:
        print("you have not connection to server")
        # p = server.runserver()
        time.sleep(5)
        # os.kill(p.pid)
