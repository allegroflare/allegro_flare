#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Prototypes_TileDrive_Hud_HudTest : public ::testing::Test {};
class AllegroFlare_Prototypes_TileDrive_Hud_HudTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/TileDrive/Hud/Hud.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
}


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
   EXPECT_THROW_GUARD_ERROR(
      hud.initialize(),
      "AllegroFlare::Prototypes::TileDrive::Hud::Hud::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTest, initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
   EXPECT_THROW_GUARD_ERROR(
      hud.initialize(),
      "AllegroFlare::Prototypes::TileDrive::Hud::Hud::initialize",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTest, initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
   EXPECT_THROW_GUARD_ERROR(
      hud.initialize(),
      "AllegroFlare::Prototypes::TileDrive::Hud::Hud::initialize",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
   EXPECT_THROW_GUARD_ERROR(
      hud.initialize(),
      "AllegroFlare::Prototypes::TileDrive::Hud::Hud::initialize",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud(&get_font_bin_ref());
   hud.initialize();
   hud.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Prototypes_TileDrive_Hud_HudTestWithAllegroRenderingFixture,
   CAPTURE__render__will_work_as_expected)
{
   AllegroFlare::Prototypes::TileDrive::Hud::Hud hud(&get_font_bin_ref());
   hud.initialize();

   hud.show_win_slate();

   hud.render();
   al_flip_display();

   sleep_for(1);
}


