
#include <gtest/gtest.h>

#include <AllegroFlare/ClubCatt/Logo.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/RenderSurfaces/DisplayBackbuffer.hpp>


class AllegroFlare_ClubCatt_LogoTest: public ::testing::Test {};
class AllegroFlare_ClubCatt_LogoWithAllegroRenderingFixtureTest : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_ClubCatt_LogoWithAllegroRenderingFixtureTest, VISUAL__will_appear_as_expected)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer render_surface;
   render_surface.set_display(get_display()); // TODO: Not sure how this should be destroyed
   render_surface.initialize();
   AllegroFlare::ModelBin model_bin;
   model_bin.set_path(get_fixtures_path() + "models");

   AllegroFlare::ClubCatt::Logo logo;
   logo.set_render_surface(&render_surface);
   logo.set_bitmap_bin(&get_bitmap_bin_ref());
   logo.set_model_bin(&model_bin);
   logo.initialize();

   logo.play(al_get_time());

   float number_of_seconds = 6.0f;
   int loops = (int)(number_of_seconds * 60.0f);
   for (int i=0; i<loops; i++)
   {
      float time_now = al_get_time();

      logo.update(time_now);
      if (logo.get_finished()) break;
      logo.draw(time_now);

      al_flip_display();
   }
}


TEST_F(AllegroFlare_ClubCatt_LogoWithAllegroRenderingFixtureTest,
   initialize__will_allocate_some_resources_through_the_bins)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer render_surface;
   render_surface.set_display(get_display()); // TODO: Not sure how this should be destroyed
   render_surface.initialize();
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::ModelBin model_bin;
   model_bin.set_path(get_fixtures_path() + "models");

   AllegroFlare::ClubCatt::Logo logo;
   logo.set_render_surface(&render_surface);
   logo.set_bitmap_bin(&bitmap_bin);
   logo.set_model_bin(&model_bin);
   logo.initialize();

   EXPECT_EQ(1, model_bin.size());
   EXPECT_EQ(2, bitmap_bin.size());
}


TEST_F(AllegroFlare_ClubCatt_LogoWithAllegroRenderingFixtureTest,
   destroy__will_deallocate_the_aquired_resources_in_the_bins)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer render_surface;
   render_surface.set_display(get_display()); // TODO: Not sure how this should be destroyed
   render_surface.initialize();
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::ModelBin model_bin;
   model_bin.set_path(get_fixtures_path() + "models");

   AllegroFlare::ClubCatt::Logo logo;
   logo.set_render_surface(&render_surface);
   logo.set_bitmap_bin(&bitmap_bin);
   logo.set_model_bin(&model_bin);
   logo.initialize();

   EXPECT_EQ(1, model_bin.size());
   EXPECT_EQ(2, bitmap_bin.size());

   logo.destroy();

   EXPECT_EQ(0, model_bin.size());
   EXPECT_EQ(0, bitmap_bin.size());
}


