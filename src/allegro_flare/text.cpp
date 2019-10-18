



#include <allegro_flare/text.h>

#include <allegro_flare/box.h>
#include <allegro_flare/allegro_flare.h> // for fonts
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>




namespace allegro_flare
{
   UIText::UIText(UIWidget *parent, float x, float y, std::string text)
      : UIWidget(parent, "UIText", new UISurfaceAreaBox(x, y, 200, 20)) // just set arbitrary width and height
      , text(text)
      , font(Framework::font("DroidSans.ttf 20"))
      , font_color(color::white)
   {
      // text elements do not recieve focus when ALLEGRO_KEY_TABbing
      no_focus = true;

      // unlike other widgets, text will always align left by default
      this->surface_area->placement.align.x = 0.0;

      // update the dimentions of the box
      place.size.x = al_get_text_width(font, text.c_str());
      place.size.y = al_get_font_line_height(font);
   }




   void UIText::on_draw()
   {
      al_draw_text(font, font_color, 0, 0, ALLEGRO_ALIGN_LEFT, text.c_str());
   }




   std::string UIText::get_text()
   {
      return text;
   }




   void UIText::set_font_and_text(ALLEGRO_FONT *font, std::string text)
   {
      this->text = text;
      this->font = font;
      place.size.x = al_get_text_width(font, text.c_str());
      place.size.y = al_get_font_line_height(font);
   }




   void UIText::set_text(std::string text)
   {
      set_font_and_text(this->font, text);
   }




   void UIText::set_font(ALLEGRO_FONT *font)
   {
      set_font_and_text(font, this->text);
   }




   void UIText::set_font_color(const ALLEGRO_COLOR &font_color)
   {
      this->font_color = font_color;
   }
}




