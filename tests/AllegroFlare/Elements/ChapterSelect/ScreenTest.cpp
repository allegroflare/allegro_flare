
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Elements_ChapterSelect_ScreenTest : public ::testing::Test {};
class AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
   EXPECT_EQ("AllegroFlare/Elements/ChapterSelect/Screen", screen.get_type());
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
   EXPECT_EQ(AllegroFlare::Elements::ChapterSelect::Screen::TYPE, screen.get_type());
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.initialize();

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(3);
}


