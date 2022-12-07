
#include <AllegroFlare/Achievement.hpp>


namespace AllegroFlare
{
   Achievement::Achievement(std::string title, std::string description)
      : title(title)
      , description(description)
      , unlocked(false)
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


   void Achievement::set_title(std::string title)
   {
      this->title = title;
   }


   std::string Achievement::get_title()
   {
      return title;
   }


   void Achievement::set_description(std::string description)
   {
      this->description = description;
   }


   std::string Achievement::get_description()
   {
      return description;
   }
}


