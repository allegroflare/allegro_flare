#ifndef __AF_INTERPROCESS_HEADER
#define __AF_INTERPROCESS_HEADER







#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/shared_memory.h>




class InterprocessSender : public Screen, public SharedMemory
{
	// note: this Screen does not use a display, it only inherets the timer_func()
private:
	ALLEGRO_TIMER *timer;
	std::string memory_location_identifier;
	std::vector<std::string> commands;

	void timer_func() override;
public:
	InterprocessSender(std::string memory_location_identifier="my_shared_memory", int size_in_bytes=512);
	~InterprocessSender();
	void push_command(std::string command);
};




class InterprocessRecipient : public Screen, public SharedMemory
{
	// checks the shared memory location for changes in the memory at a frequncy of 240 checks/sec
	// if a new string is there, it grabs it as a string, clears the shared memory space, then
	// the user can process the command through on_command();
private:
	ALLEGRO_TIMER *timer;
	std::string memory_location_identifier;

	std::string empty_string;
	std::string content_now;
	std::string content_last_check;

public:
	InterprocessRecipient(std::string memory_location_identifier="my_shared_memory", int size_in_bytes=512, int num_refreshes_per_sec=30);
	~InterprocessRecipient();
	void timer_func() override;
	virtual void on_command(std::string command);
};






#endif