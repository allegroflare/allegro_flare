#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <iostream>

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp> // TODO: Consider alternative to this loader
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp> // TODO: Remove this dependency
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp> // TODO: Remove this dependency


class AllegroFlare_DialogSystem_DialogSystemTest : public ::testing::Test {};

class AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::DialogSystem::CharacterRoster *create_and_assemble_character_roster()
   {
      AllegroFlare::DialogSystem::CharacterRoster *result_roster = new AllegroFlare::DialogSystem::CharacterRoster();

      AllegroFlare::DialogSystem::Characters::Basic *character = nullptr;
     
      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Detective Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("detective-01.gif");
      result_roster->add_character("DETECTIVE", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Banker Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("banker-01.gif");
      result_roster->add_character("BANKER", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Commissioner Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("commissioner-01.gif");
      character->set_expressions({
            { "happy", "smiling-01.gif" },
            { "unsure", "unsure-01.gif" },
         });
      result_roster->add_character("COMMISSIONER", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Assistant Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("assistant-01.gif");
      result_roster->add_character("ASSISTANT", character);

      return result_roster; // TODO: Delete after use
   }

   static bool my_load_node_bank_func(
         std::string filename,
         AllegroFlare::DialogTree::NodeBank* node_bank,
         void* user_data
      )
   {
      AllegroFlare::DialogTree::YAMLLoader yaml_loader;
      yaml_loader.load_file(filename);
      *node_bank = yaml_loader.get_node_bank();
      return true;
   }
};



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


static void destroy_driver(AllegroFlare::DialogSystemDrivers::Base* _driver)
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



TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
}



TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"bitmap_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_an_event_emitter__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   dialog_system.set_font_bin(&font_bin);
   std::string expected_error_message =
      "DialogSystem::initialize: error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_system.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver
   dialog_system.render();
   al_flip_display();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__render__when_a_dialog_box_is_open__will_work_as_expected)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.spawn_basic_dialog("Hugo", { "Hello, basic dialog", "Good to see you today" });

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__load_dialog_node_bank_from_file__will_not_blow_up)
{
   std::string dialog_filename = get_fixtures_path() + "/dialogs/linear_dialog.yml";

   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.set_load_node_bank_func(my_load_node_bank_func);
   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.activate_dialog_node_by_name("start_node");

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__load_dialog_node_bank_from_file__with_a_branching_dialog_that_includes_choices__will_not_blow_up)
{
   std::string dialog_filename = get_fixtures_path() + "/dialogs/branching_dialog.yml";

   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.set_load_node_bank_func(my_load_node_bank_func);
   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.activate_dialog_node_by_name("start_node");

   int NUM_PASSES = 20;
   int passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance(); // Advance the text to the end (and reveal the choice list box)
   dialog_system.move_dialog_cursor_position_down();
   dialog_system.dialog_advance(); // Advance the dialog (with the 2nd choice option selected)
   EXPECT_EQ("yuki_response_2", dialog_system.get_active_dialog_node_name());
   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   EXPECT_EQ(false, dialog_system.dialog_is_finished());
   dialog_system.dialog_advance(); // Skip to end of "yuki_response_2"
   EXPECT_EQ("yuki_response_2", dialog_system.get_active_dialog_node_name());
   EXPECT_EQ(false, dialog_system.dialog_is_finished()); // Node will not be finished until an update()

   // TODO: Sort out the remaining steps, and consider design option that does not require a call to update()
   // to advance as expected

   //dialog_system.dialog_advance();
   //EXPECT_EQ("ethan_response_2", dialog_system.get_active_dialog_node_name());

   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }

   //dialog_system.dialog_advance();
   //EXPECT_EQ("ethan_response_2", dialog_system.get_active_dialog_node_name());
   //dialog_system.dialog_advance(); // Skip to end

   //{ // Once
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      //dialog_system.update();
      //dialog_system.render();
      //al_flip_display();
   //}

   //dialog_system.dialog_advance();
   //EXPECT_EQ("", dialog_system.get_active_dialog_node_name());


/*
   dialog_system.dialog_advance();
   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
*/
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__without_a_character_roster__will_work_as_expected)
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
   std::string dialog_filename = get_fixtures_path() + "/dialogs/branching_dialog_with_long_text.yml";
   std::string node_name_to_start = "start_node";
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.set_load_node_bank_func(my_load_node_bank_func);
   dialog_system.initialize();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver
   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   //dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

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
                  dialog_system.activate_dialog_node_by_name(node_name_to_start);
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

   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__when_a_character_roster_is_present__will_work_as_expected)
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
   std::string dialog_filename = get_fixtures_path() + "/dialogs/basic_screenplay_text.screenplay.txt";
   std::string node_name_to_start = "dialog_node_0";
   AllegroFlare::DialogSystem::CharacterRoster *character_roster = create_and_assemble_character_roster();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );

   dialog_system.initialize();

   //AllegroFlare::DialogSystemDrivers::* _driver = dialog_system.get__driver();
   dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   AllegroFlare::DialogSystemDrivers::Base* _driver = dialog_system.get__driver();
   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->character_roster = character_roster; // TODO: Change this to a setter
   }
   //dialog_system.get_driver_ref().character_roster = character_roster; // TODO: Change this to a setter
   //dialog_system.initialize(); // NOTE: Initialization must happen before
   dialog_system.load_dialog_node_bank_from_file(dialog_filename);

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
                  dialog_system.activate_dialog_node_by_name(node_name_to_start);
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

   delete character_roster;

   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   update__when_the_currently_active_node_is_of_type_Wait__will_wait_until_the_time_has_finished_before_continuing)
{
   // Setup our test context
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   dialog_system.set_font_bin(&font_bin);
   dialog_system.set_event_emitter(&event_emitter);


   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *_driver =
      new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();
   if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
      driver->set_bitmap_bin(&bitmap_bin);
      driver->initialize();
   }

   dialog_system.set__driver(_driver);


   event_emitter.initialize();

   // Build up a node_bank with a wait node
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node("wait_node_1", new AllegroFlare::DialogTree::Nodes::Wait(1, "next_node"));
   node_bank.add_node("next_node", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
         "Speaker man", // TODO: Improve this test data
         { "I'm a speaker" },
         {
            //{ "Exit program", new AllegroFlare::DialogTree::NodeOptions::ExitProgram() }
            { "Exit dialog", new AllegroFlare::DialogTree::NodeOptions::ExitDialog() }
         }
      ));

   // Use our assembled node_bank
   dialog_system.set_dialog_node_bank(node_bank);
   dialog_system.initialize();

   // Start on the wait node
   dialog_system.activate_dialog_node_by_name("wait_node_1");
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("wait_node_1", dialog_system.get_active_dialog_node_name());
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("wait_node_1", dialog_system.get_active_dialog_node_name());
   al_rest(1.2);
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("next_node", dialog_system.get_active_dialog_node_name());

   // Shutdown our test context
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


