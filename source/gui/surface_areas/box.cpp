



#include <iostream>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/color.h>




UISurfaceAreaBox::UISurfaceAreaBox(float x, float y, float w, float h)
   : UISurfaceArea(x, y, w, h)
{
   //std::cout << "UISurfaceAreaBox()" << std::endl;
}




UISurfaceAreaBox::~UISurfaceAreaBox()
{
   //std::cout << "~UISurfaceAreaBox()" << std::endl;
}




bool UISurfaceAreaBox::collides(float x, float y)
{
   return placement.collide(x, y);
}




void UISurfaceAreaBox::draw_bounding_area()
{
   placement.draw_box(color::color(color::aliceblue, 0.2), true);
}




