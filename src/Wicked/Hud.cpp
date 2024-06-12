

#include <Wicked/Hud.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{


Hud::Hud(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , score(0)
   , health(0)
{
}


Hud::~Hud()
{
}


void Hud::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Hud::set_score(int score)
{
   this->score = score;
}


void Hud::set_health(int health)
{
   this->health = health;
}


int Hud::get_score() const
{
   return score;
}


int Hud::get_health() const
{
   return health;
}


void Hud::primary_timer_func()
{
   return;
}

void Hud::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Hud::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Hud::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Hud::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Hud::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_health();
   draw_score();
   return;
}

void Hud::draw_health()
{
   ALLEGRO_FONT *font = obtain_hud_text_font();
   std::stringstream ss;
   ss << "HEALTH   " << health;
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 50, 30, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   return;
}

void Hud::draw_score()
{
   ALLEGRO_FONT *font = obtain_hud_text_font();
   int surface_width = 1920;
   std::stringstream ss;
   ss << "SCORE " << std::setw(6) << std::setfill('0') << score;
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, surface_width -50, 30, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
   return;
}

ALLEGRO_FONT* Hud::obtain_hud_text_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Hud::obtain_hud_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Hud::obtain_hud_text_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -48");
   //NOTE: previously return font_bin->auto_get("Manrope-Light.ttf -48");
}


} // namespace Wicked


