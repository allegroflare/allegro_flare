


#include <allegro_flare/allegro_flare.h> // for bins

#include <allegro_flare/gui/widgets/scroll_area.h>
#include <allegro_flare/gui/widgets/slider.h>



FGUIScrollArea::FGUIScrollArea(FGUIWidget *parent, float x, float y, float w, float h, FGUIWidget *content_parent)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , canvas(content_parent)
   , v_slider(NULL)
   , canvas_render(al_create_bitmap(w, h))
{
   if (canvas) FGUIFamily::assign_child_to_new_parent(canvas, this); // I believe this usage is the proper design.

   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScrollArea");
   attr.set("id", "ScrollArea" + tostring(FGUIWidget::get_num_created_widgets()));

   v_slider = new FGUIScrollBar(this, w, 0, 16, h);
   v_slider->place.align = vec2d(1, 0);
}



FGUIWidget *FGUIScrollArea::get_canvas()
{
   return canvas;
}



void FGUIScrollArea::render_canvas()
{
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_TRANSFORM);

   ALLEGRO_TRANSFORM ident;
   al_identity_transform(&ident);
   al_use_transform(&ident);

   al_set_target_bitmap(canvas_render);
   al_clear_to_color(color::mix(color::coral, color::transparent, 1.0));


   canvas->draw_func();


   al_restore_state(&state);
}



void FGUIScrollArea::mouse_axes_func(float mx, float my, float mdx, float mdy)
{
   float tmx = mx;
   float tmy = my;
   float tmdx = mdx;
   float tmdy = mdy;

   if (!surface_area->collides(mx, my))
   {
      family.parent->mouse_is_blocked = true; // TODO: this works, but I don't think it's "correct"
                                              // e.g. what if there is no parent?
   }
   else
   {
      //std::cout << ".";
   }

   FGUIWidget::mouse_axes_func(tmx, tmy, tmdx, tmdy);
}



void FGUIScrollArea::on_timer()
{
   if (canvas)
      canvas->place.position.y = v_slider->get_position() * -(canvas->place.size.y-place.size.y);
   FGUIWidget::on_timer();
}



void FGUIScrollArea::on_mouse_wheel()
{
   //if (focused && !v_slider->is_focused())
   //   v_slider->set_val(v_slider->get_val() + af::current_event->mouse.dz * v_slider->wheel_sensitivity);
}



void FGUIScrollArea::draw_func()
{
   // render the canvas
   if (canvas) render_canvas();

   // draw the inset, canvas_render, and children, but do not draw the canvas child widget;
   place.start_transform();

   FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, color::color(color::black, 0.1));
   if (canvas) al_draw_bitmap(canvas_render, 0, 0, ALLEGRO_FLAGS_EMPTY);

   family.draw_all_except(canvas); // except the canvas?

   place.restore_transform();
}


