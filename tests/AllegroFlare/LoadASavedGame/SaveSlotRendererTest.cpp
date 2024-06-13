#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>


class AllegroFlare_LoadASavedGame_SaveSlotRendererTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_SaveSlotRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer(&get_font_bin_ref());
   AllegroFlare::LoadASavedGame::SaveSlots::Basic basic_save_slot;
   save_slot_renderer.render(&basic_save_slot);
   al_flip_display();
   sleep_for(1);
}


