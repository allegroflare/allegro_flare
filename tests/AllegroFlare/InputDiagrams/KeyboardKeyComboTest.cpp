
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_InputDiagrams_KeyboardKeyComboTest : public ::testing::Test
{};

class AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

MATCHER(IsEven, "") { return (arg % 2) == 0; }

#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key;
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key;
   EXPECT_THROW_GUARD_ERROR(
      keyboard_key.render(),
      "AllegroFlare::InputDiagrams::KeyboardKeyCombo::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key(&get_font_bin_ref());
   keyboard_key.render();
   SUCCEED();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_keyboard_combo_tokens)
{
   std::vector<std::vector<std::string>> test_keyboard_input_key_combos = {
      { { "SHIFT", "%SPACE", "%PLUS", "%SPACE", "N", "%SPACER", "LABEL>>", "Create new" } },
      { { "W", "%SPACE", "A", "%SPACE", "S", "%SPACE", "D", "%SPACER", "LABEL>>", "Move player" } },
      { { "PAGE UP", "%SPACE", "%SLASH", "%SPACE", "PAGE DOWN" } },
      { { "CTRL", "%SPACE", "%PLUS", "%SPACE", "Z", "%SPACE", "%SLASH", "%SPACE", "Y",
          "%SPACER", "LABEL>>", "Undo / Redo" } },
      { { "I", "%SPACER", "LABEL>>", "Toggle inventory", 
          "%SEPARATOR",
          "X", "%SPACER", "LABEL>>", "Exit", 
          "%SEPARATOR",
          "P", "%SPACER", "LABEL>>", "Pause", 
          } },
   };

   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key_combo(&get_font_bin_ref());

   for (int i=0; i<test_keyboard_input_key_combos.size(); i++)
   {
      std::vector<std::string> test_keyboard_input_key_combo = test_keyboard_input_key_combos[i];
      keyboard_key_combo.set_keyboard_combo_tokens(test_keyboard_input_key_combo);
      float keyboard_key_box_height = keyboard_key_combo.get_keyboard_key_box_height();
      AllegroFlare::Placement2D placement = build_centered_placement(0, 0);
      placement.position.y += (i * keyboard_key_box_height * 1.5)
                           - (test_keyboard_input_key_combos.size() * keyboard_key_box_height / 2)
                           ;
      placement.start_transform();

      keyboard_key_combo.render();

      placement.restore_transform();
   }

   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   calculate_width__will_return_the_width_of_the_diagram)
{
   std::vector<std::tuple<std::vector<std::string>, int>> keyboard_input_key_combos_and_expected_widths = {
      { { "A" }, 42 },
      { { "." }, 42 },
      { { "SHIFT", "%SPACE", "%PLUS", "%SPACE", "A" }, 152 },
   };

   for (auto &keyboard_input_key_combo_and_expected_width : keyboard_input_key_combos_and_expected_widths)
   {
      std::vector<std::string> keyboard_input_key_tokens = std::get<0>(keyboard_input_key_combo_and_expected_width);
      float expected_diagram_width = std::get<1>(keyboard_input_key_combo_and_expected_width);
      AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key_combo(&get_font_bin_ref(), keyboard_input_key_tokens);

      EXPECT_EQ(expected_diagram_width, keyboard_key_combo.render(false));
   }
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   calculate_width__will_guarantee_the_width_is_calculated_as_an_even_number)
{
   std::vector<std::vector<std::string>> keyboard_key_combos_to_test = {
      { "." },
      { "A" },
      { "%PLUS", },
      { "SHIFT", "%SPACE", "%PLUS", "%SPACE", "A" },
      { "SHIFT", "%SPACER", "%SLASH", "A" },
   };

   for (auto &keyboard_key_combo_to_test : keyboard_key_combos_to_test)
   {
      AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key_combo(&get_font_bin_ref(), keyboard_key_combo_to_test);
      EXPECT_THAT(keyboard_key_combo.calculate_width(), IsEven());
   }
}


