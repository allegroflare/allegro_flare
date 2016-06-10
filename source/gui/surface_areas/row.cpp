



#include <allegro_flare/gui/surface_areas/row.h>




UISurfaceAreaRow::UISurfaceAreaRow(float y, float h)
   : UISurfaceArea(0, y, 0, h)
{
}




void UISurfaceAreaRow::draw_bounding_area()
{
}




bool UISurfaceAreaRow::collides(float x, float y)
{
   if (y < placement.position.y) return false;
   if (y > placement.position.y + placement.size.y) return false;
   return true;
}




