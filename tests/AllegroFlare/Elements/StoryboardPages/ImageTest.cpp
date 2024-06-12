
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, start__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   std::string expected_error_message =
      "Image::start: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(image.start(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   std::string expected_error_message =
      "Image::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(image.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTest, render__without_a_current_display__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::StoryboardPages::Image image;
   std::string expected_error_message =
      "Image::render: error: guard \"al_get_current_display()\" not met";
   EXPECT_THROW_WITH_MESSAGE(image.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   image.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTestWithAllegroRenderingFixture,
   update__after_duration_to_advance_sec_have_passed__will_mark_the_page_as_finished)
{
   AllegroFlare::Elements::StoryboardPages::Image image;
   AllegroFlare::Elements::StoryboardPages::Base *image_as_base =
      dynamic_cast<AllegroFlare::Elements::StoryboardPages::Base*>(&image);
   
   image.set_duration_to_advance_sec(0.25);
   int attempts = 60; // 60 frames
   image.start();
   // TODO add profile timer to ensure time was > 0.5 seconds
   while (!image_as_base->get_finished())
   {
      image.update();
      sleep_for_frame();

      attempts--;
      if (attempts < 0) FAIL();
   }
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageTestWithAllegroRenderingFixture,
   VISUAL__render__will_display_as_expected)
{
   ALLEGRO_BITMAP *bitmap = get_bitmap_bin_ref()["monoplex-1.png"];

   AllegroFlare::Elements::StoryboardPages::Image image(bitmap);
   AllegroFlare::Elements::StoryboardPages::Base *image_as_base =
      dynamic_cast<AllegroFlare::Elements::StoryboardPages::Base*>(&image);
   
   int attempts = 60*3;
   image.start();
   while (!image_as_base->get_finished())
   {
      al_clear_to_color(ALLEGRO_COLOR{0});
      image.update();
      image.render();
      al_flip_display();
      sleep_for_frame();

      attempts--;
      if (attempts < 0) FAIL() << "Too many attempts while expecting auto-close; aborting.";
   }
   SUCCEED();
}


