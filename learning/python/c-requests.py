#!/usr/bin/env python

import requests

def getHtmlText(url):
    try:
        r = requests.get(url, timeout=30);
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return "exception happens"

if __name__ == "__main__":
    url = "https://www.baidu.com"
    print (getHtmlText(url))
    url = "http://www.baidu.com"
    print (getHtmlText(url))
    url = "www.baidu.com"
    print (getHtmlText(url))
