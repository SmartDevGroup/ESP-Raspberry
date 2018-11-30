import json
with open('poll.json', 'r', encoding='utf-8') as fh:
    data = json.load(fh)
    print(json.dumps(data))

