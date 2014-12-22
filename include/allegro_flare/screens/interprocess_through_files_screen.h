#ifndef __AF_INTERPROCESS_SCREEN_HEADER
#define __AF_INTERPROCESS_SCREEN_HEADER




#include <allegro_flare/allegro_flare.h>
//#include <allegro_flare/curl.h>
#include <allegro_flare/interprocess.h>
#include <allegro_flare/interprocess_through_files.h>



// InterprocessScreen
// 1) An interprocess screen automatically polls the interprocess location for new instruction (each instruction is a file)
// 2) when a new instruction is detected, it broadcasts the instruction as a signal to all the the other screens.
// 3) When an InterprocessScreen is running, all Screen objects will recieve an interprocess broadcast as a signal.


class InterprocessThroughFilesScreen : public Screen, public InterprocessThroughFiles
{
private:
	void process_interprocess_instruction(std::string &filename);
	bool active;
	float check_frequency;
	double last_check_time;
	double timeout_clear_time;
	bool first_time_launch;
	bool ignore_all_on_load;

public:
	InterprocessThroughFilesScreen(std::string full_path="C:/II/", bool ignore_all_on_load=false);
	void primary_timer_func() override;
	void set_check_frequency(float frequency_in_sec);
	void halt(); // stop interprocess checks
	void resume(); // continue interprocess checks
};




#endif