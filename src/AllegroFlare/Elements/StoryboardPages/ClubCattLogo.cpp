

#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


ClubCattLogo::ClubCattLogo()
   : AllegroFlare::Elements::StoryboardPages::Base(AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE)
   , clubcatt_logo()
{
}


ClubCattLogo::~ClubCattLogo()
{
}


void ClubCattLogo::initialize()
{
   set_finished(false);
   clubcatt_logo.initialize();
}

void ClubCattLogo::primary_timer_func()
{
   // Update
   float time_now = al_get_time();
   clubcatt_logo.update(time_now);
   if (!get_finished() && clubcatt_logo.get_finished()) set_finished(true);

   // Draw
   clubcatt_logo.draw(time_now);
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


