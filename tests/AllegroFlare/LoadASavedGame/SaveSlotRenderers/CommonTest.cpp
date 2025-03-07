#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Common.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest : public ::testing::Test {};
class AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic;
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic;
   EXPECT_THROW_GUARD_ERROR(
      basic.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic;
   EXPECT_THROW_GUARD_ERROR(
      basic.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest,
   render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic;
   EXPECT_THROW_GUARD_ERROR(
      basic.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTest, render__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic;
   EXPECT_THROW_GUARD_ERROR(
      basic.render(),
      "AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common::render",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_LoadASavedGame_SaveSlotRenderers_CommonTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common basic(
         &get_bitmap_bin_ref(),
         &get_font_bin_ref(),
         "scene3-01.jpg"
      );
   basic.set_x(1920/2);
   basic.set_y(1080/2);
   basic.render();
   draw_crosshair(basic.get_x(), basic.get_y());
   al_flip_display();
   sleep_for(1);
}


