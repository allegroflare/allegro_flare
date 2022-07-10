
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StoryboardPages_ImageTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_ImageTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   EXPECT_EQ("Image", image.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   std::string expected_error_message =
      "Image::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(image.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, render__without_a_current_display__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::StoryboardPages::Image image;
   std::string expected_error_message =
      "Image::render: error: guard \"al_get_current_display()\" not met";
   ASSERT_THROW_WITH_MESSAGE(image.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   image.render();
   SUCCEED();
}


