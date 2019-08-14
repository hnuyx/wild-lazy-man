
#coding=utf-8

from time import sleep, ctime
import threading


def super_player(file, interval):
    for i in range(10):
        print("Start playing: " + file, ctime())
        sleep(interval)

list = {'爱情买卖.mp3':3, '阿凡达.mp4':5, "我和你.mp3":4}

threads = []
files = range(len(list))

for file, interval in list.items():
    t = threading.Thread(target=super_player, args=(file, interval))
    threads.append(t)

if __name__ == '__main__':
    for i in files:
        threads[i].start()
    for i in files:
        threads[i].join()

    print("end: " + ctime())

