
# requests doesn't work
# from: https://blog.csdn.net/luanpeng825485697/article/details/78403943

import urllib
from bs4 import BeautifulSoup

# url and page numbers
URL = "https://www.qiushibaike.com/8hr/page/%d/"
PAGE_START = 1
PAGE_END = 10

QB_KV = {'user-agent': 'Mozilla/5.0 (Windows NT 6.3; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0'}

def parse_data(html):
    soup = BeautifulSoup(html, 'html.parser')
    cnts = soup.find_all("div", class_="content")
    votes = soup.find_all("span", class_="stats-vote")
    for i in range(0, len(cnts)):
        cnt = str.strip(cnts[i].span.contents[0])
        vote = int(votes[i].i.contents[0])
        print(cnt)
        print(vote)
        print('-----------------------------------------------------------------------------------------')

def go_craw(url):
    try:
        # create request and get response
        request = urllib.request.Request(url, headers=QB_KV)
        response = urllib.request.urlopen(request)    
        html = response.read().decode('utf-8')
        parse_data(html)
    except urllib.error.URLError as e:
        if hasattr(e,"code"):
            print(e.code)
        if hasattr(e,"reason"):
            print(e.reason)

if __name__ == "__main__":
    for i in range(PAGE_START, PAGE_END + 1):
        url = URL % i
        go_craw(url)
