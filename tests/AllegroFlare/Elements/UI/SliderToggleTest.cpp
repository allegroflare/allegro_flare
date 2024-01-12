#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/UI/SliderToggle.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_UI_SliderToggleTest : public ::testing::Test {};
class AllegroFlare_Elements_UI_SliderToggleTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   std::string expected_error_message =
      "SliderToggle::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(slider_toggle.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   std::string expected_error_message =
      "SliderToggle::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(slider_toggle.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   std::string expected_error_message =
      "SliderToggle::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(slider_toggle.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   std::string expected_error_message =
      "SliderToggle::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(slider_toggle.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_UI_SliderToggleTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::UI::SliderToggle on_slider_toggle(&get_font_bin_ref(), 1920/2 - 200, 1080/2);
   AllegroFlare::Elements::UI::SliderToggle off_slider_toggle(&get_font_bin_ref(), 1920/2 + 200, 1080/2);
   off_slider_toggle.set_onoff(false);

   on_slider_toggle.render();
   off_slider_toggle.render();

   al_flip_display();
   sleep_for(1);
}


