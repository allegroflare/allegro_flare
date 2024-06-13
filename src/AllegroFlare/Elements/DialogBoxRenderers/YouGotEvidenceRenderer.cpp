

#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotEvidenceRenderer.hpp>

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


YouGotEvidenceRenderer::YouGotEvidenceRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string evidence_name, std::string evidence_bitmap_identifier, float age, float width, float height)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , evidence_name(evidence_name)
   , evidence_bitmap_identifier(evidence_bitmap_identifier)
   , age(age)
   , width(width)
   , height(height)
{
}


YouGotEvidenceRenderer::~YouGotEvidenceRenderer()
{
}


std::string YouGotEvidenceRenderer::get_evidence_name() const
{
   return evidence_name;
}


std::string YouGotEvidenceRenderer::get_evidence_bitmap_identifier() const
{
   return evidence_bitmap_identifier;
}


float YouGotEvidenceRenderer::get_age() const
{
   return age;
}


float YouGotEvidenceRenderer::get_width() const
{
   return width;
}


float YouGotEvidenceRenderer::get_height() const
{
   return height;
}


void YouGotEvidenceRenderer::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   // source data
   std::string notification_text = "You got new evidence";
   std::string evidence_name_text = get_evidence_name(); // "Watch";
   std::string evidence_bitmap_identifier = get_evidence_bitmap_identifier();
   ALLEGRO_BITMAP* evidence_bitmap = bitmap_bin->auto_get(evidence_bitmap_identifier);

   // style attributes
   ALLEGRO_COLOR fading_white = opaquify(ALLEGRO_COLOR{1, 1, 1, 1});
   ALLEGRO_FONT* notification_text_font = obtain_notification_text_font();
   ALLEGRO_FONT* evidence_name_text_font = obtain_evidence_name_text_font();
   ALLEGRO_FONT* evidence_description_font = obtain_evidence_description_font();
   float notification_text_font_line_heigt = al_get_font_line_height(notification_text_font);
   float evidence_name_text_font_line_heigt = al_get_font_line_height(evidence_name_text_font);
   float evidence_description_font_line_height = al_get_font_line_height(evidence_description_font);
   //ALLEGRO_COLOR text_color = opaquify(al_color_html("fbedc3"));
   ALLEGRO_COLOR text_color = opaquify(al_color_html("ffffff"));
   ALLEGRO_COLOR evidence_name_text_color = opaquify(al_color_html("ffffff"));
   ALLEGRO_COLOR evidence_name_text_dropshadow_color = opaquify(al_color_html("770000"));
   int evidence_bitmap_width = al_get_bitmap_width(evidence_bitmap);
   int evidence_bitmap_height = al_get_bitmap_height(evidence_bitmap);
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   //dialog_box_frame.set_fill_color(opaquify(al_color_html("2a2104")));
   //dialog_box_frame.set_border_color(opaquify(al_color_html("c49505")));
   dialog_box_frame.set_border_color(opaquify(ALLEGRO_COLOR{0.0, .75, 1.0, 1.0}));
   dialog_box_frame.set_backfill_color(opaquify(al_color_html("2a2c38")));
   AllegroFlare::Placement2D evidence_place(340, 292, evidence_bitmap_width, evidence_bitmap_height);
   //evidence_place.scale.x = 0.55;
   //evidence_place.scale.y = 0.55;

   // animations
   float reveal_counter = get_live_reveal_counter();
   evidence_place.position.y += ((1.0 - AllegroFlare::interpolator::fast_in(reveal_counter)) * 30);
   float scale_multiplier = 1.0;
   evidence_place.scale.x = evidence_place.scale.x * scale_multiplier;
   evidence_place.scale.y = evidence_place.scale.y * scale_multiplier;

   // draw the frame
   dialog_box_frame.render();

   // draw the notification text
   al_draw_text(
      notification_text_font,
      text_color,
      width/2,
      46,
      ALLEGRO_ALIGN_CENTER,
      notification_text.c_str()
   );

   // draw the evidence image
   evidence_place.start_transform();
   al_draw_tinted_bitmap(evidence_bitmap, fading_white, 0, 0, 0);
   evidence_place.restore_transform();

   // the collected evidence name
   float evidence_name_text_y_position = 180;//height/2 + 120;
   float column_gutter = 38;
   al_draw_text(
      evidence_name_text_font,
      evidence_name_text_color,
      width/2 + column_gutter/2,
      evidence_name_text_y_position,
      ALLEGRO_ALIGN_LEFT,
      evidence_name_text.c_str()
   );

   // the description paragraph
   float description_text_y_position = evidence_name_text_y_position + 80;
   std::string description_text = "The item was added to your [List of Evidence].  You can view the "
                                  "[List of Evidence] in the chronicle menu.";

   al_draw_multiline_text(
      evidence_description_font,
      evidence_name_text_color,
      width/2 + column_gutter/2,
      description_text_y_position,
      492,
      evidence_description_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      description_text.c_str()
   );

   return;
}

float YouGotEvidenceRenderer::get_live_reveal_counter()
{
   float local_age = get_age();
   float time_duration_to_reveal = 0.8;
   if (local_age >= time_duration_to_reveal) local_age = time_duration_to_reveal;
   float reveal_duration_normalized = 1.0 - ((time_duration_to_reveal - local_age) / time_duration_to_reveal);
   //return 0.5;
   return reveal_duration_normalized;
}

ALLEGRO_FONT* YouGotEvidenceRenderer::obtain_notification_text_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer::obtain_notification_text_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Regular.ttf -48";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}

ALLEGRO_FONT* YouGotEvidenceRenderer::obtain_evidence_name_text_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -42");
}

ALLEGRO_FONT* YouGotEvidenceRenderer::obtain_evidence_description_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -36");
}

ALLEGRO_COLOR YouGotEvidenceRenderer::opaquify(ALLEGRO_COLOR color)
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


