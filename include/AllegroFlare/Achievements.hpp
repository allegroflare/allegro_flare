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
      bool unlock(std::pair<Achievement *, bool> *achievement);

   public:
      Achievements(EventEmitter *event_emitter=nullptr);
      ~Achievements();

      void add(std::string identifier, Achievement *achievement);
      void check_all();
      int get_num_achievements();
      void clear_all();
      bool all_unlocked();
      bool unlock_manually(std::string identifier);

      void set_event_emitter(EventEmitter *event_emitter=nullptr);
      std::string dump();
   };
}


