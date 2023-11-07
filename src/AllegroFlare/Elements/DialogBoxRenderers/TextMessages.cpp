

#include <AllegroFlare/Elements/DialogBoxRenderers/TextMessages.hpp>

#include <AllegroFlare/Elements/TextMessageBubble.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxRenderers
{


TextMessages::TextMessages(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string, float>> messages, float age, float phone_screen_width, float phone_screen_height)
   : font_bin(font_bin)
   , messages(messages)
   , age(age)
   , phone_screen_width(phone_screen_width)
   , phone_screen_height(phone_screen_height)
   , draw_background_fill(false)
{
}


TextMessages::~TextMessages()
{
}


void TextMessages::set_draw_background_fill(bool draw_background_fill)
{
   this->draw_background_fill = draw_background_fill;
}


bool TextMessages::get_draw_background_fill() const
{
   return draw_background_fill;
}


void TextMessages::render()
{
   //int line = 0;
   float dialog_box_height = 160;
   float dialog_box_spacing = dialog_box_height + 30;
   AllegroFlare::Placement2D dialog_bubble_placement;
   float window_padding = 30;
   float bubble_width = phone_screen_width - window_padding * 2;

   float window_roundness = 22;
   if (draw_background_fill)
   {
      al_draw_filled_rounded_rectangle(
         0,
         0,
         phone_screen_width,
         phone_screen_height,
         window_roundness,
         window_roundness,
         ALLEGRO_COLOR{0, 0.08, 0.1, 0.95}
      );
   }

   for (unsigned i=0; i<messages.size(); i++)
   {
      auto &message = messages[i];
      std::string message_sender = std::get<0>(message); // TODO: Incorporate this property
      std::string message_text = std::get<1>(message);
      float message_sent_at = std::get<2>(message);      // TODO: Incorporate this property

      float sanitized_age = build_sanitized_age();
      float y_reveal_offset = (1.0 - AllegroFlare::interpolator::tripple_fast_in(sanitized_age))
                            * 80
                            + (1.0 - AllegroFlare::interpolator::tripple_fast_in(sanitized_age))
                            * i * 20;
      float reveal_scale = AllegroFlare::interpolator::tripple_fast_in(sanitized_age);
      float y_position = i * dialog_box_spacing + y_reveal_offset + window_padding;
      //auto &message = messages[i];
      AllegroFlare::Placement2D dialog_bubble_placement{window_padding, y_position, 0, 0};
      dialog_bubble_placement.scale.y = 0.7 + reveal_scale * 0.3;

      dialog_bubble_placement.start_transform();
      AllegroFlare::Elements::TextMessageBubble dialog_bubble_element(
         font_bin,
         message_text,
         bubble_width,
         dialog_box_height,
         true
      );
        //- name: font_bin
        //- name: text
        //- name: width
        //- name: height
        //- name: callout_on_left

      dialog_bubble_element.render();
      dialog_bubble_placement.restore_transform();
   }
   return;
}

float TextMessages::build_sanitized_age()
{
   float sanitized_age = age;
   if (sanitized_age < 0.0) sanitized_age = 0.0f;
   if (sanitized_age >= 1.0) sanitized_age = 1.0f;
   return sanitized_age;
}


} // namespace DialogBoxRenderers
} // namespace Elements
} // namespace AllegroFlare


