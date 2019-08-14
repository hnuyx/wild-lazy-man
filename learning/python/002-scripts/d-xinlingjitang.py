
import requests

url = "http://www.59xihuan.cn/"

kv = {'User-agent': 'Mozilla/5.0 (Windows NT 6.3; W…) Gecko/20100101 Firefox/60.0'}


try:
    #r = requests.get(url)
    r = requests.get(url, kv)
    #print(r.text)
    r.raise_for_status()
    print(r.status_code)
    #r.encoding = r.apparent_encoding
    #print(r.text)
except:
    print("failed")
    #print(r.status_code)
