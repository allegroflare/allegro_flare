
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Krampus21/DialogBoxRenderers/SmartPhone.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/Krampus21/bin/programs/data/fonts/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/Krampus21/bin/programs/data/fonts/"
#endif

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>

class Krampus21_DialogBoxRenderers_SmartPhoneTest : public ::testing::Test {};
class Krampus21_DialogBoxRenderers_SmartPhoneWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(Krampus21_DialogBoxRenderers_SmartPhoneWithAllegroRenderingFixtureTest, can_be_created_without_blowing_up)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, 600/2, 600 };
   int passes = 60;
   float reveal_counter = 0;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      Krampus21::DialogBoxRenderers::SmartPhone smart_phone_dialog_renderer(
         &get_font_bin_ref(),
         600,
         100,
         { "Hello, this is bubble text", "And this is a second line", "And finally the last line" },
         reveal_counter
      );

      place.start_transform();
      smart_phone_dialog_renderer.render();
      place.restore_transform();
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
      reveal_counter += (1.0/60.0f) * 2;
   }

   //std::this_thread::sleep_for(std::chrono::seconds(1));
}


