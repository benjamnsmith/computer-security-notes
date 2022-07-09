import requests

URL = "https://192.168.7.1/mac-cookie"

goal = "goal hash"

for i in range(256):
    base = "base username"
    user = base + chr(i)
    param = {'username':user}
    r = requests.get(url=URL, params=param,)
    if goal in r.text:
        print("success! next char:", chr(i))
        break