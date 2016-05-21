


#include <allegro_flare/gui/surface_areas/column.h>






UISurfaceAreaColumn::UISurfaceAreaColumn(float x, float w)
   : UISurfaceArea(x, 0, w, 0)
{
}





void UISurfaceAreaColumn::draw_bounding_area()
{
   
}





bool UISurfaceAreaColumn::collides(float x, float y)
{
   if (x < placement.position.x) return false;
   if (x > placement.position.x + placement.size.x) return false;
   return true;
}

