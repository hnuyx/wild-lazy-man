
import requests

from bs4 import BeautifulSoup

baseurl = "http://www.59xihuan.cn/"

kv = {'User-agent': 'Mozilla/5.0 (Windows NT 6.3; W…) Gecko/20100101 Firefox/60.0'}
#kv = {'user-agent': 'Mozilla/5.0 (Windows NT 6.3; W…) Gecko/20100101 Firefox/60.0',
      'cookie': 'SESSc60faee9ca2381b86f19bef961…7066299842; homere=2; xqrclm=',
      'accept': 'text/html,application/xhtml+xm…plication/xml;q=0.9,*/*;q=0.8',
      'accept-Encoding': 'gzip, deflate',
      'accept-language': 'en-US,en;q=0.8,zh-CN;q=0.5,zh;q=0.3',
      'connection': 'keep-alive',
      'host': 'www.juzimi.com'
     }


#fo = open('4-xljt.txt', 'a+')
fo = open('5-xljt.txt', 'a+')

try:
    for i in range(1, 101):
        #url = baseurl + 'index_' + str(i) +'.html'
        url = baseurl + 'jingdianyulu_11_' + str(i) +'.html'
        #print(url)
        #r = requests.get(url)
        r = requests.get(url, kv)
        #print(r.text)
        r.raise_for_status()
        #print(r.status_code)
        #r.encoding = r.apparent_encoding
        #print(r.text)
        demo = r.text
        soup = BeautifulSoup(demo, 'html.parser')
        #print(soup.prettify())
        msgs = soup.find_all('div', class_ = 'pic_text1')
        #print(msg)
        for msg in msgs:
            #print(msg.contents[0].strip())
            fo.write(msg.contents[0].strip())
            fo.write('\n')
except:
    print("failed")
    #print(r.status_code)

fo.close()
