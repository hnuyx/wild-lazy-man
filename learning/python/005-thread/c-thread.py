
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

threads = []
t1 = threading.Thread(target=music, args=(u'爱情买卖',))
threads.append(t1)
t2 = threading.Thread(target=movie, args=(u'阿凡达',))
threads.append(t2)

if __name__ == '__main__':
    for t in threads:
        t.setDaemon(True)
        t.start()

    t.join()
    print("all over " + ctime())
