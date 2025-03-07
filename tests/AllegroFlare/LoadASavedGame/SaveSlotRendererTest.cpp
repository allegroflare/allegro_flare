#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Common.hpp>


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


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer;
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer(&bitmap_bin);
   EXPECT_THROW_GUARD_ERROR(
      save_slot_renderer.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__with_as_Basic_type__will_render_as_expected)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer(&get_bitmap_bin_ref(), &get_font_bin_ref());
   AllegroFlare::LoadASavedGame::SaveSlots::Basic basic_save_slot;
   save_slot_renderer.render(&basic_save_slot);
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__with_as_Common_type__will_render_as_expected)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderer save_slot_renderer(&get_bitmap_bin_ref(), &get_font_bin_ref());
   AllegroFlare::LoadASavedGame::SaveSlots::Common common_save_slot;
   common_save_slot.screenshot_of_gameplay_at_save_identifier = "scene3-01.jpg";
   common_save_slot.location_of_save = "Southern Outpost";
   common_save_slot.date_and_time_of_save = "3/7/2025 4:18PM";
   common_save_slot.time_since_text = "3 minutes";
   save_slot_renderer.set_slot_width(AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::DEFAULT_WIDTH);
   save_slot_renderer.set_slot_height(AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::DEFAULT_HEIGHT);
   save_slot_renderer.render(&common_save_slot);
   al_flip_display();
   sleep_for(1);
}


