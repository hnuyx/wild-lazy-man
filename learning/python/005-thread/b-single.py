
#coding=utf-8

from time import ctime, sleep

def music(name):
    for i in range(2):
        print("I was listening to " + name, ctime() )
        sleep(1)

def movie(name):
    for i in range(2):
        print("I was watching " + name, ctime())
        sleep(5)

if __name__ == '__main__':
    music(u'爱情买卖')
    movie(u'阿凡达')

    print("all over " + ctime())
