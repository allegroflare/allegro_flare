


#include <allegro_flare/screens/interprocess_through_files_screen.h>





InterprocessThroughFilesScreen::InterprocessThroughFilesScreen(std::string full_path, bool ignore_all_on_load)
	: InterprocessThroughFiles(full_path)
	, Screen()
	, check_frequency(0)
	, last_check_time(0)
	, active(true)
	, timeout_clear_time(5)
	, first_time_launch(true)
	, ignore_all_on_load(ignore_all_on_load)
{
	set_log_output(&std::cout);
}





void InterprocessThroughFilesScreen::set_check_frequency(float frequency_in_sec)
{
	check_frequency = frequency_in_sec;
}




void InterprocessThroughFilesScreen::primary_timer_func()
{
	if (!active) return;
	if (last_check_time + check_frequency < af::time_now)
	{
		check_for_interprocess_instructions();
		last_check_time = af::time_now;
		first_time_launch = false;
	}

	delete_interprocess_files_aged(timeout_clear_time);
}





void InterprocessThroughFilesScreen::halt()
{
	active = false;
}



void InterprocessThroughFilesScreen::resume()
{
	active = true;
}




void InterprocessThroughFilesScreen::process_interprocess_instruction(std::string &filename)
{
	std::string instructions = php::file_get_contents(filename);
	std::cout << std::endl << "processing < " << filename << std::endl;

	std::string instruction;
	std::string *argument_str = new std::string;

	size_t pos_of_first_space = instructions.find(' ');
	if (pos_of_first_space == std::string::npos) instruction = instructions;
	else
	{
		instruction = instructions.substr(0, pos_of_first_space);
		*argument_str = instructions.substr(pos_of_first_space+1);
	}

	std::cout << "signaling >> " << instruction << "|" << *argument_str << std::endl;

	if (first_time_launch && ignore_all_on_load) return;
	send_signal(instruction, (void *)argument_str);
}

