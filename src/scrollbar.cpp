



#include <allegro_flare/scrollbar.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/box.h>
#include <allegro_flare/style_assets.h>
#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/useful.h> // for limit




UIScrollBar::UpButton::UpButton(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIScrollBar::UpButton", new UISurfaceAreaBox(x, y, w, h))
{}




void UIScrollBar::UpButton::on_click()
{
   static_cast<UIScrollBar *>(get_parent())->step_up();
}




void UIScrollBar::UpButton::on_draw()
{
   UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}




UIScrollBar::DownButton::DownButton(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIScrollBar::DownButton", new UISurfaceAreaBox(x, y, w, h))
{}




void UIScrollBar::DownButton::on_click()
{
   static_cast<UIScrollBar *>(get_parent())->step_down();
}




void UIScrollBar::DownButton::on_draw()
{
   UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}




UIScrollBar::Rail::Rail(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIScrollBar::Rail", new UISurfaceAreaBox(x, y, w, h))
   , current_mouse_y(0)
{}




void UIScrollBar::Rail::on_draw()
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::mix(color::transparent, color::hex("3a3c47"), 0.4));
   al_draw_rectangle(0.5, 0.5, place.size.x-0.5, place.size.y-0.5, color::color(color::black, 0.2), 1.0);
}




void UIScrollBar::Rail::on_mouse_move(float x, float y, float dx, float dy)
{
   current_mouse_y = y;
}




void UIScrollBar::Rail::on_click()
{
   // find the direction of the jump based on the handle's position
   UIScrollBar *slider_parent = static_cast<UIScrollBar *>(get_parent());
   if (slider_parent->handle->place.position.y < current_mouse_y) slider_parent->jump_down();   
   else slider_parent->jump_up();   
}




UIScrollBar::Handle::Handle(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIScrollBar::Handle", new UISurfaceAreaBox(x, y, w, h))
   , min_y(0)
   , max_y(0)
{
}




void UIScrollBar::Handle::set_min_max_coordinate_position(float min_val, float max_val)
{
   min_y = min_val;
   max_y = max_val;
}




void UIScrollBar::Handle::on_drag(float x, float y, float dx, float dy)
{
   place.position.y = limit<float>(min_y+place.size.y/2, max_y-place.size.y/2, place.position.y+dy);
   if (has_parent()) static_cast<UIWidget *>(get_parent())->on_change();
}




void UIScrollBar::Handle::on_draw()
{
   UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}




float UIScrollBar::Handle::get_position()
{
   return (place.position.y - min_y - place.size.y/2.0) / (max_y - min_y - place.size.y);
}




void UIScrollBar::Handle::set_position(float position_in_unit_value)
{
   // TODO: check and see if an on_change is necessairy
   // float previous_pos = place.position.y;

   float previous_pos = place.position.y;

   position_in_unit_value = limit<float>(0.0, 1.0, position_in_unit_value);
   float new_pos = position_in_unit_value * (max_y - min_y - place.size.y) + (min_y + place.size.y/2.0);
   place.position.y = new_pos; 

   if ((place.position.y != previous_pos) && (has_parent())) static_cast<UIWidget *>(get_parent())->on_change();
}




UIScrollBar::UIScrollBar(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIScrollBar", new UISurfaceAreaBox(x, y, w, h))
   , rail(NULL)
   , handle(NULL)
   , up_button(NULL)
   , down_button(NULL)
{
   // create the rail
   rail = new UIScrollBar::Rail(this, 0, 0, w, h);
   rail->place.align = vec2d(0, 0);

   // create the up and down buttons
   up_button = new UIScrollBar::UpButton(this, w/2, w/2, w, w);
   down_button = new UIScrollBar::DownButton(this, w/2, h-w/2, w, w);

   // create the handle
   handle = new UIScrollBar::Handle(this, w/2, h/2, w, w*3);
   handle->set_min_max_coordinate_position(w, h-w);
}




float UIScrollBar::get_position()
{
   return handle->get_position();
}




void UIScrollBar::jump_down()
{
   float jump_rate = 0.3;
   set_position(handle->get_position() + jump_rate);
}




void UIScrollBar::jump_up()
{
   float jump_rate = 0.3;
   set_position(handle->get_position() - jump_rate);
}




void UIScrollBar::step_up()
{
   float step_rate = 0.1;
   set_position(handle->get_position() - step_rate);
}




void UIScrollBar::step_down()
{
   float step_rate = 0.1;
   set_position(handle->get_position() + step_rate);
}




void UIScrollBar::set_position(float position_in_unit_value)
{
   handle->set_position(position_in_unit_value);
   on_change();
}




void UIScrollBar::on_key_down()
{
   if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_DOWN) step_down();
   else if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_UP) step_up();
}




void UIScrollBar::on_draw() {}




void UIScrollBar::on_change()
{
   send_message_to_parent("on_change");
}




