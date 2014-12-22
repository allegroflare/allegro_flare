#ifndef __AF_SCRIPTABLE_HEADER
#define __AF_SCRIPTABLE_HEADER



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>




template <class T>
class Scriptable
{
private:
	std::string scriptable_identifier;
	typedef void (T::*scriptable_func)(std::string arg);
	class lookup_row
	{
	public:
		std::string identifier;
		scriptable_func function;
		lookup_row(std::string identifier, scriptable_func function)
			: identifier(identifier)
			, function(function)
		{}
	};

	std::vector<lookup_row *> lookup_table;
	scriptable_func get_scriptable_func(std::string identifier)
	{
		for (unsigned i=0; i<lookup_table.size(); i++)
			if (lookup_table[i]->identifier == identifier) return lookup_table[i]->function;
		return NULL;
	}
	static int lookup_row_cmp(const void *row_a, const void *row_b)
	{
		return ((lookup_row *)row_a)->identifier.compare(((lookup_row *)row_b)->identifier);
	}
public:
	Scriptable(std::string scriptable_identifier)
		: scriptable_identifier(scriptable_identifier)
	{}
	void set_scriptable_identifier(std::string scriptable_identifier)
	{
		this->scriptable_identifier = scriptable_identifier;
	}
	const std::string &get_scriptable_identifier() { return scriptable_identifier; }
	void register_function(std::string identifier, scriptable_func function)
	{
		lookup_table.push_back(new lookup_row(identifier, function));
		//std::sort(lookup_table.begin(), lookup_table.end(), lookup_row_cmp);
	}
/*
	void call_scriptable_func(T *calling_object, std::string identifier, std::string args)
	{
		scriptable_func found_func = get_scriptable_func(identifier);
		if (found_func) (calling_object->*found_func)(args);
	}
*/
	bool call_scriptable_func(std::string identifier, std::string args)
	{
		T *calling_object = (T *)(this);
		scriptable_func found_func = get_scriptable_func(identifier);
		if (found_func) { (calling_object->*found_func)(args); return true; }
		return false;
	}
	void call_scriptable_command_function(std::string command)
		// has the following format command_identifier(argument_string)
	{
		std::string command_identifier = command;
		std::string command_args = "";

		std::size_t paren_start = command.find_first_of("(");
		std::size_t paren_end = command.find_last_of(")");

		if (paren_start != std::string::npos && paren_end != std::string::npos && paren_start < paren_end)
		{
			command_identifier = command.substr(0, paren_start);
			command_args = command.substr(paren_start+1, paren_end-paren_start-1);
		}

		std::cout << "call_scriptable_command_function:" << std::endl;
		std::cout << "  command_identifier: \"" << command_identifier << "\"" << std::endl;
		std::cout << "  command_args: \"" << command_args << "\"" << std::endl;

		if (!call_scriptable_func(command_identifier, command_args))
		{
			std::cout << "[Scriptable<?>::call_scriptable_command_function()] error, command \"" << command_identifier << "\" does not exist." << std::endl;
		}
	}
	//virtual void call_func(std::string funcname, std::string args) = 0;
};









/*
////////// EXAMPLE ////////////
////////// EXAMPLE ////////////



class MyScriptableThing : public Scriptable<MyScriptableThing>
{
public:
//	void call_func(std::string funcname, std::string args)
//	{
//		call_scriptable_func(this, funcname, args);
//	}

	void echo (std::string arg)
	{
		std::cout << arg << std::endl;
	}

	MyScriptableThing(std::string name)
		: Scriptable(name)
	{
		register_function("echo", &MyScriptableThing::echo);
	}
};




int main()
{
	MyScriptableThing f("yada");

	f.call_func("echo", "hello_world");

	int i;
	std::cin >> i;
}
*/



#endif