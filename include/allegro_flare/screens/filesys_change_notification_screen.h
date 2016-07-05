#ifndef __AF_FILESYS_WATCHER_HEADER
#define __AF_FILESYS_WATCHER_HEADER




#include <allegro_flare/allegro_flare.h>

#define ALLEGRO_EVENT_FILESYS_CHANGE ALLEGRO_GET_EVENT_TYPE('F','S','C','H')




class FileSysWatcher
{
private:
   static FileSysWatcher *instance;
   ALLEGRO_EVENT_SOURCE filesys_change_event_source;
   static FileSysWatcher *get_instance();

   FileSysWatcher();
   ~FileSysWatcher();

public:
   static void watch_directory__blocking(std::string directory);
   static void watch_directory__in_thread(std::string directory);
   static void emit_filesys_change(std::string dir);
   //static void unwatch_directory(std::string directory);
   //static std::vector<std::string> get_watched_directories();
};




#endif
