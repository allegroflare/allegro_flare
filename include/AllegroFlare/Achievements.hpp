#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <string>
#include <map>
#include <tuple>


namespace AllegroFlare
{
   class Achievements
   {
   private:
      EventEmitter *event_emitter;
      std::map<std::string, std::tuple<Achievement *, bool, bool>> all_achievements;
      bool unlock(std::tuple<Achievement *, bool, bool> *achievement);

   public:
      Achievements(
         EventEmitter *event_emitter=nullptr,
         std::map<std::string, std::tuple<Achievement *, bool, bool>> all_achievements={}
      );
      ~Achievements();

      void add(std::string identifier, Achievement *achievement);
      void check_all();
      int get_num_achievements();
      void clear_all();
      bool all_unlocked();
      bool unlock_manually(std::string identifier);

      void set_achievements(std::map<std::string, std::tuple<Achievement *, bool, bool>> all_achievements={});
      std::map<std::string, std::tuple<Achievement *, bool, bool>> get_achievements();

      void set_event_emitter(EventEmitter *event_emitter=nullptr);
      std::string dump();
   };
}


