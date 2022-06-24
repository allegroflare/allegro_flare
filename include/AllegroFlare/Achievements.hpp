#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <string>
#include <map>


namespace AllegroFlare
{
   class Achievements
   {
   private:
      std::map<std::string, std::pair<Achievement *, bool>> all_achievements;
      EventEmitter *event_emitter;

   public:
      Achievements(EventEmitter *event_emitter=nullptr);
      ~Achievements();

      void add(std::string name, Achievement *achievement);
      void check_all();
      int get_num_achievements();
      void clear_all();
      bool all_achieved();

      void set_event_emitter(EventEmitter *event_emitter=nullptr);
   };
}


