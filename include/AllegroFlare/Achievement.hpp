#pragma once


#include <string>


namespace AllegroFlare
{
   class Achievement
   {
   private:
      std::string name;
      bool unlocked;

   public:
      Achievement(std::string name="Base");
      virtual ~Achievement();

      bool virtual unlock_manually() final;
      bool is_unlocked();
      bool virtual test_condition();
      void virtual on_unlocked();

      bool set_name(std::string name);
      std::string get_name();
   };
}


