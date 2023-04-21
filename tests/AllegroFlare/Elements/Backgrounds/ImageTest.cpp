
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/Backgrounds/Image.hpp>

#include <chrono>
#include <thread>

class AllegroFlare_Elements_Backgrounds_ImageTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_ImageWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_Backgrounds_ImageTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Image image_background;
}


TEST(AllegroFlare_Elements_Backgrounds_ImageTest, TYPE__has_the_expected_value)
{
   std::string expected_type = "AllegroFlare/Elements/Backgrounds/Image";
   std::string actual_type = AllegroFlare::Elements::Backgrounds::Image::TYPE;
   EXPECT_EQ(expected_type, actual_type);
}


TEST(AllegroFlare_Elements_Backgrounds_ImageTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Image base_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Image::TYPE, base_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_ImageWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_render_the_image)
{
   AllegroFlare::Elements::Backgrounds::Image image_background(
         &get_bitmap_bin_ref(),
         "deep-green-leaves-white-veins-960x540.jpg"
      );

   clear();
   image_background.render();
   al_flip_display();
}


