#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Basic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic;
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_BasicTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic basic(&get_font_bin_ref());
   basic.render();
   al_flip_display();
   sleep_for(1);
}


