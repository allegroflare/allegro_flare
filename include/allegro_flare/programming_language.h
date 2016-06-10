#ifndef __AF_PROGRAMMING_LANGUAGE_HEADER
#define __AF_PROGRAMMING_LANGUAGE_HEADER




#include <iostream>
#include <string>
#include <vector>



class Function
{
public:
	std::string identifier;
	std::vector<std::string> args;
	std::string body;

	//Function
};


// a variable is also a function (without arguments)

// you could overload it with arguments if you wanted to


class Variable
{
public:
	std::string identifier;
	std::string value;
	std::string type;

	Variable(std::string identifier, std::string value, std::string type);
};





class VirtualMemory
{
private:
	Variable *get_record_by_identifier(std::string identifier) const;
	std::vector<Variable *> variable;

public:
	// get, set, and isset
	std::string get(std::string identifier) const;
	void set(std::string identifier, std::string value);
	bool isset(std::string identifier) const;

	std::string get_type(std::string identifier) const;
	void set_type(std::string identifier, std::string type);
	bool has_type(std::string identifier);

	// get the variable casted as a specific type
	int get_as_int(std::string identifier) const;
	float get_as_float(std::string identifier) const;
	std::string get_as_string(std::string identifier) const;

	// output to console
	void dump();
};





class InterpreterInterface
{
public:
	VirtualMemory memory;
	virtual void interpret(std::string val) = 0;
};





#endif
