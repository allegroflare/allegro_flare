

#include <AllegroFlare/Achievements.hpp>


#include <iostream>


namespace AllegroFlare
{
   Achievements::Achievements()
      : all_achievements({})
   {}


   Achievements::~Achievements()
   {
      for (auto &achievement : all_achievements)
         delete achievement.second.first;
      all_achievements.clear();
   }


   void Achievements::add(std::string name, Achievement *achievement)
   {
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
            achievement.second.first->on_achieved();
            achievement.second.second = true;
         }
      }
   }
}


