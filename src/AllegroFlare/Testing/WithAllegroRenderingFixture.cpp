

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

   // dropping these comments here for later
   //#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/Krampus21/bin/programs/data/fonts/"
   //#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/Krampus21/bin/programs/data/fonts/"

   font_bin.set_full_path("/Users/markoates/Repos/Krampus21/bin/programs/data/fonts");
   bitmap_bin.set_full_path("/Users/markoates/Repos/Krampus21/bin/programs/data/bitmaps");

   //display = al_create_display(1280 * 2, 720 * 2);
   display = al_create_display(1920, 1080);
   al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
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

allegro_flare::placement2d WithAllegroRenderingFixture::build_centered_placement(float width, float height)
{
   if (!(al_get_target_bitmap()))
      {
         std::stringstream error_message;
         error_message << "WithAllegroRenderingFixture" << "::" << "build_centered_placement" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
         throw std::runtime_error(error_message.str());
      }
   allegro_flare::placement2d place(al_get_display_width(display)/2, al_get_display_height(display)/2, width, height);
   return place;
}
} // namespace Testing
} // namespace AllegroFlare


