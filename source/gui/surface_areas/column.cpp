


#include <allegro_flare/gui/surface_areas/column.h>






FGUISurfaceAreaColumn::FGUISurfaceAreaColumn(float x, float w)
   : FGUISurfaceArea(x, 0, w, 0)
{
}





void FGUISurfaceAreaColumn::draw_bounding_area()
{
   
}





bool FGUISurfaceAreaColumn::collides(float x, float y)
{
   if (x < placement.position.x) return false;
   if (x > placement.position.x + placement.size.x) return false;
   return true;
}

