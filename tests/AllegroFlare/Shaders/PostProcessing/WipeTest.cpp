
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/PostProcessing/Wipe.hpp>

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>


TEST(AllegroFlare_Shaders_PostProcessing_WipeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::PostProcessing::Wipe shader;
}


TEST(AllegroFlare_Shaders_PostProcessing_WipeTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::PostProcessing::Wipe shader;
   EXPECT_EQ("AllegroFlare/Shaders/PostProcessing/Wipe", shader.get_type());
}


TEST(AllegroFlare_Shaders_PostProcessing_WipeTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::PostProcessing::Wipe shader;
   EXPECT_EQ(AllegroFlare::Shaders::PostProcessing::Wipe::TYPE, shader.get_type());
}


TEST(AllegroFlare_Shaders_PostProcessing_WipeTest, initialize__will_work_without_blowing_up)
{
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Shaders::PostProcessing::Wipe *shader = new AllegroFlare::Shaders::PostProcessing::Wipe;
   shader->initialize(); // for now, we'll have to use a pointer due to the way it's structured (should fix eventually)
   delete shader;

   al_uninstall_system();
}


TEST(AllegroFlare_Shaders_PostProcessing_WipeTest, VISUAL__will_appear_as_expected)
{
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Shaders::PostProcessing::Wipe *shader = new AllegroFlare::Shaders::PostProcessing::Wipe;
   shader->initialize(); // for now, we'll have to use a pointer due to the way it's structured (should fix eventually)
   shader->set_direction("right");

   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.set_surface_width(al_get_display_width(display));
   render_surface.set_surface_height(al_get_display_height(display));
   render_surface.initialize();

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      // Render everything to our temporary render surface
      render_surface.set_as_target();
      // For now, just setting our surface as a color
      al_clear_to_color(ALLEGRO_COLOR{0.63, 0.9, 0.09, 1.0});

      float transition_playhead_position = (float)(i) / passes;
      shader->set_transition_playhead_position(transition_playhead_position);

      // Render our render surface to the backbuffer
      al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
      shader->activate();
      al_draw_bitmap(render_surface.obtain_surface(), 0, 0, 0);
      shader->deactivate();

      // Flip the display
      al_flip_display();
   }

   delete shader;

   al_uninstall_system();
}


