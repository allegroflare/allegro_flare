



#include <allegro_flare/music_notation.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/box.h>
#include <allegro_flare/drawing_interface_allegro5.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>




namespace allegro_flare
{
   UIMusicNotation::UIMusicNotation(UIWidget *parent, float x, float y)
      : UIWidget(parent, "UIMusicNotation", new UISurfaceAreaBox(x, y, 300, 80))
      , notation(new DrawingInterfaceAllegro5())
      , val("")
   {}




   void UIMusicNotation::set_val(std::string _val)
   {
      val = _val;
   }




   std::string UIMusicNotation::get_val()
   {
      return val;
   }




   void UIMusicNotation::on_draw()
   {
      placement2d &place = this->surface_area->placement;
      al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::white, mouse_over ? 0.2 : 0.1));
      place.size.x = std::max(10, notation.draw(0, place.size.y/2, val));
   }
}



