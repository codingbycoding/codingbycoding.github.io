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


print("Enter a number:")
a=io.read("*number")
print(fact(a))
