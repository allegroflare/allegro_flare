

#include <AllegroFlare/Achievements.hpp>


#include <AllegroFlare/EventNames.hpp>
#include <iostream>
#include <sstream>


namespace AllegroFlare
{
   Achievements::Achievements(EventEmitter *event_emitter)
      : all_achievements({})
      , event_emitter(event_emitter)
   {}


   Achievements::~Achievements()
   {
      for (auto &achievement : all_achievements)
         delete achievement.second.first;
      all_achievements.clear();
   }


   void Achievements::add(std::string name, Achievement *achievement)
   {
      // TODO: check for overwrite
      all_achievements[name].first = achievement;
      all_achievements[name].second = false;
   }


   void Achievements::check_all()
   {
      for (auto &achievement : all_achievements)
      {
         bool achievement_already_unlocked = achievement.second.second;
         if (!achievement_already_unlocked && achievement.second.first->test_condition())
         {
            unlock_manually(achievement.first);
            //achievement.second.first->on_achieved();
            //achievement.second.second = true;
            //if (event_emitter)
            //{
               //// TODO: add test for this case
               //Achievement* completed_achievement = achievement.second.first;
               //event_emitter->emit_event(ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, (intptr_t)completed_achievement);
            //}
         }
      }
   }

   int Achievements::get_num_achievements()
   {
      return all_achievements.size();
   }

   void Achievements::clear_all()
   {
      all_achievements.clear();
   }

   bool Achievements::all_achieved()
   {
      for (auto &achievement : all_achievements)
      {
         if (!achievement.second.second) return false;
      }
      return true;
   }

   bool Achievements::unlock_manually(std::string name)
   {
      std::map<std::string, std::pair<Achievement *, bool>>::iterator it = all_achievements.find(name);
      if (it == all_achievements.end())
      {
         std::stringstream ss;
         ss << "[Achievements::unlock_manually] error: Could not find achievement named \""
            << name << "\"";
         std::cout << ss.str();
         return false;
      }

      std::pair<Achievement *, bool> &achievement = it->second;

      achievement.first->on_achieved();
      achievement.second = true;
      if (event_emitter)
      {
         // TODO: add test for this case
         Achievement* completed_achievement = achievement.first;
         event_emitter->emit_event(ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, (intptr_t)completed_achievement);
      }
   }

   void Achievements::set_event_emitter(EventEmitter *event_emitter)
   {
      this->event_emitter = event_emitter;
   }
}


