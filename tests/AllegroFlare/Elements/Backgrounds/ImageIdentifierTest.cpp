
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Elements/Backgrounds/ImageIdentifier.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_Backgrounds_ImageIdentifierTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_ImageIdentifierWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_Backgrounds_ImageIdentifierTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::ImageIdentifier image_background;
}


TEST(AllegroFlare_Elements_Backgrounds_ImageIdentifierTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ(
      "AllegroFlare/Elements/Backgrounds/ImageIdentifier",
      AllegroFlare::Elements::Backgrounds::ImageIdentifier::TYPE
   );
}


TEST(AllegroFlare_Elements_Backgrounds_ImageIdentifierTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::ImageIdentifier base_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::ImageIdentifier::TYPE, base_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_ImageIdentifierWithAllegroRenderingFixtureTest, render__will_render_the_image)
{
   AllegroFlare::Elements::Backgrounds::ImageIdentifier image_background(
         &get_bitmap_bin_ref(),
         "deep-green-leaves-white-veins-960x540.jpg"
      );

   int frames = 60;
   for (unsigned i=0; i<frames; i++)
   {
      //update
      image_background.update();

      // render
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      image_background.render();
      al_flip_display();
      sleep_for_frame();
   }
}


