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
   EXPECT_THROW_GUARD_ERROR(
      slider_toggle.render(),
      "AllegroFlare::Elements::UI::SliderToggle::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   EXPECT_THROW_GUARD_ERROR(
      slider_toggle.render(),
      "AllegroFlare::Elements::UI::SliderToggle::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   EXPECT_THROW_GUARD_ERROR(
      slider_toggle.render(),
      "AllegroFlare::Elements::UI::SliderToggle::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_SliderToggleTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   EXPECT_THROW_GUARD_ERROR(
      slider_toggle.render(),
      "AllegroFlare::Elements::UI::SliderToggle::render",
      "font_bin"
   );
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


