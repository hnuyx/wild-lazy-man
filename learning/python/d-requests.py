#!/usr/bin/env python

import requests

# get, head, post, put, patch, delete
# post: append new data
# put: override  old info
# patch: update  part info
# delete:

r = requests.head("http://httpbin.org/get")

print r.headers
print "-------------------------------"
print r.text
print "-------------------------------"

payload = {'key1':'value1', 'key2':'value2'}
r = requests.post("http://httpbin.org/post", data = payload)
print r.text
print "-------------------------------"

r =  requests.post("http://httpbin.org/post", data = 'ABC')
print r.text
print "-------------------------------"

payload = {'key1':'value1', 'key2':'value2'}
r = requests.put("http://httpbin.org/put", data = payload)
print r.text
print "-------------------------------"

# requests.request(method, url, **kwargs)
# method:  'GET', 'HEAD', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'
# **kwargs:
#           params:
#           data:
#           json:
#           headers:
#           cookies:
#           auth:
#           files:
#           timeout:
#           proxies:
#           allow_redirects:
#           stream:
#           verify:
#           cert:
kv = {'key1':'value1', 'key2':'value2'}
r = requests.request('GET', "http://python123.io/ws", params = kv)
print r.url
print "-------------------------------"

kv = {'key1':'value1', 'key2':'value2'}
r = requests.request('POST', "http://python123.io/ws", data = kv)
print r.url
print "-------------------------------"
body = "main data"
r = requests.request('POST', "http://python123.io/ws", data=body)
print r.url
print "-------------------------------"
kv = {'key1':'value1', 'key2':'value2'}
r = requests.request('POST', "http://python123.io/ws", json = kv)
print r.url
print "-------------------------------"

hd = {'user-agent': 'Chrome/10'}
r = requests.request('POST', 'http://python123.io/ws', headers=hd)
print r.url
print "-------------------------------"

fs = {'file': open('data.xls', 'rb')}
r = requests.request('POST', 'http://python123.io/ws', files=fs)
print r.url
print "-------------------------------"
r = requests.request('GET', 'http://www.baidu.com', timeout=10)
print r.url
print "-------------------------------"

pxs = {'http': 'http://user:pass@10.10.10.1:1234',
        'http': 'https://10.10.10.1:4321'}
#r = requests.request('GET', 'http://www.baidu.com', proxies=pxs)
#print r.url
print "-------------------------------"

# requests.get(url, params=None, **kwargs)
# requests.head(url, **kwargs)
# requests.post(url, data=None, params=None, **kwargs)
# requests.put(url, data=None, **kwargs)
# requests.patch(url, data=None, **kwargs)
# requests.delete(url, **kwargs)

'''
try:
    r = requests.get(url, timeout=30)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    return r.text
except:
    return "exception happens"
'''









