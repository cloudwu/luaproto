local proto = require "proto"


function foo()
	print "Hello"
	return "world"
end


local p,subp,k = proto.proto(foo)

for i=1,k do
	print(i, proto.constant(p, i))
end

