



#include <allegro_flare/circle.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp> // for distance




namespace allegro_flare
{
   UISurfaceAreaCircle::UISurfaceAreaCircle(float x, float y, float r)
      : UISurfaceAreaBase(x, y, r*2, r*2)
   {}




   bool UISurfaceAreaCircle::collides(float x, float y)
   {
      placement.transform_coordinates(&x, &y);
      return distance(placement.size.x/2, placement.size.y/2, x, y) <= placement.size.x/2;
   }




   void UISurfaceAreaCircle::draw_bounding_area()
   {
      placement.start_transform();
      al_draw_circle(placement.size.x/2, placement.size.y/2, placement.size.x/2, color::color(color::aliceblue, 0.2), 3.0);
      placement.restore_transform();
   }
}



