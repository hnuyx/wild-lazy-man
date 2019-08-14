
#coding=utf-8

import threading
from time import ctime, sleep

def music(name):
    for i in range(10):
        print("I was listening to " + name, ctime() )
        sleep(1)

def movie(name):
    for i in range(10):
        print("I was watching " + name, ctime())
        sleep(1)

def player(name):
    r = name.split('.')[1]
    if r == 'mp3':
        music(name)
    else:
        if r == 'mp4':
            movie(name)
        else:
            print("error: the format is not recognized!")

list = ['爱情买卖.mp3', '阿凡达.mp4']
threads = []
files = range(len(list))

for i in files:
    t = threading.Thread(target=player, args=(list[i],))
    threads.append(t)


if __name__ == '__main__':
    for i in files:
        threads[i].start()
    for i in files:
        threads[i].join()

    print("all over " + ctime())
