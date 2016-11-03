



#include <allegro_flare/gui/widgets/camera.h>

#include <allegro_flare/gui/surface_areas/never_collide.h>




UICamera::UICamera(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UICamera", new UISurfaceAreaNeverCollide(x, y, w, h))
{}




