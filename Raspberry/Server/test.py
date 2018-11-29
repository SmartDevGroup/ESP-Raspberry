import json
with open('poll.json', 'r', encoding='utf-8') as fh:
    data = json.load(fh)
    print(data['1'])
    print(data['1']['temp'])

