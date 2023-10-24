
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp> // TODO: Remove this dependency
#include <AllegroFlare/EventNames.hpp> // For ALLEGRO_FLARE_EVENT_EXIT_GAME


class AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest: public ::testing::Test {};
class AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


static AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *create_driver(AllegroFlare::BitmapBin *bitmap_bin)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();

   driver->set_bitmap_bin(bitmap_bin);
   driver->initialize();

      //if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      //{
         //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         //driver->destroy();
         ////driver->initialize();
      //}
   return driver;
}


void destroy_driver(AllegroFlare::DialogSystemDrivers::Base* _driver)
{
      if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      {
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         driver->destroy();
         //driver->initialize();
      }
      else
      {
         throw std::runtime_error("in test: Could not destroy _driver");
      }
}



TEST_F(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver system_notifications_driver;
}


TEST_F(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver",
     AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::TYPE
   );
}


TEST_F(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver system_notifications_driver;
   EXPECT_EQ(AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::TYPE, system_notifications_driver.get_type());
}


TEST_F(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   //std::string dialog_filename = get_fixtures_path() + "/dialogs/basic_screenplay_text.screenplay.txt";
   //AllegroFlare::DialogSystem::CharacterRoster *character_roster = create_and_assemble_character_roster();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );

   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver
   //AllegroFlare::DialogSystemDrivers::Base* _driver = dialog_system.get__driver();
   //if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   //{
      //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      //driver->character_roster = character_roster; // TODO: Change this to a setter
   //}
   //dialog_system.get_driver_ref().character_roster = character_roster; // TODO: Change this to a setter
   //dialog_system.initialize(); // NOTE: Initialization must happen before
   //AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::build_node_bank();
   dialog_system.set_dialog_node_bank(
         AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::build_node_bank()
      );

   // run the interactive test
   al_start_timer(primary_timer);

   EXPECT_EQ(false, dialog_system.get_switched_in());
   float duration_until_abort_sec = 6.0f; // TODO: Add a countdown
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;

   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            switch (event.keyboard.keycode)
            {
               case ALLEGRO_KEY_R: // R for "Reset"
                  dialog_system.activate_dialog_node_by_name(
                        AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::CONFIRM_EXIT_PROGRAM
                     );
                  EXPECT_EQ(true, dialog_system.get_switched_in()); // TODO: Move this to another test
               break;

               case ALLEGRO_KEY_UP:
                  dialog_system.move_dialog_cursor_position_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  dialog_system.move_dialog_cursor_position_down();
               break;

               //case ALLEGRO_KEY_LEFT:
                  //dialog_system.move_dialog_cursor_position_left();
               //break;

               //case ALLEGRO_KEY_RIGHT:
                  //dialog_system.move_dialog_cursor_position_right();
               //break;

               case ALLEGRO_KEY_ENTER:
                  if (dialog_system.a_dialog_is_active())
                  {
                     dialog_system.dialog_advance();
                     if (!dialog_system.a_dialog_is_active())
                     {
                        EXPECT_EQ(false, dialog_system.get_switched_in()); // TODO: Move this to another test
                     }
                  }
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;

               default:
               break;
            }
         }
         break;

         case ALLEGRO_FLARE_EVENT_EXIT_GAME:
            abort = true;
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            dialog_system.update();
            dialog_system.render();
            if (!dialog_system.a_dialog_is_active())
            {
               ALLEGRO_FONT *user_prompt_font = get_user_prompt_font();
               al_draw_multiline_text(
                  user_prompt_font,
                  ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
                  1920/2,
                  1080/2-80,
                  1920,
                  al_get_font_line_height(user_prompt_font),
                  ALLEGRO_ALIGN_CENTER,
                  "There are no dialogs currently active\n(press ESC to exit, R to START dialog)"
               );
            }
            al_flip_display();
         break;
      }
   }

   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.

   //delete character_roster;

   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}

