



#include <allegro_flare/xy_controller.h>

#include <allegro_flare/box.h>
#include <allegro_flare/style_assets.h>
#include <AllegroFlare/Useful.hpp>




namespace allegro_flare
{
   UIXYController::UIXYController(UIWidget *parent, float x, float y, float w, float h)
      : UIWidget(parent, "UIXYController", new UISurfaceAreaBox(x, y, w, h))
      , mouse_pos(0)
      , marker(0.5, 0.5)
      , guide_color(AllegroFlare::color::white)
      , guide_opacity(0.3)
   {}




   void UIXYController::set_point(float x, float y)
   {
      AllegroFlare::vec2d prev_marker = marker;
      marker = AllegroFlare::vec2d(AllegroFlare::clamp<float>(0.0f, 1.0f, x), AllegroFlare::clamp<float>(0.0f, 1.0f, y));

      // check if there was a change
      if (AllegroFlare::basically_equal(marker.x, prev_marker.x) || !AllegroFlare::basically_equal(marker.y, prev_marker.y))
         on_change();
   }




   AllegroFlare::vec2d UIXYController::get_point()
   {
      return marker;
   }




   void UIXYController::on_mouse_down()
   {
      set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);   
   }




   void UIXYController::on_mouse_move(float x, float y, float dx, float dy)
   {
      place.transform_coordinates(&x, &y);
      mouse_pos = AllegroFlare::vec2d(x, y);

      if (mouse_down_on_over)
         set_point(mouse_pos.x / place.size.x, mouse_pos.y / place.size.y);   
   }




   void UIXYController::on_draw()
   {
      UIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, AllegroFlare::color::color(AllegroFlare::color::black, 0.1));

      // draw the guides
      AllegroFlare::vec2d local_marker = AllegroFlare::vec2d(marker.x * place.size.x, marker.y * place.size.y);

      al_draw_line(local_marker.x, 0, local_marker.x, place.size.y, AllegroFlare::color::color(AllegroFlare::color::white, guide_opacity), 1.0);
      al_draw_line(0, local_marker.y, place.size.x, local_marker.y, AllegroFlare::color::color(AllegroFlare::color::white, guide_opacity), 1.0);

      al_draw_circle(local_marker.x, local_marker.y, 10, AllegroFlare::color::color(AllegroFlare::color::dodgerblue, 0.2), 6);
   }




   void UIXYController::on_change()
   {
      this->send_message_to_parent("on_change");
   }
}




