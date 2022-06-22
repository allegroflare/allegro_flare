

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


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


ALLEGRO_DISPLAY* WithAllegroRenderingFixture::get_display()
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
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   #ifdef _WIN32
   // NOTE  was in  Repos/Krampus21
   #define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
   #define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
   #else
   #define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
   #define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
   #endif

   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   //display = al_create_display(1280 * 2, 720 * 2);
   display = al_create_display(1920, 1080);

   ASSERT_NE(nullptr, display);

   // clear the display to a slightly gray black color
   al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 1.0f});

   // set the window title to the current test name
   std::string current_test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
   std::string current_test_suite_name = ::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
   std::string new_window_title = current_test_suite_name + " - " + current_test_name;

   al_set_window_title(display, new_window_title.c_str());

   return;
}

void WithAllegroRenderingFixture::TearDown()
{
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
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->name();
}

std::string WithAllegroRenderingFixture::get_test_suite_name()
{
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->test_suite_name();
}

AllegroFlare::Placement2D WithAllegroRenderingFixture::build_centered_placement(float width, float height)
{
   if (!(al_get_target_bitmap()))
      {
         std::stringstream error_message;
         error_message << "WithAllegroRenderingFixture" << "::" << "build_centered_placement" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Placement2D place(al_get_display_width(display)/2, al_get_display_height(display)/2, width, height);
   return place;
}

void WithAllegroRenderingFixture::draw_rulers()
{
   if (!(al_get_target_bitmap()))
      {
         std::stringstream error_message;
         error_message << "WithAllegroRenderingFixture" << "::" << "draw_rulers" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
         throw std::runtime_error(error_message.str());
      }
   al_draw_line(1920/2, 0, 1920/2, 1080, al_color_name("gray"), 1.0); // rulers down the center
   al_draw_line(0, 1080/2, 1920, 1080/2, al_color_name("gray"), 1.0); // rulers across the middle
}
} // namespace Testing
} // namespace AllegroFlare


