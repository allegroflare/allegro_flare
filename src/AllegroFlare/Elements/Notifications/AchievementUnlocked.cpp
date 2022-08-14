

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace Notifications
{


AchievementUnlocked::AchievementUnlocked(std::string name)
   : AllegroFlare::Elements::Notifications::Base("AchievementUnlocked")
   , name(name)
{
}


AchievementUnlocked::~AchievementUnlocked()
{
}


void AchievementUnlocked::set_name(std::string name)
{
   this->name = name;
}


std::string AchievementUnlocked::get_name()
{
   return name;
}


} // namespace Notifications
} // namespace Elements
} // namespace AllegroFlare


