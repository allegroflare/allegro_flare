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

   sleep_for(1);
}


