#!/usr/bin/env python

import requests

# install requests
# pip install requests

r = requests.get("https://www.baidu.com")

print r.encoding
print r.text
print r.apparent_encoding
print "response type: ", type(r)
print "response status: ", r.status_code

r.encoding = 'utf-8'

print r.text
print "\n"
print r.encoding
print "\n"
print r.apparent_encoding
print "\n"
print r.content
