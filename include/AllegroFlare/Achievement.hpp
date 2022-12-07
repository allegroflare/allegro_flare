#pragma once


#include <string>


namespace AllegroFlare
{
   class Achievement
   {
   private:
      std::string title;
      std::string description;
      bool unlocked;

   public:
      Achievement(std::string title="Achievement", std::string description="Unset description");
      virtual ~Achievement();

      bool virtual unlock_manually() final;
      bool is_unlocked();
      bool virtual test_condition();
      void virtual on_unlocked();

      void set_title(std::string title);
      std::string get_title();
      bool set_description(std::string description);
      std::string get_description();
   };
}


