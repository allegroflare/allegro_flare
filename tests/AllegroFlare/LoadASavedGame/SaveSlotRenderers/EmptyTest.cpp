#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Empty.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty;
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty;
   EXPECT_THROW_GUARD_ERROR(
      empty.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty;
   EXPECT_THROW_GUARD_ERROR(
      empty.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty;
   EXPECT_THROW_GUARD_ERROR(
      empty.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty;
   EXPECT_THROW_GUARD_ERROR(
      empty.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_EmptyTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty empty(&get_font_bin_ref());
   empty.render();
   al_flip_display();
   sleep_for(1);
}


