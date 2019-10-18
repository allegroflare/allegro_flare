#pragma once


namespace AllegroFlare
{
   class Achievement
   {
   private:
      bool achieved;

   public:
      Achievement();
      virtual ~Achievement();

      bool is_achieved();
      bool virtual test_condition();
      void virtual on_achieved();
   };
}


