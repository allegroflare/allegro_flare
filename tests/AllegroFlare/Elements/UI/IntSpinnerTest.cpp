#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/UI/IntSpinner.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_UI_IntSpinnerTest : public ::testing::Test {};
class AllegroFlare_Elements_UI_IntSpinnerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_UI_IntSpinnerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
}


TEST_F(AllegroFlare_Elements_UI_IntSpinnerTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
   std::string expected_error_message =
      "IntSpinner::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(int_spinner.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_UI_IntSpinnerTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
   std::string expected_error_message =
      "IntSpinner::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(int_spinner.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_IntSpinnerTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
   std::string expected_error_message =
      "IntSpinner::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(int_spinner.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_UI_IntSpinnerTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
   std::string expected_error_message =
      "IntSpinner::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(int_spinner.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_UI_IntSpinnerTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   float display_w = 1920;
   float cx = display_w/2;
   float cy = 1080/2;
   float grid_units = 7;
   float dw = int(display_w / grid_units);
   AllegroFlare::Elements::UI::IntSpinner disabled_int_spinner(&get_font_bin_ref(), cx - dw*2, cy);
   AllegroFlare::Elements::UI::IntSpinner enabled_int_spinner(&get_font_bin_ref(), cx - dw*1, cy);
   AllegroFlare::Elements::UI::IntSpinner active_int_spinner(&get_font_bin_ref(), cx - dw*0, cy);
   AllegroFlare::Elements::UI::IntSpinner int_spinner_with_small_number(&get_font_bin_ref(), cx + dw*1, cy);
   AllegroFlare::Elements::UI::IntSpinner int_spinner_with_large_number(&get_font_bin_ref(), cx + dw*2, cy);

   disabled_int_spinner.set_state(AllegroFlare::Elements::UI::IntSpinner::STATE_DISABLED);
   enabled_int_spinner.set_state(AllegroFlare::Elements::UI::IntSpinner::STATE_ENABLED);
   active_int_spinner.set_state(AllegroFlare::Elements::UI::IntSpinner::STATE_ACTIVE_FOCUS);
   int_spinner_with_small_number.set_number(3);
   int_spinner_with_large_number.set_number(18765);

   disabled_int_spinner.render();
   enabled_int_spinner.render();
   active_int_spinner.render();
   int_spinner_with_small_number.render();
   int_spinner_with_large_number.render();

   al_flip_display();
   sleep_for(1);
}


