
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <filesystem>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


class TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   get_test_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "get_test_name__will_return_the_name_of_the_test";
   EXPECT_EQ(expected_test_name, get_test_name());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   get_test_suite_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture";
   EXPECT_EQ(expected_test_name, get_test_suite_name());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   SetUp__will_set_the_font_bin_path_to_the_expected_path)
{
   std::string expected_font_bin_path = "tests/fixtures/fonts/";
   std::string actual_font_bin_path = get_font_bin_ref().get_path();
   EXPECT_EQ(expected_font_bin_path, actual_font_bin_path);
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   SetUp__will_set_the_bitmap_bin_path_to_the_expected_path)
{
   std::string expected_bitmap_bin_path = "tests/fixtures/bitmaps/";
   std::string actual_bitmap_bin_path = get_bitmap_bin_ref().get_path();
   EXPECT_EQ(expected_bitmap_bin_path, actual_bitmap_bin_path);
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   DISABLED__will_set_the_window_title_to_the_test_suite_name_and_test_name)
{
   // NOTE: cannot currently test this, Allegro5 does not currently have a al_get_window_title() feature
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   DISABLED__with_a_test_name_prefixed_with_CAPTURE__will_save_a_screenshot_of_the_backbuffer_during_teardown)
{
   // NOTE: cannot currently test this, assertion would need to happen after teardown
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   DISABLED__clear_will_clear_the_current_target_rendering_surface_to_the_expected_dark_gamer_gray_color)
{
   ALLEGRO_COLOR expected_clear_color = ALLEGRO_COLOR{0.05f, 0.05f, 0.055f, 1.0f};

   clear();
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());
   al_lock_bitmap(backbuffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

   for (int y=0; y<al_get_bitmap_height(backbuffer); y++)
   {
      for (int x=0; x<al_get_bitmap_width(backbuffer); x++)
      {
         ALLEGRO_COLOR picked_color = al_get_pixel(backbuffer, x, y);
         ASSERT_EQ(expected_clear_color, picked_color);
      }
   }

   al_unlock_bitmap(backbuffer);
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   DISABLED__get_display_backbuffer__will_return_the_backbuffer_of_the_test_window)
{
   // TODO
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   CAPTURE__draw_rectangle__will_appear_as_expected)
{
   float width = 600;
   float height = 300;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;

   draw_rectangle(x, y, width, height);
   al_flip_display();
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   CAPTURE__draw_horizontal_crosshair__will_appear_as_expected)
{
   float x = 1920/2;
   float y = 1080/2;

   draw_horizontal_crosshair(x, y);
   al_flip_display();
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   CAPTURE__draw_vertical_crosshair__will_appear_as_expected)
{
   float x = 1920/2;
   float y = 1080/2;

   draw_vertical_crosshair(x, y);
   al_flip_display();
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   CAPTURE__draw_crosshair_blue__will_appear_as_expected)
{
   float x = 1920/2;
   float y = 1080/2;

   draw_crosshair_blue(x, y);
   al_flip_display();
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   CAPTURE__get_any_font__will_return_a_simple_appealing_and_usable_font)
{
   float x = 1920/2;
   float y = 1080/2;
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 1, 1, 1};

   ALLEGRO_FONT* any_font = get_any_font();
   ALLEGRO_FONT* small_font = get_small_font();
   std::string any_font_demo_text = "This is some text written in the \"get_any_font\" font.";
   std::string small_font_demo_text = "This is some text written in the \"get_small_font\" font.";

   clear();
   al_draw_text(any_font, color, x, y-20, ALLEGRO_ALIGN_CENTER, any_font_demo_text.c_str());
   al_draw_text(small_font, color, x, y+20, ALLEGRO_ALIGN_CENTER, small_font_demo_text.c_str());
   al_flip_display();
}


