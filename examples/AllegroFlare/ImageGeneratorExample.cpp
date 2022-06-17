



//
// examples/AllegroFlare/ImageGeneratorExample.cpp
//
// This example demonstrates some textures that are generated proceedurally.  These
// are "design primitives" that you might used to create more ellaborate graphical
// assets.
//




#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/ImageGenerator.hpp>




class ImageGeneratorExample : public AllegroFlare::Screen
{
private:
   AllegroFlare::ImageGenerator image_generator;
   ALLEGRO_BITMAP *circle_render;
   ALLEGRO_BITMAP *gradient_render;
   ALLEGRO_BITMAP *circle_gradient;
   ALLEGRO_BITMAP *wood_texture;
   ALLEGRO_BITMAP *noise_texture;
   ALLEGRO_BITMAP *brush_metal_texture;
   bool initialized;

public:
   ImageGeneratorExample()
      : AllegroFlare::Screen()
      , image_generator()
      , circle_render(NULL)
      , gradient_render(NULL)
      , circle_gradient(NULL)
      , wood_texture(NULL)
      , noise_texture(NULL)
      , brush_metal_texture(NULL)
      , initialized(false)
   {}

   void initialize()
   {
      //al_set_window_title(display->al_display, "Generated Images Test");

      circle_render = image_generator.generate_circle_bitmap(128);
      gradient_render = image_generator.generate_gradient_bitmap(128, AllegroFlare::color::springgreen, AllegroFlare::color::deeppink);
      circle_gradient = image_generator.generate_circle_gradient_bitmap(128, AllegroFlare::color::mediumvioletred, AllegroFlare::color::red);
      noise_texture = image_generator.generate_noise_bitmap(128, 128);
      wood_texture = image_generator.generate_wood_grain_bitmap(128, 128);
      brush_metal_texture = image_generator.generate_brush_metal_bitmap(128, 128);
   }

   void primary_timer_func() override
   {
      al_draw_bitmap(circle_render, 200, 100, 0);
      al_draw_bitmap(gradient_render, 400, 100, 0);
      al_draw_bitmap(circle_gradient, 600, 100, 0); // appears to not be working as expected
      al_draw_bitmap(noise_texture, 200, 300, 0);
      al_draw_bitmap(wood_texture, 400, 300, 0);
      al_draw_bitmap(brush_metal_texture, 600, 300, 0);
   }
};




int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   // create the screen where our example program exists
   ImageGeneratorExample image_generator_example;
   image_generator_example.initialize();

   // register the screen to the system
   framework.register_screen(&image_generator_example);

   // run the loop
   framework.run_loop();
}



