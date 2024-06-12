

#include <AllegroFlare/TransitionFX/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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


bool Base::get_finished() const
{
   return finished;
}


void Base::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TransitionFX::Base::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TransitionFX::Base::initialize]: error: guard \"(!initialized)\" not met");
   }

   // IMPORTANT: Design does not currently work effectively in conjunction with AllegroFlare
   // TODO: this needs to be modified to expect and work with existing and active AllegroFlare rendering surface
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
      error_message << "[AllegroFlare::TransitionFX::Base::get_pasteboard_a]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TransitionFX::Base::get_pasteboard_a]: error: guard \"initialized\" not met");
   }
   return pasteboard_a;
}

ALLEGRO_BITMAP* Base::get_pasteboard_b()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TransitionFX::Base::get_pasteboard_b]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TransitionFX::Base::get_pasteboard_b]: error: guard \"initialized\" not met");
   }
   return pasteboard_b;
}

void Base::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TransitionFX::Base::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TransitionFX::Base::update]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::TransitionFX::Base::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TransitionFX::Base::render]: error: guard \"initialized\" not met");
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


