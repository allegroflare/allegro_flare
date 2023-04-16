
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
   std::string expected_type = "AllegroFlare/Elements/Backgrounds/ImageIdentifier";
   std::string actual_type = AllegroFlare::Elements::Backgrounds::ImageIdentifier::TYPE;
   EXPECT_EQ(expected_type, actual_type);
}


TEST(AllegroFlare_Elements_Backgrounds_ImageIdentifierTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::ImageIdentifier base_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::ImageIdentifier::TYPE, base_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_ImageIdentifierWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_render_the_image)
{
   AllegroFlare::Elements::Backgrounds::ImageIdentifier image_background(
         &get_bitmap_bin_ref(),
         "deep-green-leaves-white-veins-960x540.jpg"
      );

   clear();
   image_background.render();
   al_flip_display();
}


