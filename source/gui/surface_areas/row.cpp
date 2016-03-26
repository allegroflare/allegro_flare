
#include <allegro_flare/gui/surface_areas/row.h>








FGUISurfaceAreaRow::FGUISurfaceAreaRow(float y, float h)
   : FGUISurfaceArea(0, y, 0, h)
{
}





void FGUISurfaceAreaRow::draw_bounding_area()
{
   
}





bool FGUISurfaceAreaRow::collides(float x, float y)
{
   if (y < placement.position.y) return false;
   if (y > placement.position.y + placement.size.y) return false;
   return true;
}

