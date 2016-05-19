



#include <allegro_flare/gui/widgets/checkbox.h>


#include <allegro5/allegro_primitives.h>

#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/fonts/font_font_awesome.h>
#include <allegro_flare/color.h>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/style_assets.h>





FGUICheckbox::FGUICheckbox(FGUIWidget *parent, float x, float y, float size)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, size, size))
   , checked(false)
   , check_placement(0, 0, size, size, -0.4, 0.0, 0.0, 0.45, 0.75)
   , check_color(color::mix(FGUIStyleAssets::get_hilight_color(), color::white, 0.6))
   , check_opacity(0)
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUICheckbox");
   attr.set("id", "Checkbox" + tostring(FGUIWidget::get_num_created_widgets()));
}



bool FGUICheckbox::is_checked()
{
   return checked;
}



void FGUICheckbox::set_color(ALLEGRO_COLOR col)
{
   check_color = col;
}



void FGUICheckbox::toggle()
{
   checked = !checked;

   float speed = 0.2;
   if (checked)
   {
      // check reveals
      Framework::motion.cmove_to(&check_opacity, 1.0, speed * 0.5, interpolator::doubleFastIn);
      Framework::motion.cmove_to(&check_placement.scale.x, 1.0, speed*0.85, interpolator::fastOut);
      Framework::motion.cmove_to(&check_placement.scale.y, 1.0, speed*0.85, interpolator::fastOut);
      Framework::motion.cmove_to(&check_placement.rotation, -0.1, speed, interpolator::fastOut);
   }
   else
   {
      // check removes
      Framework::motion.cmove_to(&check_opacity, 0.0, speed, interpolator::doubleFastOut);
      Framework::motion.cmove_to(&check_placement.scale.x, 0.0, speed, interpolator::slowIn);
      Framework::motion.cmove_to(&check_placement.scale.y, 0.0, speed, interpolator::slowIn);
      Framework::motion.cmove_to(&check_placement.rotation, -0.4, speed, interpolator::linear);
   }

   on_change();
}



bool FGUICheckbox::set_as_checked()
{
   // returns true if the value is or was changed to checked
   // the behavior for these return values might change based on some
   // future experience
   if (checked) return true;
   toggle();
   return is_checked();
}


bool FGUICheckbox::set_as_unchecked()
{
   // returns true if the value IS or WAS CHANGED TO unchecked
   // the behavior for these return values might change based on some
   // future experience
   if (!checked) return true;
   toggle();
   return !is_checked();
}



void FGUICheckbox::on_click()
{
   toggle();
}



void FGUICheckbox::on_key_char()
{
   if (!focused) return;
   if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_SPACE
      || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ENTER)
   {
      toggle();
   }
}



void FGUICheckbox::on_joy_down()
{
   if (!mouse_over) return;

   // TODO: this should not be hard-coded as button 0, it should be coded
   // as the "ENTER" button or "ACTIVATE" or whatever in the joystick config
   if (Framework::current_event->joystick.button == 0)
      toggle();
}



void FGUICheckbox::on_draw()
{
   float check_inset = place.size.x*0.2;   


   // draw the background shape
   FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, color::color(color::black, 0.1));


   // draw the gradient
   ALLEGRO_BITMAP *shade_down = FGUIStyleAssets::get_shade_down_gradient();
   al_draw_tinted_scaled_bitmap(shade_down, color::color(color::white, 0.3), 0, 0, al_get_bitmap_width(shade_down), al_get_bitmap_height(shade_down),
         check_inset, check_inset, place.size.x-check_inset*2, place.size.y-check_inset*2, ALLEGRO_FLIP_VERTICAL);


   // draw the check
   ALLEGRO_FONT *font_awesome = Framework::fonts["FontAwesome.otf " + tostring(((int)(place.size.x*1.75)))];

   static ALLEGRO_USTR *ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, font_awesome::ok);
   check_placement.position.x = place.size.x/2 + place.size.x*0.1;
   check_placement.position.y = place.size.y/2 + place.size.y*0.3;
   check_placement.size.x = al_get_ustr_width(font_awesome, ustr);
   check_placement.size.y = al_get_font_line_height(font_awesome);
   
   if (checked)
   {
      float boxfade_opacity = 1.0 - check_opacity;
      al_draw_filled_rectangle(check_inset, check_inset, place.size.x-check_inset, place.size.y-check_inset, color::color(check_color, boxfade_opacity));
   }
   check_placement.start_transform();

   al_draw_ustr(font_awesome, color::color(color::black, 0.3), 0, 3, ALLEGRO_FLAGS_EMPTY, ustr);
   al_draw_ustr(font_awesome, check_color, 0, 0, ALLEGRO_FLAGS_EMPTY, ustr);

   check_placement.restore_transform();
}



void FGUICheckbox::on_change()
{
   send_message_to_parent("on_change");
}


