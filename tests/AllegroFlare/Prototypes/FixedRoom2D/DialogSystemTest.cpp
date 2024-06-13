#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/FixedRoom2D/DialogSystem.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
}



TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest,
   initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTest, initialize__without_an_event_emitter__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   dialog_system.set_font_bin(&font_bin);
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::Prototypes::FixedRoom2D::DialogSystem::initialize",
      "event_emitter"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   dialog_system.render();
   al_flip_display();
   sleep_for(1);
}


