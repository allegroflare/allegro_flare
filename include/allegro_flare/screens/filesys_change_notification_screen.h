#ifndef __AF_FILESYS_CHANGE_NOTIFICATION_SCREEN_HEADER
#define __AF_FILESYS_CHANGE_NOTIFICATION_SCREEN_HEADER



#include <allegro_flare/allegro_flare.h>

#define ALLEGRO_EVENT_FILESYS_CHANGE ALLEGRO_GET_EVENT_TYPE('F','S','C','H')




class FileSysChangeNotificationScreen
{
private:
	static FileSysChangeNotificationScreen *instance;
	ALLEGRO_EVENT_SOURCE filesys_change_event_source;
	static FileSysChangeNotificationScreen *get_instance();

	FileSysChangeNotificationScreen();
	~FileSysChangeNotificationScreen();

public:
	static void watch_directory__blocking(std::string directory);
	static void emit_filesys_change(std::string dir);
	//static void unwatch_directory(std::string directory);
	//static std::vector<std::string> get_watched_directories();
};


/*

// example usage:

void MyProgramScreen::user_func()
{
	if (af::current_event->type == ALLEGRO_EVENT_FILESYS_CHANGE)
	{
		if (
		// handle the operations here
	}
}
*/


#endif

