

#include <AllegroFlare/Profiler.hpp>

#include <sstream>
#include <algorithm>


namespace AllegroFlare
{
   Profiler::Profiler()
      : timers()
   {}


   Profiler::~Profiler()
   {
   }


   AllegroFlare::Timer *Profiler::find_or_create(std::string name)
   {
      std::map<std::string, AllegroFlare::Timer>::iterator it = timers.find(name);
      if (it == timers.end())
      {
         timers[name] = AllegroFlare::Timer();
         return &timers[name];
      }
      return &it->second;
   }


   void Profiler::start(std::string name)
   {
      find_or_create(name)->start();
   }


   void Profiler::pause(std::string name)
   {
      find_or_create(name)->pause();
   }


   void Profiler::clear()
   {
      timers.clear();
   }
}



