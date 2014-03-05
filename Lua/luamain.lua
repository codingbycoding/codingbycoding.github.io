#!/usr/bin/lua
--like sh in linux environment 

print "HelloWorld"

luapage = [[
<html>
<head>
<title>
lua.org
</title>
</head>

<body>
<a href="http://www.lua.org">lua home page.</a>
</body>
</html>

]]

function fact(n)
   if n==0 then 
      return 1
   else
      return n*fact(n-1)
   end
end

--test comment for line


---[[
print("test comment for region") -- test comment for region
--]]

--[[
print("test comment for region") -- test comment for region
--]]

print("中文")
print("Enter a number:")
-- a=io.read("*number")
-- print(fact(a))


function testfunc()
   local a = 0
   
   return function()
      a = a+1 
      return a
   end
end

aa1 = testfunc()
aa2 = testfunc()
print(aa1())
print(aa1())
print(aa2())
print(aa1())
print(aa1)


function testfuncarg(...)
   -- print(debug.traceback())
   print(...)
end


testfuncarg("Hello", "Lua5.2")


testtab = {}
testtab.x = "abc"

for k,v in pairs(testtab)
do
   print(k,v)
-- print(k, v)
end


assert(true, "assert false.")

-- error("error message")

function receiver()
   local status, value = coroutine.resume(producer)
   return value
end

function send(x)
   print(x)
   coroutine.yield(x)
end

iii = 0
producer = coroutine.create(
   function()
      for i=1,5 do
	 local iiloc = iii+i
	 send(iiloc)
      end
   end
)



Persion = {id=16000, name="Jack", gender="Male", counter=0}

function Persion.init(self)
   print("call init") 
end

function Persion.construct(self)
   print("call consturct")
end


function Persion.destruct(self)
   print("call destruct")
end

function Persion.incCounter(self)
   print("call incCounter")
   self.counter = self.counter+1
end


function Persion:desCounter()
   print("call desCounter")
   self.counter = self.counter-1
end

function Persion.printCounter(self)
   print("call printCounter")
   print(self.counter)
end


function Persion.toString(self)
   print("call toString")
   for k,v in pairs(self) do
      print(k,v)
   end
end






receiver()
receiver()
receiver()
receiver()
receiver()
receiver()
receiver()

apersion = Persion
apersion.toString(apersion)
apersion:incCounter()

apersion:incCounter()
apersion:printCounter()

apersion:desCounter()
apersion:printCounter()



local stu = require "luamodule"

-- stu = luamodule.Student

stu:toString()


Rose = stu:new()
Rose.name = "Rose"
Rose:toString()


-- print(os.getenv(package.cpath))
-- package.cpath = package.cpath .. .
print(type(package.cpath))
print(package.cpath)

testlib = require("luaclibtest")
print(testlib.sin(20))
print(testlib.add(20, 30))
