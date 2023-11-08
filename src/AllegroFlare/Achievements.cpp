

#include <AllegroFlare/Achievements.hpp>


#include <AllegroFlare/EventNames.hpp>
#include <iostream>
#include <sstream>


namespace AllegroFlare
{
   Achievements::Achievements(
      EventEmitter *event_emitter,
      std::vector<std::tuple<std::string, Achievement *, bool, bool>> all_achievements
   )
      : event_emitter(event_emitter)
      , all_achievements(all_achievements)
   {}


   Achievements::~Achievements()
   {}


   bool Achievements::unlock(std::tuple<std::string, Achievement *, bool, bool> *achievement, bool emit_event)
   {
      if (!achievement)
      {
         // TODO: errors
      }

      if (std::get<2>(*achievement) == true)
      {
         // TODO: consider outputting a message
         return false;
      }
      else
      {
         std::get<1>(*achievement)->on_unlocked();
         std::get<2>(*achievement) = true;
         if (emit_event && event_emitter)
         {
            Achievement* completed_achievement = std::get<1>(*achievement);
            event_emitter->emit_event(ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, (intptr_t)completed_achievement);
         }
         return true;
      }
   }


   void Achievements::add(std::string identifier, Achievement *achievement)
   {
      std::tuple<std::string, Achievement *, bool, bool> *existing_achievement = find(identifier);
      if (existing_achievement)
      {
         // throw achievement with this name already exists
      }
      // TODO: check for overwrite
      all_achievements.push_back(
         std::tuple<std::string, Achievement *, bool, bool>({
            identifier,
            achievement,
            false,
            false
         })
      );
   }


   void Achievements::set_achievements(std::vector<std::tuple<std::string, Achievement *, bool, bool>> all_achievements)
   {
      this->all_achievements = all_achievements;
   }


   std::vector<std::tuple<std::string, Achievement *, bool, bool>> Achievements::get_achievements()
   {
      return all_achievements;
   }


   void Achievements::check_all()
   {
      for (auto &achievement : all_achievements)
      {
         bool achievement_already_unlocked = std::get<2>(achievement);
         if (!achievement_already_unlocked && std::get<1>(achievement)->test_condition())
         {
            unlock(&achievement);
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


   std::tuple<std::string, Achievement *, bool, bool>* Achievements::find(std::string identifier)
   {
      for (auto &achievement : all_achievements)
      {
         if (std::get<0>(achievement) == identifier) return &achievement;
      }
      return nullptr;
   }


   bool Achievements::all_unlocked()
   {
      for (auto &achievement : all_achievements)
      {
         if (!std::get<2>(achievement)) return false;
      }
      return true;
   }


   bool Achievements::unlock_manually(std::string identifier)
   {
      std::tuple<std::string, Achievement *, bool, bool> *found_achievement = find(identifier);
      if (!found_achievement)
      {
         std::stringstream ss;
         ss << "[Achievements::unlock_manually] error: Could not find achievement with identifier \""
            << identifier << "\"";
         std::cout << ss.str();
         return false;
      }

      //std::tuple<std::string, Achievement *, bool, bool> &achievement = (*it);

      return unlock(found_achievement);
   }


   bool Achievements::unlock_silently(std::string identifier)
   {
      std::tuple<std::string, Achievement *, bool, bool> *found_achievement = find(identifier);
      if (!found_achievement)
      {
         std::stringstream ss;
         ss << "[Achievements::unlock_silently] error: Could not find achievement with identifier \""
            << identifier << "\"";
         std::cout << ss.str();
         return false;
      }

      //std::tuple<std::string, Achievement *, bool, bool> &achievement = (*it);

      return unlock(found_achievement, false);
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
                << (std::get<2>(achievement) ? "true" : "false")
                << std::endl;
      }
      return result.str();
   }
}


