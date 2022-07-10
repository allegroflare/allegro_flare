

#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Text::Text(AllegroFlare::FontBin* font_bin, std::string text)
   : AllegroFlare::Elements::StoryboardPages::Base("Text")
   , font_bin(font_bin)
   , text(text)
{
}


Text::~Text()
{
}


void Text::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Text::set_text(std::string text)
{
   this->text = text;
}


AllegroFlare::FontBin* Text::get_font_bin()
{
   return font_bin;
}


std::string Text::get_text()
{
   return text;
}


void Text::start()
{
   return;
}

void Text::update()
{
   return;
}

void Text::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Text" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT* font = obtain_font();
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20, 0, text.c_str());
   return;
}

void Text::advance()
{
   return;
}

ALLEGRO_FONT* Text::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Text" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_str = "Inter-Medium.ttf 48";
   return font_bin->auto_get(font_str);
}
} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


