



#include <allegro_flare/gui/widget.h>

#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/family.h>
#include <allegro_flare/gui/style_assets.h>
#include <allegro_flare/allegro_flare.h>




UIWidget::UIWidget(UIWidget *parent, UISurfaceArea *surface_area)
   : family(parent)
   , surface_area(surface_area)
   , place(surface_area->placement)
   , mouse_down_on_over(false)
   , mouse_over(false)
   , focused(false)
   , dragging(false)
   , no_focus(false)
   , delete_me(false)
   , mouse_is_blocked(false)
   , disabled(false)
{
   attr.set(UI_ATTR__UI_WIDGET_TYPE, "UIWidget");
   attr.set("id", "Widget" + tostring(widget_count));

   if (parent) parent->family.register_as_child(this);
   num_active_widgets++;
   widget_count++;
}




UIWidget::~UIWidget()
{
   family.delete_all(); // from UIParent

   if (surface_area) delete surface_area;
   if (family.parent) family.parent->family.unregister_as_child(this);
   num_active_widgets--;

   // std::cout << "~UIWidget() { type=" << attr.get(UI_ATTR__UI_WIDGET_TYPE) << " }" << std::endl;

   // clear all elements from the motion manager
   // I'm not sure about this.  There isn't really a fast, elegant way to guarantee
   // that all attributes that are potentialy being Motion.animated on are disabled
   // so there aren't any dangling pointers.  This is an attempt to offer one type
   // of solution, but it only covers the widget.placement elements.

   if (surface_area)
   {
      float* _elem[] = {
         &surface_area->placement.position.x, &surface_area->placement.position.y,
         &surface_area->placement.size.x, &surface_area->placement.size.y,
         &surface_area->placement.scale.x, &surface_area->placement.scale.y,
         &surface_area->placement.anchor.x, &surface_area->placement.anchor.y,
         &surface_area->placement.rotation
      };

      std::vector<float*> pacement_elements (_elem, _elem + sizeof(_elem) / sizeof(float*) );
      Framework::motion().clear_animations_on(pacement_elements);
   }
}




bool UIWidget::is_focused()
{
   return focused;
}




bool UIWidget::is_mouse_over()
{
   return mouse_over;
}




bool UIWidget::is_disabled()
{
   return disabled;
}




void UIWidget::bring_to_front()
{
   if (!family.parent) return;
   // hmm.. the logic of this should be executed by the parent, not this child
   // TODO: this function should simply call something like family->bring_to_front(this)
   // and not all this stuff:
   for (unsigned i=0; i<family.parent->family.children.size(); i++)
   {
      if (family.parent->family.children[i] == this)
      {
         family.parent->family.children.erase(family.parent->family.children.begin() + i);
         family.parent->family.children.push_back(this);
         return;
      }
   }
}




void UIWidget::send_message_to_parent(std::string message)
{
   if (disabled) return;

   if (family.parent) family.parent->on_message(this, message);
}




void UIWidget::primary_timer_func()
{
   if (disabled) return;

   on_timer();

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->primary_timer_func();

   // delete the widgets who request deletion
   for (unsigned i=0; i<family.children.size(); i++)
   {
      if (family.children[i]->delete_me)
      {
         std::cout << "Deleting child object...";
         // NOTE: when a UIWidget is deleted, it automatically
         // removes itself from the parent, so that step
         // does not need to be done here.  Also, widgets will
         // automatically delete thier children as well.
         delete family.children[i];
         std::cout << "deleted." << std::endl;
         i--;
      }
   }
}




void UIWidget::draw_func()
{
   if (surface_area) surface_area->placement.start_transform();

   on_draw();

   family.draw_all(); // TODO: should be renamed to draw_children();

   // draws the focus rectangle if it's focused
   /*
   if (focused && gimmie_super_screen()->draw_focused_outline)
   {
      al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 3, 3, color::color(color::black, 0.2), 5);
      al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 3, 3, color::mix(gimmie_super_screen()->focused_outline_color, color::purple, 0.6+0.4*sin(Framework::time_now*3)), 1.5);
   }
   */

   if (surface_area) surface_area->placement.restore_transform();

   // draws the collision shape (for debugging)
   //surface_area->draw_bounding_area();
}




// widget developer functions:
void UIWidget::mouse_axes_func(float x, float y, float dx, float dy)
{
   if (disabled) return;

   // start by transforming the coordinates for the children

   float tmx = x;
   float tmy = y;
   float tmdx = dx;
   float tmdy = dy;

   surface_area->placement.transform_coordinates(&tmx, &tmy);
   surface_area->placement.transform_coordinates(&tmdx, &tmdy);

   if (family.parent && family.parent->mouse_is_blocked) mouse_is_blocked = true;
   else mouse_is_blocked = false;

   for (int i=(int)family.children.size()-1; i>=0; i--)
      family.children[i]->mouse_axes_func(tmx, tmy, dx, dy);  // I'm not sure why these are dx/dy, but it works correctly this way


   // then proceed with the execution of the function

   if (surface_area)
   {
      bool mouse_over_now = surface_area->collides(x, y);
      if (family.parent && family.parent->mouse_is_blocked) mouse_over_now = false;

      if (mouse_over_now && !mouse_over) on_mouse_enter();
      else if (!mouse_over_now && mouse_over) on_mouse_leave();

      mouse_over = mouse_over_now;
      if (family.parent && mouse_over) family.parent->mouse_is_blocked = true;
   }

   on_mouse_move(x, y, dx, dy); // TODO I think this needs to be the translated coordinates, and maybe even should be on the on_drag() call below as well
   if (mouse_down_on_over)
   {
      dragging = true;
      on_drag(x, y, dx, dy);
   }

   if (Framework::current_event->mouse.dz != 0 || Framework::current_event->mouse.dw != 0) on_mouse_wheel();
}




