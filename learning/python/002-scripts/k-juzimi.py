
import requests

from bs4 import BeautifulSoup
import demjson

#baseurl = "http://www.juzimi.com/writer/鲁迅?page="
baseurl = "http://www.juzimi.com/writer/鲁迅"

kv = {'accept': 'text/html,application/xhtml+xm…plication/xml;q=0.9,*/*;q=0.8',
      'accept-encoding': 'gzip, deflate',
      'accept-language': 'en-US,en;q=0.8,zh-CN;q=0.5,zh;q=0.3',
      'connection': 'keep-alive',
      #'cookie': 'SESSc60faee9ca2381b86f19bef9617d499b=ftnln9stlrgpvsambhrd6osan4; has_js=1; __cfduid=da695a64e1aa5a4d6fefc1a91466f5d041527066294; xqrclbr=57589; xqrcli=MTUyNzA3MDQzNCwxNjAwKjkwMCxXaW42NCxOZXRzY2FwZSw1NzU4OSw%3D; visited=1; Hm_lvt_0684e5255bde597704c827d5819167ba=1527066296; Hm_lpvt_0684e5255bde597704c827d5819167ba=1527070435; Hm_cv_0684e5255bde597704c827d5819167ba=1*login*PC-0!1*version*PC; bdshare_firstime=1527066299842; homere=2; xqrclm=*319*',
      'host': 'www.juzimi.com',
      'referer': 'http://www.juzimi.com/writer/%E9%B2%81%E8%BF%85',
      #'if-modified-since': 'Wed, 23 May 2018 10:00:30 GMT',
      #'if-none-match': '814b2a6b0f4584688e5483233950ca4c',
      #'upgrade-insecure-requests': '1',
      'user-agent': 'Mozilla/5.0 (Windows NT 6.3; W…) Gecko/20100101 Firefox/60.0'
     }


fo = open('6-xljt.txt', 'a+')

try:
    for i in range(1, 131):
        #url = baseurl + 'index_' + str(i) +'.html'
        #url = baseurl + str(i)
        url = baseurl
        print(url)
        #r = requests.get(url)
        r = requests.get(url, params = kv)
        print(r.status_code)
        #print(r.text)
        r.raise_for_status()
        #r.encoding = r.apparent_encoding
        #print(r.text)
        demo = r.text
        soup = BeautifulSoup(demo, 'html.parser')
        #print(soup.prettify())
        msgs = soup.find_all('div', class_ = 'bdshare_t bds_tools get-codes-bdshare')
        #print(msg)
        for msg in msgs:
            #print(msg.contents[0].strip())
            jd = msg.attrs['data']
            js = demjson.decode(jd)
            fo.write(js['text'])
            fo.write('\n')
except:
    print("failed")
    #print(r.status_code)

fo.close()
