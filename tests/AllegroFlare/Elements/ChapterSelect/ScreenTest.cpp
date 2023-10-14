
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>

class AllegroFlare_Elements_ChapterSelect_ScreenTest : public ::testing::Test
{
public:
   static void on_menu_choice_callback_counter_func(AllegroFlare::Elements::ChapterSelect::Screen*, void* user_data)
   {
      (*static_cast<int*>(user_data))++;
   }
   static void on_exit_screen_callback_counter_func(AllegroFlare::Elements::ChapterSelect::Screen*, void* user_data)
   {
      (*static_cast<int*>(user_data))++;
   }
};
class AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{
public:
   static void on_menu_choice_callback_func(AllegroFlare::Elements::ChapterSelect::Screen* screen, void* user_data)
   {
      // Do nothing here
   }
   static void on_exit_screen_callback_func(AllegroFlare::Elements::ChapterSelect::Screen* screen, void* user_data)
   {
      // Do nothing here
   }
};



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


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTest,
      activate_menu_option__when_on_menu_choice_callback_func_is_assigned__will_call_the_callback
   )
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
   int callback_count_counter = 0;
   screen.set_on_menu_choice_callback_func(
         AllegroFlare_Elements_ChapterSelect_ScreenTest::on_menu_choice_callback_counter_func
      );
   screen.set_on_menu_choice_callback_func_user_data((void*)(&callback_count_counter));

   screen.activate_menu_option();

   EXPECT_EQ(1, callback_count_counter);
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTest,
      exit_screen__when_on_exit_screen_callback_func_is_assigned__will_call_the_callback
   )
{
   AllegroFlare::Elements::ChapterSelect::Screen screen;
   int callback_count_counter = 0;
   screen.set_on_exit_screen_callback_func(
         AllegroFlare_Elements_ChapterSelect_ScreenTest::on_exit_screen_callback_counter_func
      );
   screen.set_on_exit_screen_callback_func_user_data((void*)(&callback_count_counter));

   screen.exit_screen();

   EXPECT_EQ(1, callback_count_counter);
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   // TODO: Update test to not timeout after a keypress
   using namespace AllegroFlare::Elements::ChapterSelect::CarouselElements;

   AllegroFlare::Elements::ChapterSelect::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_rotate_carousel_sound_effect_identifier("foo");
   screen.set_select_menu_sound_effect_identifier("bar");

   screen.initialize();

   screen.set_on_menu_choice_callback_func(
         AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture::on_menu_choice_callback_func
      );
   screen.set_on_exit_screen_callback_func(
         AllegroFlare_Elements_ChapterSelect_ScreenTestWithAllegroFrameworksFullFixture::on_exit_screen_callback_func
      );

   std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements = {
      new ThumbnailWithLabelUnlockable(
            "storyboard-image-1164x500.png",
            "CHAPTER 1: Rise of the City",
            "",
            "CHAPTER 1",
            true
         ),
      new ThumbnailWithLabelUnlockable(
            "storyboard-image-1164x500.png",
            "CHAPTER 2: The Sanctuary",
            "",
            "CHAPTER 2",
            true
         ),
      new ThumbnailWithLabelUnlockable(
            "storyboard-image-1164x500.png",
            "CHAPTER 3: The Way Ahead",
            "",
            "CHAPTER 3",
            true
         ),
      new ThumbnailWithLabelUnlockable(
            "storyboard-image-1164x500.png",
            "CHAPTER 4: The Bridge",
            "",
            "CHAPTER 4",
            false
         ),
      new ThumbnailWithLabelUnlockable(
            "storyboard-image-1164x500.png",
            "CHAPTER 5: Without an Anchor",
            "",
            "CHAPTER 5",
            false
         ),
   };

   screen.set_elements(carousel_elements);
   screen.set_pagination_bar_elements({ true, true, true, false, false });

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(3);
}


