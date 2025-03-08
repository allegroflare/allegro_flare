
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>

class AllegroFlare_LoadASavedGame_ScreenTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_LoadASavedGame_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


TEST_F(AllegroFlare_LoadASavedGame_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::Screen screen;
}


TEST_F(AllegroFlare_LoadASavedGame_ScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::LoadASavedGame::Screen screen;
   EXPECT_EQ("AllegroFlare/LoadASavedGame/Screen", screen.get_type());
}


TEST_F(AllegroFlare_LoadASavedGame_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::LoadASavedGame::Screen screen;
   EXPECT_EQ(AllegroFlare::LoadASavedGame::Screen::TYPE, screen.get_type());
}


TEST_F(AllegroFlare_LoadASavedGame_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::LoadASavedGame::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_model_bin(get_framework_model_bin());

   screen.set_save_slots({
      new AllegroFlare::LoadASavedGame::SaveSlots::Basic("Saved Game 1"),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty()
   });

   screen.initialize();

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(3);
}



/*
         case STATE_REVEALING:
            title_revealed = false; // TODO: Test this
            reveal_started_at = state_accumulated_age;
            cursor_position = 0;
            showing_menu = false;
            showing_footer_text = false;
            menu_option_chosen = false;
            menu_option_activated = false;
            menu_option_chosen_at = 0.0f;
         break;

         case STATE_REVEALED_AND_AWAITING_USER_INPUT:
            menu_option_chosen = false;
            menu_option_activated = false;
            title_revealed = true;
            showing_menu = true;
            showing_footer_text = true;
            if (menu_options.empty()) showing_empty_state_text = true;
         break;

         case STATE_MENU_OPTION_IS_CHOSEN:
            menu_option_chosen = true;
            menu_option_activated = false;
            menu_option_chosen_at = state_accumulated_age;
         break;

         case STATE_AWAITING_USER_CONFIRMATION:
            showing_confirmation_dialog = true;
         break;

         case STATE_FINISHED:
         break;

         default:
            throw std::runtime_error("weird error");
         break;

*/


