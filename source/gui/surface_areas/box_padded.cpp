




#include <allegro_flare/gui/surface_areas/box_padded.h>
#include <allegro_flare/color.h>





#include <iostream>

FGUISurfaceAreaBoxPadded::FGUISurfaceAreaBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl)
   : FGUISurfaceArea(x, y, w, h)
   , padding_top(pt)
   , padding_right(pr)
   , padding_bottom(pb)
   , padding_left(pl)
{
}



FGUISurfaceAreaBoxPadded::~FGUISurfaceAreaBoxPadded()
{
}



bool FGUISurfaceAreaBoxPadded::collides(float x, float y)
{
   return placement.collide(x, y, padding_top, padding_right, padding_bottom, padding_left);
}



void FGUISurfaceAreaBoxPadded::draw_bounding_area()
{
   placement.draw_box_with_padding(color::color(color::aliceblue, 0.2), true,
      padding_top, padding_right, padding_bottom, padding_left);
}



void FGUISurfaceAreaBoxPadded::get_padding(float *pt, float *pr, float *pb, float *pl)
{
   *pt = padding_top;
   *pr = padding_right;
   *pb = padding_bottom;
   *pl = padding_left;
}



void FGUISurfaceAreaBoxPadded::set_padding(float pt, float pr, float pb, float pl)
{
   padding_top = pt;
   padding_right = pr;
   padding_bottom = pb;
   padding_left = pl;
}




