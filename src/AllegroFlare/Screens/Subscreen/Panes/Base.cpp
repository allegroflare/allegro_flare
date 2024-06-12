

#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{
namespace Panes
{


Base::Base(std::string type, std::string name)
   : type(type)
   , name(name)
{
}


Base::~Base()
{
}


void Base::set_name(std::string name)
{
   this->name = name;
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_name() const
{
   return name;
}


void Base::on_switch_in()
{
   return;
}

void Base::on_switch_out()
{
   return;
}

void Base::update()
{
   return;
}

void Base::render()
{
   return;
}

void Base::draw_empty_state(AllegroFlare::FontBin* font_bin, std::string placeholder_text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Panes::Base::draw_empty_state]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Panes::Base::draw_empty_state]: error: guard \"font_bin\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Panes::Base::draw_empty_state]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Panes::Base::draw_empty_state]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   static constexpr float frame_width = 1920;
   static constexpr float frame_height = 1080;
   static constexpr float width = frame_width - 100 * 2;
   static constexpr float height = frame_height - 142 * 2;
   static constexpr float cx = frame_width / 2;
   static constexpr float cy = frame_height / 2;

   static constexpr float x1 = cx - width * 0.5;;
   static constexpr float y1 = cy - height * 0.5;
   static constexpr float x2 = cx + width * 0.5;
   static constexpr float y2 = cy + height * 0.5;

   al_draw_rectangle(x1, y1, x2, y2, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);

   // draw the text
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* font = font_bin->operator[](FONT_IDENTIFIER);

   al_draw_text(
         font,
         ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
         1920 * 0.5,
         1080 * 0.5,
         ALLEGRO_ALIGN_CENTER,
         placeholder_text.c_str()
      );

   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Panes
} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


