


#include <allegro_flare/gui/widgets/toggle_button.h>


#include <allegro_flare/allegro_flare.h> // for af::fonts

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/style_assets.h>





UIToggleButton::UIToggleButton(UIWidget *parent, float x, float y, float w, float h, std::string _text)
   : UIWidget(parent, new UISurfaceAreaBox(x, y, w, h))
   , pressed(false)
   , text(_text)
{
   attr.set(UI_ATTR__UI_WIDGET_TYPE, "UIToggleButton");
   attr.set("id", "ToggleButton" + tostring(get_num_created_widgets()));
}




void UIToggleButton::set_text(std::string text)
{
   this->text = text;
}




bool UIToggleButton::toggle()
   // returns true if the button is pressed
{
   pressed = !pressed;
   on_change();
   return pressed;
}



bool UIToggleButton::set_as_pressed()
   // returns true if the state was changed,
   // returns false if it stayed the same
{
   if (!pressed)
   {
      toggle();
      return true;
   }
   return false;
}



bool UIToggleButton::set_as_unpressed()
   // returns true if the state was changed,
   // returns false if it stayed the same
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



