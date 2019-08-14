
import requests

url = 'http://ip138.com/ips138.asp?ip='
#r = requests.get("http://www.baidu.com")

try:
    r = requests.get(url + '202.204.80.112')
    #print(r.status_code)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    print(r.text[:1000])
    print(r.text[1001:2000])
    print(r.text[2001:3000])
    print(r.text[3001:4000])
except:
    print("failed")
    #print(r.status_code)
