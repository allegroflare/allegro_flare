
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/FlatColor.hpp>
#include <allegro5/allegro_color.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Shaders_FlatColorTest: public ::testing::Test {};
class AllegroFlare_Shaders_FlatColorWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::FlatColor flat_color;
}


TEST_F(AllegroFlare_Shaders_FlatColorTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/FlatColor",
     AllegroFlare::Shaders::FlatColor::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_FlatColorTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::FlatColor flat_color;
   EXPECT_EQ(AllegroFlare::Shaders::FlatColor::TYPE, flat_color.get_type());
}


TEST_F(AllegroFlare_Shaders_FlatColorWithAllegroRenderingFixtureTest, activate__does_not_blow_up)
{
   AllegroFlare::Shaders::FlatColor flat_color;
   flat_color.initialize();
   flat_color.activate();
}


TEST_F(AllegroFlare_Shaders_FlatColorWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__will_apply_opacity_after_color_and_intensity)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Shaders::FlatColor flat_color;
   flat_color.initialize();

   clear();

   {
      flat_color.activate();
      flat_color.set_color(al_color_name("orange"));
      flat_color.set_color_intensity(0.5);
      flat_color.set_color_opacity(0.5);
      al_draw_bitmap(bitmap_bin["cat_for_color_testing.jpg"], 400, 200, 0);
   }

   al_flip_display();
   al_rest(1);
}
 


// TODO: Add a render test with a bitmap render subject


// TODO: Add a render test where the "set_color()" and "set_color_intensity()" is checked to ensure it is assigned
// to the shader, and to the class's member


