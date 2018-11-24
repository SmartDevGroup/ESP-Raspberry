from bottle import run, template, route, static_file, request, response

import json


def load_json():
    with open('data.json', 'r') as fh:
        data = json.load(fh)
    return data


def write_json(data):
    with open('data.json', 'w', encoding='utf-8') as fh:
        json.dump(data, fh, indent=3)
    return data


data_param = load_json()


@route('/static/<filename:re:.*\.css>')
def send_css(filename):
    return static_file(filename, root='./static/asset/css')


@route('/static/<filename:re:.*\.js>')
def send_js(filename):
    return static_file(filename, root='./static/asset/js')


@route('/get_json')
def get_json():
    data = load_json()
    return data


@route('/')
def index():
    data = load_json()
    response.headers['Access-Control-Allow-Origin'] = '*'
    return template('index_main', data=data)


@route('/chek_box_ajax', method="GET")
def chek_box_ajax():
    global data_param
    id = request.query.obj_id
    status = request.query.obj_status
    json_data = load_json()
    global key
    for n in json_data:
        if json_data[n]["id"] == id:
            key = n
    if status == 'Enable':
        json_data[key]['value'] = 'Enable'
        data_param[key].update({'value': 'Enable'})
    else:
        json_data[key]['value'] = 'Disable'
        data_param[key].update({'value': 'Disable'})
    write_json(json_data)
    return json_data[key]['value']


def runserver():
    run(host="192.168.184.103", port=80, debug=True)


runserver()
