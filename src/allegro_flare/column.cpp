



#include <allegro_flare/column.h>




UISurfaceAreaColumn::UISurfaceAreaColumn(float x, float w)
   : UISurfaceAreaBase(x, 0, w, 1)
{
   placement.align = vec2d(0, 0);
}




void UISurfaceAreaColumn::draw_bounding_area()
{
}




bool UISurfaceAreaColumn::collides(float x, float y)
{
   placement.transform_coordinates(&x, &y);
   if (x < placement.position.x) return false;
   if (x > placement.position.x + placement.size.x) return false;
   return true;
}




