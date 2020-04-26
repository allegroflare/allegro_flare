#pragma once


#include <string>
#include <map>

#include <AllegroFlare/Timer.hpp>


namespace AllegroFlare
{
   class Profiler
   {
   private:
      std::map<std::string, AllegroFlare::Timer> timers;

      AllegroFlare::Timer *find_or_create(std::string name);

   public:
      Profiler();
      ~Profiler();

      void start(std::string name);
      void pause(std::string name);
      void clear();
   };
}


