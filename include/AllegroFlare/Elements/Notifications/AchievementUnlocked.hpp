#pragma once


#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Notifications
      {
         class AchievementUnlocked : public AllegroFlare::Elements::Notifications::Base
         {
         private:
            std::string name;

         protected:


         public:
            AchievementUnlocked(std::string name="[unset-name]");
            ~AchievementUnlocked();

            void set_name(std::string name);
            std::string get_name() const;
         };
      }
   }
}



