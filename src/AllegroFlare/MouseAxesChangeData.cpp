

#include <AllegroFlare/MouseAxesChangeData.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


MouseAxesChangeData::MouseAxesChangeData()
   : x(0)
   , y(0)
   , z(0)
   , w(0)
   , dx(0)
   , dy(0)
   , dz(0)
   , dw(0)
   , display(nullptr)
{
}


MouseAxesChangeData::~MouseAxesChangeData()
{
}


void MouseAxesChangeData::populate_data_from_ALLEGRO_EVENT(ALLEGRO_EVENT* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MouseAxesChangeData::populate_data_from_ALLEGRO_EVENT]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MouseAxesChangeData::populate_data_from_ALLEGRO_EVENT]: error: guard \"ev\" not met");
   }
   if (!((ev->type == ALLEGRO_EVENT_MOUSE_AXES)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MouseAxesChangeData::populate_data_from_ALLEGRO_EVENT]: error: guard \"(ev->type == ALLEGRO_EVENT_MOUSE_AXES)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MouseAxesChangeData::populate_data_from_ALLEGRO_EVENT]: error: guard \"(ev->type == ALLEGRO_EVENT_MOUSE_AXES)\" not met");
   }
   x = ev->mouse.x;
   y = ev->mouse.y;
   z = ev->mouse.z;
   w = ev->mouse.w;

   dx = ev->mouse.dx;
   dy = ev->mouse.dy;
   dz = ev->mouse.dz;
   dw = ev->mouse.dw;

   display = ev->mouse.display;

   return;
}


} // namespace AllegroFlare


