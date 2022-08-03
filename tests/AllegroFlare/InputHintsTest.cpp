
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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
   std::string expected_error_message =
      "InputHints::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(input_hints.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_InputHintsTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::InputHints input_hints(&get_font_bin_ref());
   input_hints.render();
   al_flip_display();
}

