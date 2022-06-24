#pragma once


namespace AllegroFlare
{
   class Achievement
   {
   private:
      bool unlocked;

   public:
      Achievement();
      virtual ~Achievement();

      bool virtual unlock_manually() final;
      bool is_unlocked();
      bool virtual test_condition();
      void virtual on_unlocked();
   };
}


