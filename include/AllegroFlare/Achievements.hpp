#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <string>
#include <vector>
#include <tuple>


namespace AllegroFlare
{
   class Achievements
   {
   private:
      EventEmitter *event_emitter;
      std::vector<std::tuple<std::string, Achievement *, bool, bool>> all_achievements;
      bool unlock(std::tuple<std::string, Achievement *, bool, bool> *achievement, bool emit_event=true);
      std::tuple<std::string, Achievement *, bool, bool>* find(std::string identifier);

   public:
      Achievements(
         EventEmitter *event_emitter=nullptr,
         std::vector<std::tuple<std::string, Achievement *, bool, bool>> all_achievements={}
      );
      ~Achievements();

      void add(std::string identifier, Achievement *achievement);
      void check_all();
      int get_num_achievements();
      void clear_all();
      bool all_unlocked();
      bool unlock_manually(std::string identifier);
      bool unlock_silently(std::string identifier);

      void set_achievements(std::vector<std::tuple<std::string, Achievement *, bool, bool>> all_achievements={});
      std::vector<std::tuple<std::string, Achievement *, bool, bool>> get_achievements();

      void set_event_emitter(EventEmitter *event_emitter=nullptr);
      std::string dump();
   };
}


