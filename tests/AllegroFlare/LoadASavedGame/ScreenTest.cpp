
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>

class AllegroFlare_LoadASavedGame_ScreenTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_ScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_LoadASavedGame_ScreenTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
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


TEST_F(AllegroFlare_LoadASavedGame_ScreenTestWithInteractionFixture,
   INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::LoadASavedGame::Screen screen(get_data_folder_path());
   screen.set_on_exit_callback_func([this](AllegroFlare::LoadASavedGame::Screen*, void*){
      // Typically you would have something like swap back to the title screen, or previous screen.
      AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
         "In on_exit_callback_func for the LoadASavedGame screen: Exiting screen."
      );
      abort(); // Exit the test
   });
   screen.set_on_erase_focused_save_slot_func([](AllegroFlare::LoadASavedGame::Screen*, void*){
      // Empty for this test.
   });
   screen.set_on_menu_choice_callback_func([this](AllegroFlare::LoadASavedGame::Screen*, void*){
      // NOTE: Typically this would be the *activation* of loading the save slot. This callback is fired
      // when the screen has finished "shutting down" from selection animations and screen hiding animations.
      AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
         "In on_menu_chioce_callback_func for the LoadASavedGame screen: Submitting menu choice."
      );
      abort(); // Exit the test
   });
   screen.set_save_slots({
      new AllegroFlare::LoadASavedGame::SaveSlots::Basic("Saved Game 1"),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty()
   });

   screen.initialize();
   screen.on_activate();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            screen.primary_update_func(al_get_time(), 1.0/60.0);

            clear();
            screen.primary_render_func();
            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            screen.key_char_func(&current_event);
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  //// Do something
               //break;
            //}
         }
         break;
      }
   }

   screen.destroy();
}


TEST_F(AllegroFlare_LoadASavedGame_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::LoadASavedGame::Screen screen(get_framework_data_folder_path());
   screen.set_save_slots({
      new AllegroFlare::LoadASavedGame::SaveSlots::Basic("Saved Game 1"),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty()
   });

   screen.initialize();

   framework_register_and_activate_screen("screen", &screen);

   framework_run_loop(1);

   screen.destroy();
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

   case STATE_REVEALED_AND_HANDLING_USER_INPUT:
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


