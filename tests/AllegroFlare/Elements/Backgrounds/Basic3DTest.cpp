
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/Backgrounds/Basic3D.hpp>

#include <chrono>
#include <thread>

class AllegroFlare_Elements_Backgrounds_Basic3DTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_Basic3DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic_3d;
}


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/Backgrounds/Basic3D",
     AllegroFlare::Elements::Backgrounds::Basic3D::TYPE
   );
}


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic3d;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Basic3D::TYPE, basic3d.get_type());
}


/*
TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_render_the_image)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic_3d(
         &get_bitmap_bin_ref(),
         "deep-green-leaves-white-veins-960x540.jpg"
      );

   clear();
   basic_3d.render();
   al_flip_display();
}
*/


