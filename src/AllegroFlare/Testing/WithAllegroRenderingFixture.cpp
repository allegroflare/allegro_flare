

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/TerminalColors.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>


namespace AllegroFlare
{
namespace Testing
{


WithAllegroRenderingFixture::WithAllegroRenderingFixture()
   : ::testing::Test()
   , display(nullptr)
   , font_bin({})
   , bitmap_bin({})
{
}


WithAllegroRenderingFixture::~WithAllegroRenderingFixture()
{
}


ALLEGRO_DISPLAY* WithAllegroRenderingFixture::get_display() const
{
   return display;
}


AllegroFlare::FontBin &WithAllegroRenderingFixture::get_font_bin_ref()
{
   return font_bin;
}


AllegroFlare::BitmapBin &WithAllegroRenderingFixture::get_bitmap_bin_ref()
{
   return bitmap_bin;
}


void WithAllegroRenderingFixture::SetUp()
{
   ASSERT_EQ(false, al_is_system_installed());
   ASSERT_EQ(true, al_init());
   ASSERT_EQ(true, al_init_primitives_addon());
   ASSERT_EQ(true, al_init_font_addon());
   ASSERT_EQ(true, al_init_ttf_addon());
   ASSERT_EQ(true, al_init_image_addon());

   #ifdef _WIN32
   #define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
   #define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
   #define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
   #else
   #define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
   #define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
   #define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
   #endif

   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   //display = al_create_display(1280 * 2, 720 * 2);
   //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   display = al_create_display(1920, 1080);

   ASSERT_NE(nullptr, display);

   // clear the display to a slightly gray black color
   al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.055f, 1.0f});

   // set the window title to the current test name
   std::string new_window_title = build_full_test_name_str();

   al_set_window_title(display, new_window_title.c_str());

   return;
}

void WithAllegroRenderingFixture::TearDown()
{
   if (test_name_indicates_it_wants_a_screenshot())
   {
      capture_screenshot(build_full_test_name_str() + ".png");
   }

   font_bin.clear();
   bitmap_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                            // this is a bug in Allegro
   al_uninstall_system();
   return;
}

ALLEGRO_FONT* WithAllegroRenderingFixture::get_any_font()
{
   return font_bin.auto_get("consolas.ttf 32");
}

ALLEGRO_BITMAP* WithAllegroRenderingFixture::get_display_backbuffer()
{
   return al_get_backbuffer(display);
}

void WithAllegroRenderingFixture::sleep_for_frame()
{
   static int frame_length_in_milliseconds = 1000/60;
   std::this_thread::sleep_for(std::chrono::milliseconds(frame_length_in_milliseconds));
}

void WithAllegroRenderingFixture::sleep_for(float length_in_seconds)
{
   int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
   std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
}

std::string WithAllegroRenderingFixture::get_test_name()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->name();
}

std::string WithAllegroRenderingFixture::get_test_suite_name()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->test_suite_name();
}

std::string WithAllegroRenderingFixture::build_full_test_name_str()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   return get_test_suite_name() + " - " + get_test_name();
}

AllegroFlare::Placement2D WithAllegroRenderingFixture::build_centered_placement(float width, float height)
{
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroRenderingFixture::build_centered_placement]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroRenderingFixture::build_centered_placement: error: guard \"al_get_target_bitmap()\" not met");
   }
   AllegroFlare::Placement2D place(al_get_display_width(display)/2, al_get_display_height(display)/2, width, height);
   return place;
}

void WithAllegroRenderingFixture::draw_rulers()
{
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroRenderingFixture::draw_rulers]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroRenderingFixture::draw_rulers: error: guard \"al_get_target_bitmap()\" not met");
   }
   al_draw_line(1920/2, 0, 1920/2, 1080, al_color_name("gray"), 1.0); // rulers down the center
   al_draw_line(0, 1080/2, 1920, 1080/2, al_color_name("gray"), 1.0); // rulers across the middle
}

void WithAllegroRenderingFixture::draw_crosshair(float x, float y, ALLEGRO_COLOR color, float size)
{
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroRenderingFixture::draw_crosshair]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroRenderingFixture::draw_crosshair: error: guard \"al_get_target_bitmap()\" not met");
   }
   float h_size = size * 0.5;
   // draw horizontal line
   al_draw_line(x-h_size, y, x+h_size, y, color, 1.0);
   // draw vertical line
   al_draw_line(x, y-h_size, x, y+h_size, color, 1.0);
}

void WithAllegroRenderingFixture::draw_horizontal_crosshair(float x, float y, ALLEGRO_COLOR color, float size_v, float size_h)
{
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroRenderingFixture::draw_horizontal_crosshair]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroRenderingFixture::draw_horizontal_crosshair: error: guard \"al_get_target_bitmap()\" not met");
   }
   float h_size_h = size_h * 0.5;
   float h_size_v = size_v * 0.5;
   // draw horizontal line
   al_draw_line(x-h_size_h, y, x+h_size_h, y, color, 1.0);
   // draw vertical line
   al_draw_line(x, y-h_size_v, x, y+h_size_v, color, 1.0);
}

bool WithAllegroRenderingFixture::test_name_indicates_it_wants_a_screenshot()
{
   return (get_test_name().substr(0, 9) == "CAPTURE__");
}

void WithAllegroRenderingFixture::clear_display()
{
   // depreciated, please use clear();
   clear();
   return;
}

void WithAllegroRenderingFixture::clear()
{
   al_clear_depth_buffer(1);
   ALLEGRO_COLOR eigengrau = ALLEGRO_COLOR{0.086f, 0.086f, 0.114f, 1.0f};
   al_clear_to_color(eigengrau);
   return;
}

void WithAllegroRenderingFixture::capture_screenshot(std::string base_filename)
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   std::string full_file_save_location = TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER + base_filename;

   al_flip_display(); // this capture_screenshot technique assumes the pixels to capture are currently being
                      // shown on the display.  This al_flip_display is added here in order to flip the
                      // front-buffer *back* to the backbuffer so it can be used to capture the screenshot

   bool screenshot_successful = al_save_bitmap(full_file_save_location.c_str(), al_get_backbuffer(display));
   if (screenshot_successful)
   {
      std::cout << AllegroFlare::TerminalColors::CYAN
                << "[AllegroFlare::Testing::WithAllegroRenderingFixture::screenshot]: info: screenshot saved to "
                << "\"" << full_file_save_location << "\""
                << AllegroFlare::TerminalColors::DEFAULT
                << std::endl;
   }
   else
   {
      std::cout << AllegroFlare::TerminalColors::RED
                << "[AllegroFlare::Testing::WithAllegroRenderingFixture::screenshot]: error: screenshot "
                << "CAPTURE was not successful when trying to saving to \"" << full_file_save_location << "\""
                << AllegroFlare::TerminalColors::DEFAULT
                << std::endl;
   }
}


} // namespace Testing
} // namespace AllegroFlare


