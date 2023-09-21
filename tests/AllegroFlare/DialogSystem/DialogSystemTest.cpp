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
   dialog_system.spawn_named_dialog("start_node");

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
   CAPTURE__load_dialog_node_bank_from_file__with_a_branching_dialog_that_include_choices__will_not_blow_up)
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
   dialog_system.spawn_named_dialog("start_node");

   int NUM_PASSES = 20;
   int passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.move_dialog_cursor_position_down();
   dialog_system.dialog_advance();
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


