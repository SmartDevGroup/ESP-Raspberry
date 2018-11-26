import requests

r = requests.post("http://smartdevgroup.hopto.org/service/raspi_send.php",
                  data={'user': 123456789, 'temp': 12})
print("send post")
print(r)
