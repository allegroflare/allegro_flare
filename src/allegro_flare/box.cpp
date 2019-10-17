



#include <iostream>
#include <allegro_flare/box.h>
#include <AllegroFlare/Color.hpp>




UISurfaceAreaBox::UISurfaceAreaBox(float x, float y, float w, float h)
   : UISurfaceAreaBase(x, y, w, h)
{}




UISurfaceAreaBox::~UISurfaceAreaBox()
{}




bool UISurfaceAreaBox::collides(float x, float y)
{
   return placement.collide(x, y);
}




void UISurfaceAreaBox::draw_bounding_area()
{
   placement.draw_box(color::color(color::aliceblue, 0.2), true);
}




