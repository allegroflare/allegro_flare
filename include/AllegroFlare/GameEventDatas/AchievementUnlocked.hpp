#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class AchievementUnlocked : public AllegroFlare::GameEventDatas::Base
      {
      public:
         static constexpr char* NAME = (char*)"AllegroFlare/GameEvent/AchievementUnlocked";
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/AchievementUnlocked";

      private:
         std::string achievement_identifier;

      protected:


      public:
         AchievementUnlocked(std::string achievement_identifier="[unset-achievement_identifier]");
         ~AchievementUnlocked();

         std::string get_achievement_identifier() const;
      };
   }
}



