
#include <AllegroFlare/Achievement.hpp>


namespace AllegroFlare
{
   Achievement::Achievement()
      : achieved(false)
   {}


   Achievement::~Achievement()
   {}


   bool Achievement::is_achieved() { return achieved; }


   bool Achievement::test_condition() { return false; }


   void Achievement::on_achieved() {}
}


