luaval = {a=1,b=2,c=3,[0.2]=4,e=5}

function func(t)
	print(t.b)
	for k,v in pairs(t.a) do
		print(k,v)
	end

end