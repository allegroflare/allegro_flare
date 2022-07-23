

#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Screen::Screen()
   : AllegroFlare::Screens::Base("Prototypes::FixedRoom2D::Screen")
   , fixed_room_2d({})
{
}


Screen::~Screen()
{
}


void Screen::on_activate()
{
   return;
}

void Screen::on_deactivate()
{
   return;
}

void Screen::primary_timer_func()
{
   fixed_room_2d.update();
   fixed_room_2d.render();
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


