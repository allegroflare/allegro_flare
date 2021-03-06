



#include <allegro_flare/window.h>

#include <allegro_flare/style_assets.h>
#include <allegro_flare/box.h>
#include <allegro_flare/allegro_flare.h> // for tostring and Framework:: bins




namespace allegro_flare
{
   UIWindow::UIWindow(UIWidget *parent, float x, float y, float w, float h)
      : UIWidget(parent, "UIWindow", new UISurfaceAreaBox(x, y, w, h))
      , background_color(AllegroFlare::color::hex("3a3c47"))
   {
      no_focus = true;
   }




   void UIWindow::on_draw()
   {
      UIStyleAssets::draw_outset(0, 0, place.size.x, place.size.y);
      AllegroFlare::draw_textured_rectangle(1, 1, place.size.x-1, place.size.y-1, Framework::bitmap("rough.jpg"), AllegroFlare::color::color(AllegroFlare::color::white, 0.1));
   }




   void UIWindow::on_focus()
   {
      if (bring_to_front_on_focus) bring_to_front();
   }




   void UIWindow::set_bring_to_front_on_focus(bool val)
   {
      bring_to_front_on_focus = val;
   }
}




