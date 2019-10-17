



#include <allegro_flare/camera.h>

#include <allegro_flare/never_collide.h>




UICamera::UICamera(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UICamera", new UISurfaceAreaNeverCollide(x, y, w, h))
{}




void UICamera::on_message(UIWidget *sender, std::string message)
{
   send_message_to_parent(message, sender);
}




