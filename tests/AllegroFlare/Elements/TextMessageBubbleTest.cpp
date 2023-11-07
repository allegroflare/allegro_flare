
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/TextMessageBubble.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_Elements_TextMessageBubbleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::TextMessageBubble text_message_bubble;
}


/*

// TODO: Work in these tests

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


// TODO: Fix this folder location
#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/Krampus21/bin/programs/data/fonts/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/Krampus21/bin/programs/data/fonts/"
#endif

//#include <Krampus21/Elements/SmartPhoneDialogBubble.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>

class Krampus21_SmartPhoneDialogBubbleTest : public ::testing::Test {};
class Krampus21_SmartPhoneDialogBubbleWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(Krampus21_SmartPhoneDialogBubbleWithAllegroRenderingFixtureTest, can_be_created_without_blowing_up)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   Krampus21::Elements::SmartPhoneDialogBubble dialog_bubble(
      &get_font_bin_ref(),
      "Hello, this is bubble text",
      600,
      100,
      true
   );

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   dialog_bubble.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   std::this_thread::sleep_for(std::chrono::seconds(1));
}
*/


