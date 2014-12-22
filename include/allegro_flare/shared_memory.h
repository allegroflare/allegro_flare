#ifndef __AF_SHARED_MEMORY_HEADER
#define __AF_SHARED_MEMORY_HEADER




#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>


class SharedMemory
{
private:
	std::string identifier;
	int size;
	boost::interprocess::shared_memory_object *shared_memory_object;
	boost::interprocess::mapped_region *mapped_region;
	char empty_char;

public:
	SharedMemory(std::string identifier, int size, bool clear_on_launch=true);
	~SharedMemory();
	bool is_empty();
	void clear();
	void write(std::string message);
	bool write_if_empty(std::string message);
	std::string read();

	char get_empty_char();
};




/*
int main(int argv, char *argc[])
{
	SharedMemoryObject shared_memory_object("shared_message_memory", 256);
}
*/



#endif