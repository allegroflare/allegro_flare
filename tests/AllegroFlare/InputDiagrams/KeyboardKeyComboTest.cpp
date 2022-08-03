
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_InputDiagrams_KeyboardKeyComboTest : public ::testing::Test
{};

class AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key;
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key;
   std::string expected_error_message =
      "KeyboardKeyCombo::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(keyboard_key.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key(&get_font_bin_ref());
   AllegroFlare::Placement2D placement = build_centered_placement(100, 80);
   placement.start_transform();
   keyboard_key.render();
   placement.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_keyboard_key_str)
{
   // TODO
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   CAPTURE__various_examples)
{
   // TODO
}


TEST_F(AllegroFlare_InputDiagrams_KeyboardKeyComboTestWithAllegroRenderingFixture,
   calculate_width__will_return_the_width_of_the_diagram)
{
   // TODO
}


