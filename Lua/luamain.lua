--#!/usr/local/bin/lua --like sh in linux environment 

print "HelloWorld"


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
