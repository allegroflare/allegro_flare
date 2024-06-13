

#include <AllegroFlare/Elements/Score.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Score::Score(AllegroFlare::FontBin* font_bin, int score)
   : font_bin(font_bin)
   , score(score)
{
}


Score::~Score()
{
}


void Score::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Score::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Score::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Score::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Score::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Score::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Score::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Score::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Score::render]: error: guard \"font_bin\" not met");
   }
   float x = 1920/2;
   float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   std::string text = get_score_str();
   float text_width = al_get_text_width(font, text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, text.c_str());
   return;
}

std::string Score::get_score_str()
{
   //ALLEGRO_FONT *font = obtain_hud_text_font();
   //int surface_width = 1920;
   std::stringstream ss;
   ss << "SCORE " << std::setw(6) << std::setfill('0') << score;
   return ss.str();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, surface_width -50, 30, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
}

ALLEGRO_FONT* Score::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Score::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Score::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -52");
}


} // namespace Elements
} // namespace AllegroFlare


