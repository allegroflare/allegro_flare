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
   static void watch_directory__in_thread(std::string directory);
   static void emit_filesys_change(std::string dir);
   //static void unwatch_directory(std::string directory);
   //static std::vector<std::string> get_watched_directories();
};




/*

//
// example usage:
//

#include <allegro_flare/screens/filesys_change_notification_screen.h>

class MyProject : public Screen
{
public:
   MyProject(Display *display)
      : Screen(display)
   {
      FileSysChangeNotificationScreen::watch_directory__in_thread("C:/Users/Mark/Desktop/myfolder");
   }

   void user_event_func() override
   {
      if (af::current_event->type == ALLEGRO_EVENT_FILESYS_CHANGE)
      {
         std::cout << "DIRECTORY CHANGED!" << std::endl;
      }
   }
};

*/




#endif
