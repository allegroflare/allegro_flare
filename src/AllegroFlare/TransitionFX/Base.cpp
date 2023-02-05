

#include <AllegroFlare/TransitionFX/Base.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace TransitionFX
{


Base::Base(float duration_sec)
   : pasteboard_a(nullptr)
   , pasteboard_b(nullptr)
   , duration_sec(duration_sec)
   , position(0.0f)
   , finished(false)
   , initialized(false)
{
}


Base::~Base()
{
}


bool Base::get_finished()
{
   return finished;
}


void Base::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());

   pasteboard_a = al_create_bitmap(al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
   pasteboard_b = al_create_bitmap(al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));

   initialized = true;
   return;
}

ALLEGRO_BITMAP* Base::get_pasteboard_a()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "get_pasteboard_a" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return pasteboard_a;
}

ALLEGRO_BITMAP* Base::get_pasteboard_b()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "get_pasteboard_b" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return pasteboard_b;
}

void Base::update()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   position += 1.0 / 60.0;
   if (position >= duration_sec) finished = true;
   return;
}

void Base::render()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Base" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   float alpha = 1.0 - (duration_sec - position) / duration_sec;
   if (alpha >= 1.0) alpha = 1.0f;
   if (alpha <= 0.0) alpha = 0.0f;
   al_draw_bitmap(pasteboard_a, 0, 0, 0);
   al_draw_tinted_bitmap(pasteboard_b, ALLEGRO_COLOR{alpha, alpha, alpha, alpha}, 0, 0, 0);
   return;
}
} // namespace TransitionFX
} // namespace AllegroFlare


