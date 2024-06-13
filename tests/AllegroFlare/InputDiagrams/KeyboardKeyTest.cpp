
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_InputDiagrams_KeyboardKeyTest : public ::testing::Test
{};

class AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

MATCHER(IsEven, "") { return (arg % 2) == 0; }

#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key;
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key;
   EXPECT_THROW_GUARD_ERROR(
      keyboard_key.render(),
      "AllegroFlare::InputDiagrams::KeyboardKey::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(&get_font_bin_ref());
   AllegroFlare::Placement2D placement = build_centered_placement(100, 80);
   placement.start_transform();
   keyboard_key.render();
   placement.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture,
   CAPTURE__render__will_position_the_diagrams_x_and_y)
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(&get_font_bin_ref(), "300, 200");
   keyboard_key.set_x(300);
   keyboard_key.set_y(200);
   AllegroFlare::Placement2D placement = build_centered_placement();
   placement.start_transform();
   keyboard_key.render();
   placement.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_keyboard_key_str)
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(&get_font_bin_ref(), "SHIFT");
   AllegroFlare::Placement2D placement = build_centered_placement(100, 80);
   placement.start_transform();
   keyboard_key.render();
   placement.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture,
   CAPTURE__various_examples)
{
   std::vector<std::string> test_keyboard_input_keys = { "SHIFT", "A", ".", "/", "PGUP" };

   for (int i=0; i<test_keyboard_input_keys.size(); i++)
   {
      std::string test_keyboard_input_key = test_keyboard_input_keys[i];
      AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(&get_font_bin_ref(), test_keyboard_input_key);
      float keyboard_key_box_height = keyboard_key.get_keyboard_key_box_height();
      AllegroFlare::Placement2D placement = build_centered_placement(0, 0);
      placement.position.y += (i * keyboard_key_box_height * 1.5)
                           - (test_keyboard_input_keys.size() * keyboard_key_box_height / 2)
                           ;
      placement.start_transform();

      keyboard_key.render();

      placement.restore_transform();
   }

   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture,
   calculate_width__will_return_the_width_of_the_diagram)
{
   std::vector<std::tuple<std::string, int>> keyboard_input_keys_and_expected_widths = {
      { "SHIFT", 74 },
      { "A", 42 },
      { ".", 42 },
      { "/", 42 },
      { "PGUP", 72 },
   };

   for (auto &keyboard_input_key_and_expected_width : keyboard_input_keys_and_expected_widths)
   {
      std::string keyboard_input_key = std::get<0>(keyboard_input_key_and_expected_width);
      float expected_diagram_width= std::get<1>(keyboard_input_key_and_expected_width);
      AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(&get_font_bin_ref(), keyboard_input_key);

      EXPECT_EQ(expected_diagram_width, keyboard_key.calculate_width());
   }
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyTestWithAllegroRenderingFixture,
   calculate_width__will_guarantee_a_width_that_is_even)
{
   std::vector<std::string> keyboard_input_keys_to_test = {
      ".", "A", "SHIFT", "CTRL", "PAGE UP",
   };

   for (auto &keyboard_input_key_to_test : keyboard_input_keys_to_test)
   {
      AllegroFlare::InputDiagrams::KeyboardKey keyboard_input_key(&get_font_bin_ref(), keyboard_input_key_to_test);
      EXPECT_THAT(keyboard_input_key.calculate_width(), IsEven());
   }
}


