




#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/color.h>





#include <iostream>

FGUISurfaceAreaBox::FGUISurfaceAreaBox(float x, float y, float w, float h)
   : FGUISurfaceArea(x, y, w, h)
{
   //std::cout << "FGUISurfaceAreaBox()" << std::endl;
}



FGUISurfaceAreaBox::~FGUISurfaceAreaBox()
{
   //std::cout << "~FGUISurfaceAreaBox()" << std::endl;
}



bool FGUISurfaceAreaBox::collides(float x, float y)
{
   return placement.collide(x, y);
}



void FGUISurfaceAreaBox::draw_bounding_area()
{
   placement.draw_box(color::color(color::aliceblue, 0.2), true);
}


