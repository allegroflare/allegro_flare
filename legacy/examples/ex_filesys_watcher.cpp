



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;



class MyProject : public Screen
{
public:
   MyProject(Display *display)
      : Screen(display)
   {
      // watch the executable directory
      FileSysWatcher::watch_directory__in_thread(".");
   }

   void user_event_func() override
   {
      switch (Framework::current_event->type)
      {
      case ALLEGRO_EVENT_FILESYS_CHANGE:
         std::cout << "DIRECTORY CHANGED!" << std::endl;
         break;
      default:
         break;
      }
   }
};




int main(int argc, char *argv)
{
   MyProject proj = MyProject(nullptr);
   Framework::run_loop();
   return 0;
}




