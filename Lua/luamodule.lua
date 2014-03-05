Student = {id=16000, name="Jack", age="19", gender="Male"}

--M1 = Student


function Student:new(o)
   o = o or {}
   setmetatable(o, self)
   self.__index=self
   return o
end



function Student:print()
end 


function Student:toString()
   for k,v in pairs(self) do
      if(type(v) ~= "function") then
	 print(k .. ": " .. v)
      end
   end
end


return Student
-- return M1
