
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/PostProcessing/DipToBlack.hpp>

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>
#include <allegro5/allegro_color.h> // For al_color_name


TEST(AllegroFlare_Shaders_PostProcessing_DipToBlackTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::PostProcessing::DipToBlack shader;
}


TEST(AllegroFlare_Shaders_PostProcessing_DipToBlackTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::PostProcessing::DipToBlack shader;
   EXPECT_EQ("AllegroFlare/Shaders/PostProcessing/DipToBlack", shader.get_type());
}


TEST(AllegroFlare_Shaders_PostProcessing_DipToBlackTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::PostProcessing::DipToBlack shader;
   EXPECT_EQ(AllegroFlare::Shaders::PostProcessing::DipToBlack::TYPE, shader.get_type());
}


TEST(AllegroFlare_Shaders_PostProcessing_DipToBlackTest, initialize__will_work_without_blowing_up)
{
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Shaders::PostProcessing::DipToBlack *shader = new AllegroFlare::Shaders::PostProcessing::DipToBlack;
   shader->initialize(); // for now, we'll have to use a pointer due to the way it's structured (should fix eventually)
   delete shader;

   al_uninstall_system();
}


TEST(AllegroFlare_Shaders_PostProcessing_DipToBlackTest, VISUAL__will_appear_as_expected)
{
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Shaders::PostProcessing::DipToBlack *shader = new AllegroFlare::Shaders::PostProcessing::DipToBlack;
   shader->initialize(); // for now, we'll have to use a pointer due to the way it's structured (should fix eventually)

   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.set_surface_width(al_get_display_width(display));
   render_surface.set_surface_height(al_get_display_height(display));
   render_surface.initialize();

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      // Render everything to our temporary render surface
      render_surface.set_as_target();
      al_clear_to_color(ALLEGRO_COLOR{1.0, 0.94, 0.84, 1.0}); // Fill with the color "papaya whip"

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


