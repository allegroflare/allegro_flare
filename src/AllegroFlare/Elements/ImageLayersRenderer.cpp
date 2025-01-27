

#include <AllegroFlare/Elements/ImageLayersRenderer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ImageLayersRenderer::ImageLayersRenderer(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers, AllegroFlare::Camera2D* camera)
   : image_layers(image_layers)
   , camera(camera)
{
}


ImageLayersRenderer::~ImageLayersRenderer()
{
}


void ImageLayersRenderer::set_image_layers(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers)
{
   this->image_layers = image_layers;
}


void ImageLayersRenderer::set_camera(AllegroFlare::Camera2D* camera)
{
   this->camera = camera;
}


std::vector<AllegroFlare::Elements::ImageLayer>* ImageLayersRenderer::get_image_layers() const
{
   return image_layers;
}


AllegroFlare::Camera2D* ImageLayersRenderer::get_camera() const
{
   return camera;
}


void ImageLayersRenderer::render()
{
   if (!(image_layers))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayersRenderer::render]: error: guard \"image_layers\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayersRenderer::render]: error: guard \"image_layers\" not met");
   }
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ImageLayersRenderer::render]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ImageLayersRenderer::render]: error: guard \"camera\" not met");
   }
   float camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left;
   std::tie(camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left) = 
      camera->get_outermost_coordinates_trbl();
   float camera_frame_width = camera_frame_right - camera_frame_left;
   float camera_frame_height = camera_frame_bottom - camera_frame_top;

   //for (auto &plane : planes_background->get_planes())
   for (auto &image_layer : *image_layers)
   {
      ALLEGRO_BITMAP *bitmap = image_layer.bitmap;
      if (!bitmap) continue;

      //AllegroFlare::Placement2D &placement = plane->get_placement_ref();
      float placement_x = image_layer.offset_x;
      float placement_y = image_layer.offset_y;

      //AllegroFlare::Vec2D parallax_rate = plane->get_parallax_rate();
      AllegroFlare::Vec2D parallax_rate = { image_layer.parallax_x, image_layer.parallax_y };
      //int pixel_scale = planes_background->get_bitmaps_cloned_and_owned_at_pixel_scale();

      int pixel_scale = image_layer.pixel_scale;

      int original_image_width = al_get_bitmap_width(bitmap);
      int original_image_height = al_get_bitmap_height(bitmap);
      float scaled_bitmap_width = original_image_width / pixel_scale;
      float scaled_bitmap_height = original_image_height / pixel_scale;

      if (scaled_bitmap_width <= 0.001) continue;
      if (scaled_bitmap_height <= 0.001) continue;

      /*
      float initial_x = camera->position.x - (camera->position.x * parallax_rate.x) + placement.position.x;
      float initial_y = camera->position.y - (camera->position.y * parallax_rate.y) + placement.position.y;
      int num_x_repeats = 1;
      int num_y_repeats = 1;

      if (plane->repeats_along_x_infinite())
      {
         // Determine how many times the bitmap needs to repeat along the x-axis
         //float initial_x = camera->position.x - (camera->position.x * parallax_rate.x) + placement.position.x;
         //float initial_y = camera->position.y - (camera->position.y * parallax_rate.y) + placement.position.y;
         // TODO: Replace this with better non-looping math;
         while (initial_x < camera_frame_left) initial_x += scaled_bitmap_width;
         while (initial_x > camera_frame_left) initial_x -= scaled_bitmap_width;
         num_x_repeats = std::ceil(camera_frame_width / scaled_bitmap_width) + 1;
      }

      if (plane->repeats_along_y_infinite())
      {
         //float initial_y = camera->position.y - (camera->position.y * parallax_rate.y) + placement.position.y;
         // TODO: Replace this with better non-looping math;
         while (initial_y < camera_frame_top) initial_y += scaled_bitmap_height;
         while (initial_y > camera_frame_top) initial_y -= scaled_bitmap_height;
         num_y_repeats = std::ceil(camera_frame_height / scaled_bitmap_height) + 1;
      }

      for (int y=0; y<num_y_repeats; y++)
      {
         for (int i=0; i<num_x_repeats; i++)
         {
            al_draw_scaled_bitmap(
               bitmap,
               0,
               0,
               original_image_width,
               original_image_height,
               initial_x + scaled_bitmap_width * i,
                  //camera->position.x - (camera->position.x * parallax_rate.x) + placement.position.x,
               initial_y + scaled_bitmap_height * y,
                  //camera->position.y - (camera->position.y * parallax_rate.y) + placement.position.y,
               scaled_bitmap_width,
               scaled_bitmap_height,
               0
            );
         }
      }
      */
   }
   return;
}


} // namespace Elements
} // namespace AllegroFlare


