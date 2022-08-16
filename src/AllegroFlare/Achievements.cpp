

#include <AllegroFlare/Achievements.hpp>


#include <AllegroFlare/EventNames.hpp>
#include <iostream>
#include <sstream>


namespace AllegroFlare
{
   Achievements::Achievements(
      EventEmitter *event_emitter,
      std::unordered_map<std::string, std::tuple<Achievement *, bool, bool>> all_achievements
   )
      : event_emitter(event_emitter)
      , all_achievements(all_achievements)
   {}


   Achievements::~Achievements()
   {}


   bool Achievements::unlock(std::tuple<Achievement *, bool, bool> *achievement)
   {
      if (!achievement)
      {
         // TODO: errors
      }

      if (std::get<1>(*achievement) == true)
      {
         // TODO: consider outputting a message
         return false;
      }
      else
      {
         std::get<0>(*achievement)->on_unlocked();
         std::get<1>(*achievement) = true;
         if (event_emitter)
         {
            Achievement* completed_achievement = std::get<0>(*achievement);
            event_emitter->emit_event(ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, (intptr_t)completed_achievement);
         }
         return true;
      }
   }


   void Achievements::add(std::string identifier, Achievement *achievement)
   {
      // TODO: check for overwrite
      std::get<0>(all_achievements[identifier]) = achievement;
      std::get<1>(all_achievements[identifier]) = false;
   }


   void Achievements::set_achievements(std::unordered_map<std::string, std::tuple<Achievement *, bool, bool>> all_achievements)
   {
      this->all_achievements = all_achievements;
   }


   std::unordered_map<std::string, std::tuple<Achievement *, bool, bool>> Achievements::get_achievements()
   {
      return all_achievements;
   }


   void Achievements::check_all()
   {
      for (auto &achievement : all_achievements)
      {
         bool achievement_already_unlocked = std::get<1>(achievement.second);
         if (!achievement_already_unlocked && std::get<0>(achievement.second)->test_condition())
         {
            unlock(&achievement.second);
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


   bool Achievements::all_unlocked()
   {
      for (auto &achievement : all_achievements)
      {
         if (!std::get<1>(achievement.second)) return false;
      }
      return true;
   }


   bool Achievements::unlock_manually(std::string identifier)
   {
      std::unordered_map<std::string, std::tuple<Achievement *, bool, bool>>::iterator it = all_achievements.find(identifier);
      if (it == all_achievements.end())
      {
         std::stringstream ss;
         ss << "[Achievements::unlock_manually] error: Could not find achievement with identifier \""
            << identifier << "\"";
         std::cout << ss.str();
         return false;
      }

      std::tuple<Achievement *, bool, bool> &achievement = it->second;

      return unlock(&achievement);
   }


   void Achievements::set_event_emitter(EventEmitter *event_emitter)
   {
      this->event_emitter = event_emitter;
   }


   std::string Achievements::dump()
   {
      std::stringstream result;
      for (auto &achievement : all_achievements)
      {
         result << "achievement: \""
                << std::get<0>(achievement)    //.first
                << "\", unlocked: "
                << (std::get<1>(achievement.second) ? "true" : "false")
                << std::endl;
      }
      return result.str();
   }
}


