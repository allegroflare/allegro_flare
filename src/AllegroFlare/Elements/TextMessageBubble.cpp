

#include <AllegroFlare/Elements/TextMessageBubble.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


TextMessageBubble::TextMessageBubble(AllegroFlare::FontBin* font_bin, std::string text, float width, float height, bool callout_on_left)
   : font_bin(font_bin)
   , text(text)
   , width(width)
   , height(height)
   , callout_on_left(callout_on_left)
{
}


TextMessageBubble::~TextMessageBubble()
{
}


void TextMessageBubble::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TextMessageBubble::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMessageBubble::render: error: guard \"font_bin\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TextMessageBubble::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TextMessageBubble::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   //ALLEGRO_COLOR bubble_color = al_color_html("40669F");
   //ALLEGRO_COLOR bubble_color = al_color_html("6F7C8F"); // a nice gray
   ALLEGRO_COLOR bubble_color = al_color_html("66848b");
   ALLEGRO_COLOR text_color = al_color_name("white");
   float roundness = 32.0f;
   //if (roundness <= 10.0) roundness = 10.0;
   float sender_indent_padding = 80;

   al_draw_filled_rounded_rectangle(0, 0, width - sender_indent_padding, height, roundness, roundness, bubble_color);

   if (callout_on_left)
   {
      al_draw_filled_rectangle(0, height/2, height/2, height, bubble_color);
   }
   else
   {
      al_draw_filled_rectangle(width, height/2, width-height/2, height, bubble_color);
   }

   ALLEGRO_FONT *font = obtain_text_font();
   float padding_x = 30;
   float padding_y = 20;
   float text_box_width = width - padding_y * 2 - sender_indent_padding;
   float line_height = al_get_font_line_height(font);
   al_draw_multiline_text(
      font,
      text_color,
      padding_x,
      padding_y,
      text_box_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      text.c_str()
   );

   return;
}

ALLEGRO_FONT* TextMessageBubble::obtain_text_font()
{
   return font_bin->auto_get("Inter-Medium.ttf -42");
}


} // namespace Elements
} // namespace AllegroFlare


