
print(b)

b = 10
print(b)

b = nil
print(b)
print("------------------------------------------------------")

print(type(b))

print("------------------------------------------------------")
tab1 = {key1 = "val1", key2 = "val2", "val3"}
for k,v in pairs(tab1) do
    print(k .."-".. v)
end

print("------------------------------------------------------")
tab1.key1 = nil
for k,v in pairs(tab1) do
    print(k .."-".. v)
end

print("------------------------------------------------------")
print(type(x))
print((type(x)==nil))
print((type(x)=="nil"))

print("------------------------------------------------------")
print(type(true))
print(type(false))
print(type(nil))

if false or nil then
    print("at least one is true")
else
    print("both false and nil are is false")
end

print("------------------------------------------------------")
print(type(2))
print(type(2.2))
print(type(0.2))
print(type(2e+1))
print(type(0.2e-1))
print(type(7.8263692594256e-06))

print("------------------------------------------------------")
string1 = "this is string1"
string2 = "this is string2"
html = [[
<html>
<head></head>
<body>
  <a href="http://www.runoob.com/">learning lesson</a>
</body>
</html>
]]

print(string1)
print(string2)
print(html)


print("------------------------------------------------------")
print("2" + 6)
print("2" + "6")
print("2 + 6")
print("-2e2" * "6")
--print("error" + 1)

print("------------------------------------------------------")
print("a" .. "b")
print(157 .. 428)

print("------------------------------------------------------")
len = "www.runoob.com"
print(#len)
print(#"www.runoob.com")

print("------------------------------------------------------")
local tab1 = {}
local tab2 = {"apple", "pear", "orange", "grape"}

for k,v in pairs(tab2) do
    print (k .. "-" .. v)
end

print("------------------------------------------------------")
tab3 = {}
tab3["key"] = "value"
key = 10
tab3[key] = 22
tab3[key] = tab3[key] + 11
for k,v in pairs(tab3) do
    print (k .. "-" .. v)
end

print("------------------------------------------------------")
tab4 = {}
for i = 1,10 do
    tab4[i] = i
end

tab4["key"] = "val"
print(tab4["key"])
print(tab4["none"])


print("------------------------------------------------------")
function factorial(n)
    if n == 0 then
        return 1
    else
        return n * factorial(n - 1)
    end
end

print(factorial(5))
factorial2 = factorial
print(factorial2(5))

print("------------------------------------------------------")

function testfun(tab, fun)
    for k,v in pairs(tab) do
        print(fun(k, v))
    end
end

tab = {key1 = "val1", key2 = "val2"}
testfun(tab,
    function (key, val)
        return (key .. "=" .. val)
    end
)

print("------------------------------------------------------")

a = 5
local b = 5

function joke()
    c = 5
    local d = 6
end

joke()
print(c, d)

do
    local a = 6
    b = 6
    print (a, b)
end
print (a, b)


print("------------------------------------------------------")
a = "hello" .. "world"
--t.n = t.n+1
print(a)

x = 10
a, b = 10, 2*x
print (a, b)
a, b = b, a
print (a, b)

print("------------------------------------------------------")
-- while, for, repeat...until,
-- if then ... end, if then ... else ... end

a = 10
while (a < 20) do
    print("a's vlaue is: ", a)
    a = a + 1
end

for i = 10,1,-1 do
    print (i)
end

function f(x)
    print("function f(x)");
    return x*2
end
for i = 1,f(5) do
    print(i)
end

days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
for i,v in ipairs(days) do
    print(v)
end

a = 10
repeat
    print(a)
    a = a +1
until(a > 15)

j = 2
for i = 2,10 do
    for j = 2, (i/j), 2 do
        if (not (i%j)) then
            break
        end
        if (j > (i/j)) then
            print("i is ", i)
        end
    end
end

a = 10
if (a < 20) then
    print("a less than 20")
end
print("a is ", a)

a = 100
if (a < 20) then
    print ("a less than 20")
else
    print ("a bigger than 20")
end
print ("a is ", a)

a = 100
if (a == 10) then
    print ("a is 10")
elseif (a == 20) then
    print ("a is 20")
elseif (a == 30) then
    print ("a is 30")
else
    print ("no matched a")
end
print ("a is ", a)

a = 100
b = 200
if (a == 100) then
    if (b == 200) then
        print ("a is 100 and b is 200")
    end
end
print ("a is ", a)
print ("b is ", b)

print("------------------------------------------------------")
function max(n1, n2)
    if (n1 > n2) then
        return n1
    else
        return n2
    end
end
print(max(10, 4))
print(max(5, 4))

myprint = function(p)
    print("param is ", p)
end

function add (n1, n2, fun)
    fun(n1 + n2)
end

myprint(10)
add(1, 2, myprint)

s, e = string.find("www.runoob.com", "runoob")
print(s, e)

function maximum(a)
    local mi = 1
    local m = a[mi]
    for i, v in ipairs(a) do
        if (v > m) then
            mi = i
            m = v
        end
    end
    return mi, m
end

print(maximum({8, 10, 24, 12, 5, 30}))

function adds(...)
    local s = 0
    for i, v in ipairs{...} do
        s = s + v
    end
    return s
end
print(adds(3,4,5,6,7))

function average(...)
    local s = 0
    local arg = {...}
    for i,v in ipairs(arg) do
        s = s + v
    end
    return (s/#arg)
end
print (average(10, 5, 3, 4, 5, 6))

function average2(...)
    local s = 0
    local arg = {...}
    for i,v in ipairs(arg) do
        s = s + v
    end
    return (s/select("#", ...))
end
print (average2(10, 5, 3, 4, 5, 6))

function fwrite(fmt, ...)
    return io.write(string.format(fmt, ...))
end

fwrite("runoob\n")
fwrite("%d%d\n", 1, 2)

do
    function foo(...)
        for i = 1, select("#", ...) do
            local arg = select(i, ...)
            print("arg", arg)
        end
    end

    foo(1, 2, 3, 4)
end

print("------------------------------------------------------")

print("------------------------------------------------------")
print("------------------------------------------------------")


