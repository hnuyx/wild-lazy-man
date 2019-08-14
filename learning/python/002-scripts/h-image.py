
import requests
import os

#url = "https://farm5.staticflickr.com/4259/35163667010_8bfcaef274_k_d.jpg"
url = "http://img05.tooopen.com/images/20150531/tooopen_sy_127445886487.jpg"
img_dir= "./imgs/"
img_path = img_dir + url.split('/')[-1]



try:
    if not os.path.exists(img_dir):
        os.mkdir(img_dir)
    if not os.path.exists(img_path):
        r = requests.get(url)
        with open(img_path, 'wb') as f:
            f.write(r.content)
            f.close()
            print("image is saved successfully")
    else:
        print("file already exists")
except:
    print("failed")
