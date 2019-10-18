



#include <allegro_flare/draggable_region.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/box.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>




namespace allegro_flare
{
   std::string tostring(int v); // so as not to have to declare  #include <allegro_flare/useful.h>




   UIDraggableRegion::UIDraggableRegion(UIWidget *parent, float x, float y, float w, float h)
      : UIWidget(parent, "UIDraggableRegion", new UISurfaceAreaBox(x, y, w, h))
      , background_color(AllegroFlare::color::color(AllegroFlare::color::black, 0.1))
   {}




   void UIDraggableRegion::set_color(ALLEGRO_COLOR new_color)
   {
      background_color = new_color;
   }




   void UIDraggableRegion::on_draw()
   {
      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 5, 5, background_color);
   }




   void UIDraggableRegion::on_drag(float x, float y, float dx, float dy)
   {
      UIWidget *parent = static_cast<UIWidget *>(get_parent());
      if (parent)
      {
         // This might not be the best method, that is, directly controlling the parameters
         // of a parent object.  It might interfere with other events or other actions on
         // or around the parent's parameters.  For example, if the parent is being animated, etc.
         placement2d &parent_placement = parent->place;
         parent_placement.position.x += dx;
         parent_placement.position.y += dy;
      }
   }
}