void UIWidget::mouse_down_func()
{
   if (disabled) return;

   // call this function on the children first
   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->mouse_down_func();

   // now do the execution of the function
   if (mouse_over)
   {
      mouse_down_on_over = true;
      on_mouse_down();
      focused = true;
      on_focus();
   }
   else
   {
      if (focused)
      {
         focused = false;
         on_blur();
      }
   }
}




void UIWidget::mouse_up_func()
{
   if (disabled) return;

   // call this function on the children first
   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->mouse_up_func();

   // then continue with the function on self
   if (mouse_over && mouse_down_on_over)
   {
      on_click();
   }
   mouse_down_on_over = false;
   if (dragging)
   {
      dragging = false;
      on_drop();
   }
   on_mouse_up();
}




void UIWidget::key_down_func()
{
   if (disabled) return;

   // call this function on the children first
   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->key_down_func();

   // then call on self
   on_key_down();
}




void UIWidget::key_up_func()
{
   if (disabled) return;

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->key_up_func();

   on_key_up();
}




void UIWidget::key_char_func()
{
   if (disabled) return;

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->key_char_func();

   on_key_char();
}




void UIWidget::joy_up_func()
{
   if (disabled) return;

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->joy_up_func();

   on_joy_up();
}




void UIWidget::joy_axis_func()
{
   if (disabled) return;

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->joy_axis_func();

   on_joy_axis();
}




void UIWidget::joy_down_func()
{
   if (disabled) return;

   for (unsigned i=0; i<family.children.size(); i++)
      family.children[i]->joy_down_func();


   if (mouse_over && Framework::current_event->joystick.button == 0)
   {
      set_as_focused();
   }

   on_joy_down();
}




// user functions:
void UIWidget::on_focus() {}
void UIWidget::on_blur() {}
void UIWidget::on_drop() {}
void UIWidget::on_mouse_enter() {}
void UIWidget::on_mouse_leave() {}
void UIWidget::on_mouse_move(float x, float y, float dx, float dy) {}
void UIWidget::on_mouse_down() {}
void UIWidget::on_mouse_up() {}
void UIWidget::on_mouse_wheel() {}
void UIWidget::on_click() {}
void UIWidget::on_key_down() {}
void UIWidget::on_key_up() {}
void UIWidget::on_key_char() {}
void UIWidget::on_joy_down() {}
void UIWidget::on_joy_up() {}
void UIWidget::on_joy_axis() {}
void UIWidget::on_timer() {}




void UIWidget::on_draw()
{
   if (surface_area)
   {
      al_draw_rounded_rectangle(0, 0, surface_area->placement.size.x, surface_area->placement.size.y, 4, 4, color::color(color::aliceblue, 0.2), 2.0);
      ALLEGRO_BITMAP *widget_icon = UIStyleAssets::get_widget_icon();
      al_draw_tinted_bitmap(widget_icon, color::color(color::white, 0.1), place.size.x/2-al_get_bitmap_width(widget_icon)/2, place.size.y/2-al_get_bitmap_height(widget_icon)/2, 0);
   }
}




void UIWidget::on_drag(float x, float y, float dx, float dy) {}
void UIWidget::on_change() {}
void UIWidget::on_message(UIWidget *sender, std::string message) {};




int UIWidget::num_active_widgets = 0;




int UIWidget::widget_count = 0;




int UIWidget::get_num_created_widgets()
{
   return widget_count;
}




int UIWidget::get_num_active_widgets()
{
   return num_active_widgets;
}




// iterates through all siblings and sets all parent's children to unfocused.
// if the widget is not already focused, then set to focused and on_focus() is called
void UIWidget::set_as_focused()
{
   if (disabled) return;
   // todo: this might require that the superparent is iterated
   if (family.parent) family.parent->family.set_focus_to_child(this);
}




// if the widget is currently focused, chages the state to !focused and calls on_blur().
void UIWidget::set_as_unfocused()
{
   if (disabled) return;

   if (is_focused())
   {
      focused=false;
      on_blur();
   }
}




void UIWidget::set_as_disabled()
{
   if (disabled) return; // no change

   if (focused) set_as_unfocused();
   disabled = true;
}




void UIWidget::set_as_enabled()
{
   if (!disabled) return; // no change

   disabled = false;
}




