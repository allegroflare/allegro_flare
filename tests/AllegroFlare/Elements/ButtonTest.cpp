
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_ButtonTest : public ::testing::Test
{};

class AllegroFlare_Elements_ButtonTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Button.hpp>

#include <allegro5/allegro_primitives.h>


TEST_F(AllegroFlare_Elements_ButtonTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Button button;
}


TEST_F(AllegroFlare_Elements_ButtonTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Button button;
   std::string expected_error_message =
      "Button::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(button.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_ButtonTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::Button button;
   std::string expected_error_message =
      "Button::render: error: guard \"al_is_font_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(button.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ButtonTest, DISABLED__render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::Elements::Button button;
   std::string expected_error_message =
      "Button::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(button.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ButtonTest, render__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_primitives_addon();
   AllegroFlare::Elements::Button button;
   std::string expected_error_message =
      "Button::render: error: guard \"al_is_ttf_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(button.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ButtonTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_primitives_addon();
   AllegroFlare::Elements::Button button;
   std::string expected_error_message =
      "Button::render: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(button.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ButtonTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::Button button(&get_font_bin_ref());
   button.render();
}


TEST_F(AllegroFlare_Elements_ButtonTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_button_as_expected)
{
   AllegroFlare::Elements::Button button(&get_font_bin_ref());
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   button.set_started_at(al_get_time());

   for (int passes=0; passes<=20; passes++)
   {
      clear();

      showcased_placement.start_transform();
      button.render();
      draw_crosshair(0, 0);
      showcased_placement.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_ButtonTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__with_different_alignment_strategies__will_render_as_expected)
{
   AllegroFlare::Elements::Button button(&get_font_bin_ref());
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   float position_origin_x = showcased_placement.position.x;
   button.set_started_at(al_get_time());

   for (int passes=0; passes<=30; passes++)
   {
      clear();

      showcased_placement.position.x = position_origin_x - 200;
      showcased_placement.start_transform();
      //button.set_alignment_stragegy(AllegroFlare::Elements::Button::Alignments::ALIGNED_AT_TEXT_START);
      button.render();
      draw_crosshair(0, 0);
      showcased_placement.restore_transform();

      showcased_placement.position.x = position_origin_x + 200;
      showcased_placement.start_transform();
      //button.set_alignment_stragegy(AllegroFlare::Elements::Button::Alignments::CENTERED);
      button.render();
      draw_crosshair(0, 0);
      showcased_placement.restore_transform();

      al_flip_display();

      sleep_for_frame();
   }
}


