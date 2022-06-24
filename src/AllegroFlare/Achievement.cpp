
#include <AllegroFlare/Achievement.hpp>


namespace AllegroFlare
{
   Achievement::Achievement()
      : unlocked(false)
   {}


   Achievement::~Achievement()
   {}



   bool Achievement::unlock_manually()
   {
      if (unlocked) return false;

      unlocked = true;
      on_unlocked();
      return true;
   }

   bool Achievement::is_unlocked() { return unlocked; }


   bool Achievement::test_condition() { return false; }


   void Achievement::on_unlocked() {}
}


