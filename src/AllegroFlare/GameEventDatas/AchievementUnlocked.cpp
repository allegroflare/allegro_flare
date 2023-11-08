

#include <AllegroFlare/GameEventDatas/AchievementUnlocked.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


AchievementUnlocked::AchievementUnlocked(std::string achievement_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::AchievementUnlocked::TYPE)
   , achievement_identifier(achievement_identifier)
{
}


AchievementUnlocked::~AchievementUnlocked()
{
}


std::string AchievementUnlocked::get_achievement_identifier() const
{
   return achievement_identifier;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


