



#include <iostream>
#include <allegro_flare/gui/surface_areas/always_collide.h>




UISurfaceAreaAlwaysCollide::UISurfaceAreaAlwaysCollide()
   : UISurfaceArea(0, 0, 1, 1)
{}




UISurfaceAreaAlwaysCollide::~UISurfaceAreaAlwaysCollide()
{}




bool UISurfaceAreaAlwaysCollide::collides(float x, float y)
{
   (void)x;
   (void)y;
   return true;
}




void UISurfaceAreaAlwaysCollide::draw_bounding_area()
{}




