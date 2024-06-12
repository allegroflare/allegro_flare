
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_DialogButtonTest : public ::testing::Test
{};

class AllegroFlare_Elements_DialogButtonTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/DialogButton.hpp>

#include <allegro5/allegro_primitives.h>


TEST_F(AllegroFlare_Elements_DialogButtonTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogButton dialog_button;
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogButton dialog_button;
   std::string expected_error_message =
      "DialogButton::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_button.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::DialogButton dialog_button;
   std::string expected_error_message =
      "DialogButton::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_button.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, DISABLED__render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::Elements::DialogButton dialog_button;
   std::string expected_error_message =
      "DialogButton::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_button.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, render__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogButton dialog_button;
   std::string expected_error_message =
      "DialogButton::render: error: guard \"al_is_ttf_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_button.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogButton dialog_button;
   std::string expected_error_message =
      "DialogButton::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_button.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogButtonTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogButton dialog_button(&get_font_bin_ref());
   dialog_button.render();
}


TEST_F(AllegroFlare_Elements_DialogButtonTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_button_as_expected)
{
   AllegroFlare::Elements::DialogButton dialog_button(&get_font_bin_ref());
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   dialog_button.set_started_at(al_get_time());

   for (int passes=0; passes<=20; passes++)
   {
      clear();

      showcased_placement.start_transform();
      dialog_button.render();
      showcased_placement.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogButtonTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__when_at_last_advance__will_draw_the_button_as_expected)
{
   AllegroFlare::Elements::DialogButton dialog_button(&get_font_bin_ref());
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   dialog_button.set_at_last_advance(true);
   dialog_button.set_started_at(al_get_time());

   for (int passes=0; passes<=20; passes++)
   {
      clear();

      showcased_placement.start_transform();
      dialog_button.render();
      showcased_placement.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogButtonTest, test_suite_ends_without_allegro_initialized)
{
   EXPECT_EQ(false, al_is_system_installed());
}


