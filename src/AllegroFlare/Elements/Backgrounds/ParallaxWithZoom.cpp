

#include <AllegroFlare/Elements/Backgrounds/ParallaxWithZoom.hpp>

#include <AllegroFlare/RepeatingBitmapLogic.hpp>
#include <AllegroFlare/Useful.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


ParallaxWithZoom::ParallaxWithZoom(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers, AllegroFlare::Camera2D* camera)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::TYPE)
   , layers(layers)
   , camera(camera)
{
}


ParallaxWithZoom::~ParallaxWithZoom()
{
}


void ParallaxWithZoom::set_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers)
{
   this->layers = layers;
}


void ParallaxWithZoom::set_camera(AllegroFlare::Camera2D* camera)
{
   this->camera = camera;
}


std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> ParallaxWithZoom::get_layers() const
{
   return layers;
}


AllegroFlare::Camera2D* ParallaxWithZoom::get_camera() const
{
   return camera;
}


void ParallaxWithZoom::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::render]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::render]: error: guard \"camera\" not met");
   }
   //camera->start_reverse_transform();

   //float camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left;
   //std::tie(camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left) =
         //camera.get_outermost_coordinates_trbl();

   //for (auto &layer : layers)
   //{
      //AllegroFlare::RepeatingBitmapLogic repeating_bitmap_logic(-3, -2, 3, 2);
      //repeating_bitmap_logic.fit_loop_width_to_bitmap_width();
      //repeating_bitmap_logic.fit_loop_height_to_bitmap_height();
   //}

   //AllegroFlare::Camera2D this_layer_camera = *camera;


   for (auto &layer : layers)
   {
      ALLEGRO_BITMAP *layer_bitmap = layer.get_bitmap();
      AllegroFlare::Camera2D this_layer_camera = *camera;
      this_layer_camera.position.x *= layer.get_offset_rate() + layer.get_anchor_x();
      this_layer_camera.position.y *= layer.get_offset_rate() + layer.get_anchor_y();

      this_layer_camera.start_reverse_transform();

      float camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left;
      std::tie(camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left) =
            this_layer_camera.get_outermost_coordinates_trbl();

      AllegroFlare::RepeatingBitmapLogic repeating_bitmap_logic(layer_bitmap, -1, -1, 1, 1);
      repeating_bitmap_logic.fit_loop_width_to_bitmap_width();
      repeating_bitmap_logic.fit_loop_height_to_bitmap_height();
      repeating_bitmap_logic.fit_rows_and_columns_to_frame(
            camera_frame_left,
            camera_frame_top,
            camera_frame_right,
            camera_frame_bottom
         );
      repeating_bitmap_logic.fit_placement_dimensions_to_bitmap_dimensions();
      //repeating_bitmap_logic.get_placement_ref().align = { 0.5, 0.5 };
      repeating_bitmap_logic.get_placement_ref().align = AllegroFlare::Vec2D{ 0.0, 0.0 }; // TODO: Figure out if/how
                                                                                          // this alignment needs to
                                                                                          // be applied

      //this_layer_camera.start_transform();
      repeating_bitmap_logic.draw_repeating_rows_and_columns();

      // Origin frame
      //al_draw_rectangle(0, 0, repeating_bitmap_logic.placement.x, repeating_bitmap_logic.placement.y);
      draw_crosshair(0, 0, 100); // Origin crosshair

      this_layer_camera.restore_transform();
   }


   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


