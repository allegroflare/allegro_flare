#pragma once


#include <string>


namespace AllegroFlare
{
   class Achievement
   {
   private:
      std::string title;
      bool unlocked;

   public:
      Achievement(std::string title="Base");
      virtual ~Achievement();

      bool virtual unlock_manually() final;
      bool is_unlocked();
      bool virtual test_condition();
      void virtual on_unlocked();

      bool set_title(std::string title);
      std::string get_title();
   };
}


