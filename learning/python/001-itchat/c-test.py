import requests

apiUrl = 'http://www.tuling123.com/openapi/api'

data = {
    #'key'    : '8edce3ce905a4c1dbb965e6b35c3834d',
    #'key'    : 'eb720a8970964f3f855d863d24406576',
    #'key'    : '1107d5601866433dba9599fac1bc0083',
    'key'    : '71f28bf79c820df10d39b4074345ef8c',
    'info'   : 'hello',
    'userid' : 'wechat-robot'
    }

r = requests.post(apiUrl, data).json()

print(r)

