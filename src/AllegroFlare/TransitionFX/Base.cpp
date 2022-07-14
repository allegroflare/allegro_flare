

#include <AllegroFlare/TransitionFX/Base.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace TransitionFX
{


Base::Base(ALLEGRO_BITMAP* display_bitmap)
   : display_bitmap(display_bitmap)
   , surface_A(nullptr)
   , surface_B(nullptr)
   , duration(2.0f)
   , position(0.0f)
   , finished(false)
   , initialized(false)
{
}


Base::~Base()
{
}


ALLEGRO_BITMAP* Base::get_surface_A()
{
   return surface_A;
}


ALLEGRO_BITMAP* Base::get_surface_B()
{
   return surface_B;
}


bool Base::get_finished()
{
   return finished;
}


void Base::set_display_bitmap(ALLEGRO_BITMAP* display_bitmap)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "set_display_bitmap" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->display_bitmap = display_bitmap;
   return;
}

void Base::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(display_bitmap))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "initialize" << ": error: " << "guard \"display_bitmap\" not met";
         throw std::runtime_error(error_message.str());
      }
   surface_A = al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap));
   surface_B = al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap));
   initialized = true;
   return;
}

void Base::update()
{
   return;
}

void Base::draw()
{
   return;
}
} // namespace TransitionFX
} // namespace AllegroFlare


