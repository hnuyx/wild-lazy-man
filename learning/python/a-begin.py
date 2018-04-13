#!/usr/bin/env python

import getpass

# input username
username = raw_input("Please input your user name: ")
#print "Your user name is", username

# input password
password = getpass.getpass("Please input your password: ");
#print "Your password is", password

# judge if user is henry
if username == "henry" and password == "henry":
    print "Welcome, henry!"
else:
    print "You are not henry!"

# judge user type
if username == "henry":
    print "Hi Super Administrator"
elif username == "heart":
    print "Hi Administartor"
elif username == "hot" or username == "hard":
    print "Hi Director"
else:
    print "Hi", username

# break and continue
while True:
    print "True 123"
    break
    print "True 456"

# print 1 2 3 4 5 6  8 9 10
n = 1
while n < 11:
    if n == 7:
        pass
    else:
        print n
    n = n + 1
print "-------------------"

# compute sum of 1-100
n = 1
ret = 0
while n < 101:
    ret = ret + n
    n = n + 1
print "sum is", ret

# compute sum of all odd in 1-100
n = 1
ret = 0
while n < 101:
    tmp = n % 2
    if tmp == 0:
        pass
    else:
        ret = ret + n
    n = n + 1
print "odd sum", ret

# compute sum of all even in 1-100
n = 1
ret = 0
while n < 101:
    tmp = n % 2
    if tmp == 0:
        ret = ret + n
    else:
        pass
    n = n + 1
print "even sum", ret

# user login limit is 3 times
count = 0
while count < 3:
    user = raw_input('Please input username: ')
    pwd  = getpass.getpass('Please input password: ')
    if user == "henry" and pwd == "henry":
        print "Welcome henry"
        print "-------------"
        break
    else:
        print "user or pwd is error"
    count =  count + 1

#-------------------------EDN OF FILE-------------------------------------
