
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_InputHintsTest : public ::testing::Test
{};

class AllegroFlare_InputHintsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/InputHints.hpp>


TEST_F(AllegroFlare_InputHintsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InputHints input_hints;
}


TEST_F(AllegroFlare_InputHintsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::InputHints input_hints;
   EXPECT_THROW_GUARD_ERROR(
      input_hints.render(),
      "AllegroFlare::InputHints::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_InputHintsTest, render__respects_text_color)
{
   // TODO
}


TEST_F(AllegroFlare_InputHintsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::InputHints input_hints(&get_font_bin_ref());
   al_clear_to_color(ALLEGRO_COLOR{0.2, 0.2, 0.21, 1.0});
   input_hints.render();
   al_flip_display();
}


TEST_F(AllegroFlare_InputHintsTestWithAllegroRenderingFixture, render__with_the_placeholder_tokens__will_not_blow_up)
{
   AllegroFlare::InputHints input_hints(&get_font_bin_ref());
   input_hints.set_input_hints_tokens(AllegroFlare::InputHints::build_placeholder_input_hints_tokens());
   al_clear_to_color(ALLEGRO_COLOR{0.2, 0.2, 0.21, 1.0});
   input_hints.render();
   al_flip_display();
}


TEST_F(AllegroFlare_InputHintsTestWithAllegroRenderingFixture,
   build_placeholder_input_hints__builds_a_list_of_expected_hints)
{
   std::vector<std::pair<std::string, std::string>> expected_placeholder_hints_tokens = {
      { "[W/A/S/D]", "Move cursor" },
      { "[N/P]",     "Next/Previous entity" },
      { "[Shift+8]", "Capture screenshot" },
      { "[PAD +/-]", "Zoom" },
      { "[ESC]",     "Toggle Inventory" },
      { "[-/+]",     "Change time of day" },
   };

   std::vector<std::pair<std::string, std::string>> actual_placeholder_hints_tokens =
      AllegroFlare::InputHints::build_placeholder_input_hints_tokens();

   EXPECT_EQ(expected_placeholder_hints_tokens, actual_placeholder_hints_tokens);
}


TEST_F(AllegroFlare_InputHintsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render__keyboard_key_combo_tokens__when_they_are_present)
{
   std::vector<std::string> keyboard_key_combo_tokens = {
      "I", "%SPACER", "LABEL>>", "Toggle inventory", 
      "%SEPARATOR",
      "X", "%SPACER", "LABEL>>", "Exit", 
      "%SEPARATOR",
      "P", "%SPACER", "LABEL>>", "Pause", 
      "%SEPARATOR",
      "SHIFT", "%SPACE", "%PLUS", "%SPACE", "ESC", "%SPACER", "LABEL>>", "Exit program", 
   };

   AllegroFlare::InputHints input_hints(&get_font_bin_ref());
   input_hints.set_keyboard_key_combo_tokens(keyboard_key_combo_tokens);
   al_clear_to_color(ALLEGRO_COLOR{0.2, 0.2, 0.21, 1.0});
   input_hints.render();
   al_flip_display();
}


