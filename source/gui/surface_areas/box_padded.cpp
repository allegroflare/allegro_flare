



#include <iostream>
#include <allegro_flare/gui/surface_areas/box_padded.h>
#include <allegro_flare/color.h>




UISurfaceAreaBoxPadded::UISurfaceAreaBoxPadded(float x, float y, float w, float h, float pt, float pr, float pb, float pl)
   : UISurfaceArea(x, y, w, h)
   , padding_top(pt)
   , padding_right(pr)
   , padding_bottom(pb)
   , padding_left(pl)
{
}




UISurfaceAreaBoxPadded::~UISurfaceAreaBoxPadded()
{
}




bool UISurfaceAreaBoxPadded::collides(float x, float y)
{
   return placement.collide(x, y, padding_top, padding_right, padding_bottom, padding_left);
}




void UISurfaceAreaBoxPadded::draw_bounding_area()
{
   placement.draw_box_with_padding(color::color(color::aliceblue, 0.2), true,
      padding_top, padding_right, padding_bottom, padding_left);
}




void UISurfaceAreaBoxPadded::get_padding(float *pt, float *pr, float *pb, float *pl)
{
   *pt = padding_top;
   *pr = padding_right;
   *pb = padding_bottom;
   *pl = padding_left;
}




void UISurfaceAreaBoxPadded::set_padding(float pt, float pr, float pb, float pl)
{
   padding_top = pt;
   padding_right = pr;
   padding_bottom = pb;
   padding_left = pl;
}




