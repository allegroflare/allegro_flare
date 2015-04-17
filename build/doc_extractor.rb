


myregex = /\n(?<name>(\n\/\/ (.+))+)(?<funcs>(\n.+)+)/

str = File.read('../include/allegro_flare/useful_.h')

match = str.scan(myregex)

match.each do |a, b|
	# a are the comments
	# b are the function(s)
	# TODO: output the data in a nice HTML format
end


