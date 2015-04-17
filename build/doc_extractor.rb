





class CodeDef
	attr_reader :line_number, :section, :declaration, :description, :func_name

	def initialize(line_number, section, declaration, description)
		@line_number = line_number
		@section = section
		@declaration = declaration
		function_name_reg = / (?<func_identifier>.*)\(/
		declaration.scan(function_name_reg) { |val| puts val }
		@description = description
	end
end




class DocParser
	attr_reader :function_defs, :section_names

	def initialize
		@filename = filename = '../include/allegro_flare/useful_.h'
		@function_defs = Array.new
		parse_contents
	end


	def parse_contents
		# myregex = /\n(?<name>(\n\/\/ (.+))+)(?<funcs>(\n.+)+)/
		myregex = /\n(?<name>(\n\/\/ (.+))+)(?<function_def>(\n.+)+)/

		str = File.read(@filename)

		str.scan(myregex) do |a, b|
			@function_defs.push(CodeDef.new(0, '--', b, a))
		end
	end


	def write_html

		content = String.new
		content += "<DOCTYPE html>\n<head>\n<link rel='stylesheet' href='docstyle.css'/></head>\n<body>\n\n"
		content += "<H1>AllegroFlare Documentation</H1>\n";

		@function_defs.each do |fdef|
			content += "<h3>#{fdef.func_name}</h3>\n"
			content += "<code><pre>#{fdef.declaration}</pre></code>\n"
			content += "<p>#{fdef.description}</p>\n"
		end

		content += "\n\n</body>\n"
		File.write('./usefuldoc.html', content)

	end
end



doc_parser = DocParser.new
#puts doc_parser.function_defs.inspect
doc_parser.write_html




