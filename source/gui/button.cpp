



#include <allegro_flare/gui/widgets/button.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/style_assets.h>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/widget.h>
#include <allegro_flare/allegro_flare.h> // for Framework::time_now
#include <allegro_flare/color.h>




UIButton::UIButton(UIWidget *parent, float x, float y, float w, float h, std::string text)
   : UIWidget(parent, "UIButton", new UISurfaceAreaBox(x, y, w, h))
   , text(text)
   , content_alignment(0.5)
   , font(UIStyleAssets::get_ui_font())
   , icon(NULL)
{}




void UIButton::set_icon(ALLEGRO_BITMAP *icon)
{
   if (!icon) return;
   this->icon = icon;
}




void UIButton::set_content_alignment(float _content_alignment)
{
   content_alignment = _content_alignment;
}




void UIButton::on_draw()
{
   bool is_depressed = mouse_over && mouse_down_on_over;
   if (is_disabled()) UIStyleAssets::draw_flatset(0, 0, place.size.x, place.size.y, color::color(UIStyleAssets::get_surface_color(), 0.5));
   else if (is_depressed) UIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y);
   else UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);

   // draw a gloss along the top
   // al_draw_filled_rounded_rectangle(4, 4, place.size.x-4, 4+place.size.y/3, 4, 4, color::color(color::white, 0.05));

   // draw a soft hilight over the button if the mouse is over it
   if (!disabled)
      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 5, 5,
            color::mix(color::transparent, UIStyleAssets::get_hilight_color(), mouse_over * 0.1));


   // draw the icon and/or the text
   // in this case, the icon is always drawn to the left of the text
   // with a padding of 10px

   // get the width of the inner content
   float inner_content_width = 0;
   float start_x = 0;
   if (icon) inner_content_width += al_get_bitmap_width(icon); // the width of the icon
   if (font && !text.empty() && icon) inner_content_width += 10; // the padding between the icon and the text
   if (font && !text.empty()) inner_content_width += al_get_text_width(font, text.c_str());
   start_x = place.size.x * content_alignment - inner_content_width * content_alignment;

   // draw the stuff
   if (icon)
   {
      al_draw_bitmap(icon, start_x, place.size.y/2 - al_get_bitmap_height(icon)/2, ALLEGRO_FLAGS_EMPTY);
      start_x += al_get_bitmap_width(icon);
   }
   if (font && !text.empty() && icon)
   {
      start_x += 10;
   }
   if (font && !text.empty())
   {
      UIStyleAssets::draw_styled_text(is_disabled() ? "ui_disabled" : "ui", place.size.x/2, place.size.y/2 + is_depressed*1, 0.5, 0.5, text);
      /*
      al_draw_text(font, color::color(color::black, 0.4), start_x, placement.size.y/2-al_get_font_line_height(font)/2+1, ALLEGRO_ALIGN_LEFT, text.c_str());
      al_draw_text(font, color::white, start_x, placement.size.y/2-al_get_font_line_height(font)/2-1, ALLEGRO_ALIGN_LEFT, text.c_str());
      */
   }

   if (is_disabled())
   {
      draw_textured_rectangle(1, 1, place.size.x-2, place.size.y-2, UIStyleAssets::get_pixel_pattern_3(), color::color(color::white, 0.2));
      //al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3,
      //   color::mix(color::gray, color::transparent, 0.5));
   }
}




void UIButton::set_text(std::string text)
{
   this->text = text;
}




void UIButton::on_click()
{
   UIWidget::on_click();

   // automatic behavior for UIButton, will send an on_click to the parent when clicked this
   // represents a new use-friendly concept where widgets automatically send messages to their
   // parents for their most common purpose event.  In this case, a button. You click it.
   if (family.parent) family.parent->on_message(this, "on_click");
}




void UIButton::on_mouse_enter() {}




void UIButton::on_mouse_leave() {}




void UIButton::on_key_down()
{
   // NOTE! this is similar to the on_joy_down button too.
   if (!is_focused()) return;

   if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ENTER
         || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_SPACE
      )
   {
      on_click();
   }
}




void UIButton::on_joy_down()
{
   // NOTE! this is similar to the on_key_down button too.
   if (!mouse_over) return;

   if (Framework::current_event->joystick.button == 0)
   {
      on_click();
   }
}




