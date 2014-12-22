



#include <allegro_flare/interprocess.h>









void InterprocessSender::timer_func()
{
	if (!commands.empty() && SharedMemory::is_empty())
	{
		// the buffer is empty and there are some commands to be written
		write(commands.front());
		commands.erase(commands.begin());
	}
}




InterprocessSender::InterprocessSender(std::string memory_location_identifier, int size_in_bytes)
	: Screen(NULL)
	, SharedMemory(memory_location_identifier, size_in_bytes, true)
	, memory_location_identifier(memory_location_identifier)
	, timer(NULL)
	, commands()
{
	timer = al_create_timer(ALLEGRO_BPS_TO_SECS(240));
	al_register_event_source(af::event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
}




InterprocessSender::~InterprocessSender()
{
	//destroy_command_event_source(command_event_source);
	al_unregister_event_source(af::event_queue, al_get_timer_event_source(timer));
	al_destroy_timer(timer);
}




void InterprocessSender::push_command(std::string command)
{
	commands.push_back(command);
}
















InterprocessRecipient::InterprocessRecipient(std::string memory_location_identifier, int size_in_bytes, int num_refreshes_per_sec)
	: Screen(NULL)
	, memory_location_identifier(memory_location_identifier)
	, SharedMemory(memory_location_identifier, size_in_bytes, true)
	, empty_string(size_in_bytes, SharedMemory::get_empty_char())
	, content_last_check(empty_string)
	, content_now(empty_string)
{
	timer = al_create_timer(ALLEGRO_BPS_TO_SECS(num_refreshes_per_sec));
	al_register_event_source(af::event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
}




InterprocessRecipient::~InterprocessRecipient()
{
	al_unregister_event_source(af::event_queue, al_get_timer_event_source(timer));
	al_destroy_timer(timer);
}




void InterprocessRecipient::timer_func()
{
	content_now = read();
	if (content_now != empty_string)
	{
		clear();
		//content_last_check = empty_string;
		on_command(content_now);
	}
}




void InterprocessRecipient::on_command(std::string command)
{
	std::cout << "mem change" << std::endl;
	std::cout << "   " << php::trim(command) << std::endl;
	// You have recieved a command!
	// now you could...
		// dispatch a user_event
		// send out a Screen::send_signal();
		// something else, I dunno, call some functions directly
}



