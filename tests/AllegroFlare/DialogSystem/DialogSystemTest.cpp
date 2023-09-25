#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>


class AllegroFlare_DialogSystem_DialogSystemTest : public ::testing::Test {};
class AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


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

   dialog_system.spawn_basic_dialog({ "Hello, basic dialog", "Good to see you today" });

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
   dialog_system.initialize();

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.spawn_dialog_by_name("start_node");

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
   dialog_system.initialize();

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.spawn_dialog_by_name("start_node");

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
   std::string dialog_filename = get_fixtures_path() + "/dialogs/branching_dialog_with_long_text.yml";
   std::string node_name_to_start = "start_node";
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
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
                  dialog_system.spawn_dialog_by_name(node_name_to_start);
                  EXPECT_EQ(true, dialog_system.get_switched_in()); // TODO: Move this to another test
               break;

               case ALLEGRO_KEY_UP:
                  dialog_system.move_dialog_cursor_position_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  dialog_system.move_dialog_cursor_position_down();
               break;

               case ALLEGRO_KEY_LEFT:
                  dialog_system.move_dialog_cursor_position_left();
               break;

               case ALLEGRO_KEY_RIGHT:
                  dialog_system.move_dialog_cursor_position_right();
               break;

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


