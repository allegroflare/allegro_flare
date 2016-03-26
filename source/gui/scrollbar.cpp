


#include <allegro_flare/gui/widgets/scrollbar.h>

#include <allegro5/allegro_primitives.h>

#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/useful.h> // for limit

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/style_assets.h>




FGUIScrollBar::UpButton::UpButton(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScrollBar::UpButton");
   attr.set("id", "ScrollBar::UpButton" + tostring(get_num_created_widgets()));

}
void FGUIScrollBar::UpButton::on_click()
{
   static_cast<FGUIScrollBar *>(family.parent)->step_up();
}
void FGUIScrollBar::UpButton::on_draw()
{
   FGUIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}



FGUIScrollBar::DownButton::DownButton(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScrollBar::DownButton");
   attr.set("id", "ScrollBar::DownButton" + tostring(get_num_created_widgets()));
}
void FGUIScrollBar::DownButton::on_click()
{
   static_cast<FGUIScrollBar *>(family.parent)->step_down();
}
void FGUIScrollBar::DownButton::on_draw()
{
   FGUIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}



FGUIScrollBar::Rail::Rail(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , current_mouse_y(0)
{}
void FGUIScrollBar::Rail::on_draw()
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::mix(color::transparent, color::hex("3a3c47"), 0.4));
   al_draw_rectangle(0.5, 0.5, place.size.x-0.5, place.size.y-0.5, color::color(color::black, 0.2), 1.0);
}
void FGUIScrollBar::Rail::on_mouse_move(float x, float y, float dx, float dy)
{
   current_mouse_y = y;
}
void FGUIScrollBar::Rail::on_click()
{
   // find the direction of the jump based on the handle's position
   FGUIScrollBar *slider_parent = static_cast<FGUIScrollBar *>(family.parent);
   if (slider_parent->handle->place.position.y < current_mouse_y) slider_parent->jump_down();   
   else slider_parent->jump_up();   
}



FGUIScrollBar::Handle::Handle(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , min_y(0)
   , max_y(0)
{
}
void FGUIScrollBar::Handle::set_min_max_coordinate_position(float min_val, float max_val)
{
   min_y = min_val;
   max_y = max_val;
}
void FGUIScrollBar::Handle::on_drag(float x, float y, float dx, float dy)
{
   place.position.y = limit<float>(min_y+place.size.y/2, max_y-place.size.y/2, place.position.y+dy);
   family.parent->on_change();
}
void FGUIScrollBar::Handle::on_draw()
{
   FGUIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
}
float FGUIScrollBar::Handle::get_position()
{
   return (place.position.y - min_y - place.size.y/2.0) / (max_y - min_y - place.size.y);
}
void FGUIScrollBar::Handle::set_position(float position_in_unit_value)
{
   // TODO: check and see if an on_change is necessairy
   // float previous_pos = place.position.y;

   float previous_pos = place.position.y;

   position_in_unit_value = limit<float>(0.0, 1.0, position_in_unit_value);
   float new_pos = position_in_unit_value * (max_y - min_y - place.size.y) + (min_y + place.size.y/2.0);
   place.position.y = new_pos; 

   if (place.position.y != previous_pos) family.parent->on_change();
}




FGUIScrollBar::FGUIScrollBar(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , rail(NULL)
   , handle(NULL)
   , up_button(NULL)
   , down_button(NULL)
{
   // create the rail
   rail = new FGUIScrollBar::Rail(this, 0, 0, w, h);
   rail->place.align = vec2d(0, 0);

   // create the up and down buttons
   up_button = new FGUIScrollBar::UpButton(this, w/2, w/2, w, w);
   down_button = new FGUIScrollBar::DownButton(this, w/2, h-w/2, w, w);

   // create the handle
   handle = new FGUIScrollBar::Handle(this, w/2, h/2, w, w*3);
   handle->set_min_max_coordinate_position(w, h-w);
}
float FGUIScrollBar::get_position()
{
   return handle->get_position();
}
void FGUIScrollBar::jump_down()
{
   float jump_rate = 0.3;
   set_position(handle->get_position() + jump_rate);
}
void FGUIScrollBar::jump_up()
{
   float jump_rate = 0.3;
   set_position(handle->get_position() - jump_rate);
}
void FGUIScrollBar::step_up()
{
   float step_rate = 0.1;
   set_position(handle->get_position() - step_rate);
}
void FGUIScrollBar::step_down()
{
   float step_rate = 0.1;
   set_position(handle->get_position() + step_rate);
}
void FGUIScrollBar::set_position(float position_in_unit_value)
{
   handle->set_position(position_in_unit_value);
   on_change();
}
void FGUIScrollBar::on_key_down()
{
   if (af::current_event->keyboard.keycode == ALLEGRO_KEY_DOWN) step_down();
   else if (af::current_event->keyboard.keycode == ALLEGRO_KEY_UP) step_up();
}
void FGUIScrollBar::on_draw() {}
void FGUIScrollBar::on_change()
{
   send_message_to_parent("on_change");
}




