

#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/ImageProcessing/ImageReduction.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_ImageProcessing_ImageReductionTest : public ::testing::Test {};
class AllegroFlare_ImageProcessing_ImageReductionTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_ImageProcessing_ImageReductionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ImageProcessing::ImageReduction image_reduction;
}


TEST_F(AllegroFlare_ImageProcessing_ImageReductionTestWithAllegroRenderingFixture,
   create_pixel_perfect_reduction__will_create_the_expected_image)
{
   ALLEGRO_BITMAP *source_image = get_bitmap_bin_ref().auto_get("ascii_glyphs_12x16-08-4x.png");
   EXPECT_NE(nullptr, source_image);

   int width = 264;
   int height = 352;

   ALLEGRO_BITMAP *result =
      AllegroFlare::ImageProcessing::ImageReduction::create_pixel_perfect_reduction(source_image, width, height);
   EXPECT_EQ(width, al_get_bitmap_width(result));
   EXPECT_EQ(height, al_get_bitmap_height(result));

   // TODO: Consider improving this destination filename
   save_bitmap_to_test_snapshots_folder("create_pixel_perfect_reduction__result.png", result);

   al_flip_display();
   sleep_for(1);
}


