import requests
from pwn import cyclic
for i in range(200):
    r = requests.post("http://localhost:6666", data=cyclic(6000))
# print(r.text)
