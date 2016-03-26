


#include <allegro_flare/gui/widgets/toggle_button.h>


#include <allegro_flare/allegro_flare.h> // for af::fonts

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/style_assets.h>





FGUIToggleButton::FGUIToggleButton(FGUIWidget *parent, float x, float y, float w, float h, std::string _text)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , pressed(false)
   , text(_text)
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIToggleButton");
   attr.set("id", "ToggleButton" + tostring(get_num_created_widgets()));
}




void FGUIToggleButton::set_text(std::string text)
{
   this->text = text;
}




bool FGUIToggleButton::toggle()
   // returns true if the button is pressed
{
   pressed = !pressed;
   on_change();
   return pressed;
}



bool FGUIToggleButton::set_as_pressed()
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



bool FGUIToggleButton::set_as_unpressed()
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



void FGUIToggleButton::silently_set_as_pressed()
{
   pressed = true;
}



void FGUIToggleButton::silently_set_as_unpressed()
{
   pressed = false;
}



bool FGUIToggleButton::is_pressed()
{
   return pressed;
}



void FGUIToggleButton::on_draw()
{
   if (pressed) FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y);
   else FGUIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);

   FGUIStyleAssets::draw_styled_text("ui", place.size.x/2, place.size.y/2 + (pressed ? 1 : 0),
      0.5, 0.5, text.c_str());
}




void FGUIToggleButton::on_click() { toggle(); }




void FGUIToggleButton::on_change()
{
   send_message_to_parent("on_change");
}



