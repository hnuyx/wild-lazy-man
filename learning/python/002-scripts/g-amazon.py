
import requests

url = "https://www.amazon.cn/gp/product/B06WWBG3JJ/ref=ox_sc_act_title_1?ie=UTF8&psc=1&smid=A2SRRU74VVEXPG"

kv = {'user-agent': 'Mozilla/5.0 (Windows NT 6.3; Win64; x64; rv:60.0) Gecko/20100101 Firefox/60.'}


try:
    r = requests.get(url)
    print(r.status_code)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    print(r.text)
except:
    print("failed")
    print(r.text)
