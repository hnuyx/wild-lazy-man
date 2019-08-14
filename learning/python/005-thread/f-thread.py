
#coding=utf-8

from time import sleep, ctime
import threading

class MyThread(threading.Thread):

    def __init__(self, func, args, name=''):
        threading.Thread.__init__(self)
        self.name = name
        self.func = func
        self.args = args

    def run(self):
        self.func(*self.args)

def super_play(file, interval):
    for i in range(10):
        print("Start playing: " + file, ctime())
        sleep(interval)

list = {'爱情买卖.mp3':3, '阿凡达.mp4':5, '我和你.mp3':4}

threads = []
files = range(len(list))

for k,v in list.items():
    t = MyThread(super_play, (k, v), super_play.__name__)
    threads.append(t)

if __name__ == '__main__':
    for i in files:
        threads[i].start()
    for i in files:
        threads[i].join()

    print("end: " + ctime())

