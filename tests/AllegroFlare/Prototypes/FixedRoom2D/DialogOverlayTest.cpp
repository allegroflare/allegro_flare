#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/FixedRoom2D/DialogOverlay.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay;
   std::string expected_error_message =
      "DialogOverlay::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_overlay.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay;
   std::string expected_error_message =
      "DialogOverlay::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_overlay.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay;
   std::string expected_error_message =
      "DialogOverlay::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_overlay.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay;
   std::string expected_error_message =
      "DialogOverlay::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_overlay.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_DialogOverlayTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogOverlay dialog_overlay(&get_font_bin_ref());
   dialog_overlay.render();
   al_flip_display();
   sleep_for(1);
}


