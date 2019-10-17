



#include <allegro_flare/slider.h>

#include <allegro_flare/allegro_flare.h>




UIVerticalSlider::UIVerticalSlider(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIVerticalSlider", new UISurfaceAreaBox(x, y, w, h))
   , val(0.6)
   , mouse_y(0)
   , num_notches(0)
   , wheel_sensitivity(0.1)
   , slider_color(color::dodgerblue)
{}




void UIVerticalSlider::on_draw()
{
   al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2));

   float hilight_inset = 1;
   al_draw_filled_rounded_rectangle(0+hilight_inset, place.size.y*(1.0-val)+hilight_inset,
      place.size.x-hilight_inset, place.size.y-hilight_inset, 3, 3, slider_color);
   al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::color(color::black, 0.2), 2);

   // draw the dividing line
   al_draw_line(0, place.size.y*(1-val), place.size.x, place.size.y*(1-val), color::color(color::black, 0.2), 1.0);
}




void UIVerticalSlider::set_notches(int num_notches)
{
   this->num_notches = num_notches;
}




void UIVerticalSlider::set_val_by_y(float y)
{
   set_val((place.size.y-y)/place.size.y);
}




void UIVerticalSlider::set_val(float val)
{
   val = limit<float>(0.0, 1.0, val);
   if (num_notches >= 3) val = (round_up(val * num_notches)) / (float)num_notches;
   this->val = limit<float>(0.0, 1.0, val);
   on_change();
}




void UIVerticalSlider::set_color(ALLEGRO_COLOR col)
{
   slider_color = col;
}




void UIVerticalSlider::on_mouse_move(float x, float y, float dx, float dy)
{
   place.transform_coordinates(&x, &y);
   mouse_y = y; // TODO: check, is setting the mouse_y directly appropriate for this?
}




void UIVerticalSlider::on_mouse_down()
{
   //if (mouse_over && Framework::current_event->mouse.button == 1) set_val_by_y(mouse_y);
   if (mouse_over)
   {
      set_val_by_y(mouse_y);
      //on_change();
   }
}




void UIVerticalSlider::on_drag(float x, float y, float dx, float dy)
{
   place.transform_coordinates(&x, &y);

   set_val_by_y(y);
   //on_change();
}




void UIVerticalSlider::on_mouse_wheel()
{
   if (focused) set_val(get_val() + Framework::current_event->mouse.dz * wheel_sensitivity);
}




void UIVerticalSlider::on_key_char()
{
   if (!focused) return;
   float increment_dist = 0.1;
   if (num_notches >= 3) increment_dist = 1.0 / num_notches;
   switch (Framework::current_event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         set_val(val + increment_dist);
         break;
      case ALLEGRO_KEY_DOWN:
         set_val(val - increment_dist);
         break;
   }
}




float UIVerticalSlider::get_val()
{
   return val;
}




float UIVerticalSlider::get_val(float min, float max)
{
   return (max-min) * val + min;
}




