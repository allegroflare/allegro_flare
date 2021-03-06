



#include <allegro_flare/toggle_button.h>

#include <allegro_flare/box.h>
#include <allegro_flare/style_assets.h>
#include <allegro_flare/allegro_flare.h> // for af::fonts




namespace allegro_flare
{
   UIToggleButton::UIToggleButton(UIWidget *parent, float x, float y, float w, float h, std::string _text)
      : UIWidget(parent, "UIToggleButton", new UISurfaceAreaBox(x, y, w, h))
      , pressed(false)
      , text(_text)
   {}




   void UIToggleButton::set_text(std::string text)
   {
      this->text = text;
   }




   // returns true if the button is pressed
   bool UIToggleButton::toggle()
   {
      pressed = !pressed;
      on_change();
      return pressed;
   }




   // returns true if the state was changed,
   // returns false if it stayed the same
   bool UIToggleButton::set_as_pressed()
   {
      if (!pressed)
      {
         toggle();
         return true;
      }
      return false;
   }




   // returns true if the state was changed,
   // returns false if it stayed the same
   bool UIToggleButton::set_as_unpressed()
   {
      if (pressed)
      {
         toggle();
         return true;
      }
      return false;
   }




   void UIToggleButton::silently_set_as_pressed()
   {
      pressed = true;
   }




   void UIToggleButton::silently_set_as_unpressed()
   {
      pressed = false;
   }




   bool UIToggleButton::is_pressed()
   {
      return pressed;
   }




   void UIToggleButton::on_draw()
   {
      if (pressed) UIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y);
      else UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);

      UIStyleAssets::draw_styled_text("ui", place.size.x/2, place.size.y/2 + (pressed ? 1 : 0),
            0.5, 0.5, text.c_str());
   }




   void UIToggleButton::on_click() { toggle(); }




   void UIToggleButton::on_change()
   {
      send_message_to_parent("on_change");
   }
}




