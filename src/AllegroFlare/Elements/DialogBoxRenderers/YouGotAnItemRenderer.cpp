

#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotAnItemRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


YouGotAnItemRenderer::YouGotAnItemRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string item_name, std::string item_bitmap_identifier, float age, float width, float height)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , item_name(item_name)
   , item_bitmap_identifier(item_bitmap_identifier)
   , age(age)
   , width(width)
   , height(height)
{
}


YouGotAnItemRenderer::~YouGotAnItemRenderer()
{
}


std::string YouGotAnItemRenderer::get_item_name() const
{
   return item_name;
}


std::string YouGotAnItemRenderer::get_item_bitmap_identifier() const
{
   return item_bitmap_identifier;
}


float YouGotAnItemRenderer::get_age() const
{
   return age;
}


void YouGotAnItemRenderer::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   // style attributes
   ALLEGRO_COLOR fading_white = opaquify(ALLEGRO_COLOR{1, 1, 1, 1});
   ALLEGRO_FONT* notification_text_font = obtain_notification_text_font();
   ALLEGRO_FONT* item_name_text_font = obtain_item_name_text_font();
   float notification_text_font_line_heigt = al_get_font_line_height(notification_text_font);
   float item_name_text_font_line_heigt = al_get_font_line_height(item_name_text_font);
   //ALLEGRO_COLOR text_color = opaquify(al_color_html("fbedc3"));
   ALLEGRO_COLOR text_color = opaquify(al_color_html("ffffff"));
   ALLEGRO_COLOR item_name_text_color = opaquify(al_color_html("ffffff"));
   ALLEGRO_COLOR item_name_text_dropshadow_color = opaquify(al_color_html("770000"));
   std::string notification_text = "You got an item!";
   std::string item_name_text = get_item_name(); // "Watch";
   std::string item_bitmap_identifier = get_item_bitmap_identifier();
   ALLEGRO_BITMAP* item_bitmap = bitmap_bin->auto_get(item_bitmap_identifier);
   int item_bitmap_width = al_get_bitmap_width(item_bitmap);
   int item_bitmap_height = al_get_bitmap_height(item_bitmap);
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   //dialog_box_frame.set_fill_color(opaquify(al_color_html("2a2104")));
   //dialog_box_frame.set_border_color(opaquify(al_color_html("c49505")));
   dialog_box_frame.set_border_color(opaquify(ALLEGRO_COLOR{1.0, .65, 0.0, 1.0}));
   AllegroFlare::Placement2D item_place(width/2, height/2, item_bitmap_width, item_bitmap_height);
   item_place.scale.x = 0.55;
   item_place.scale.y = 0.55;

   // animations
   float reveal_counter = get_live_reveal_counter();
   item_place.position.y += ((1.0 - AllegroFlare::interpolator::fast_in(reveal_counter)) * 30);
   float scale_multiplier = 1.0;
   item_place.scale.x = item_place.scale.x * scale_multiplier;
   item_place.scale.y = item_place.scale.y * scale_multiplier;

   // draw the frame
   dialog_box_frame.render();

   // draw the notification text
   al_draw_text(
      notification_text_font,
      text_color,
      width/2,
      30, //height/2 - 180,
      //height - 180,
      ALLEGRO_ALIGN_CENTER,
      notification_text.c_str()
   );

   // draw the item image
   item_place.start_transform();
   al_draw_tinted_bitmap(item_bitmap, fading_white, 0, 0, 0);
   item_place.restore_transform();

   // the collected item name
   // draw a nice little drop shadow :)
   float item_name_text_y_position = height - 80;//height/2 + 120;
   al_draw_text(
      item_name_text_font,
      item_name_text_dropshadow_color,
      width/2,
      item_name_text_y_position + 3,
      ALLEGRO_ALIGN_CENTER,
      item_name_text.c_str()
   );
   al_draw_text(
      item_name_text_font,
      item_name_text_color,
      width/2,
      item_name_text_y_position,
      ALLEGRO_ALIGN_CENTER,
      item_name_text.c_str()
   );

   return;
}

float YouGotAnItemRenderer::get_live_reveal_counter()
{
   float local_age = get_age();
   float time_duration_to_reveal = 0.8;
   if (local_age >= time_duration_to_reveal) local_age = time_duration_to_reveal;
   float reveal_duration_normalized = 1.0 - ((time_duration_to_reveal - local_age) / time_duration_to_reveal);
   //return 0.5;
   return reveal_duration_normalized;
}

ALLEGRO_FONT* YouGotAnItemRenderer::obtain_notification_text_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotAnItemRenderer::obtain_notification_text_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Regular.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}

ALLEGRO_FONT* YouGotAnItemRenderer::obtain_item_name_text_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -36");
}

ALLEGRO_COLOR YouGotAnItemRenderer::opaquify(ALLEGRO_COLOR color)
{
   //AllegroFlare::color::change_alpha(color, reveal_counter);
   //AllegroFlare::color::change_alpha(color, 1.0);
      float opacity = get_live_reveal_counter();
      opacity = AllegroFlare::interpolator::double_fast_in(opacity);
      color.a *= opacity;
      color.r *= color.a;
      color.g *= color.a;
      color.b *= color.a;
   return color;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


