#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest : public ::testing::Test {};
class AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, initialized__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message =
      "SoftwareKeyboard::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message =
      "SoftwareKeyboard::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message =
      "SoftwareKeyboard::initialize: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message =
      "SoftwareKeyboard::initialize: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.render();
   al_flip_display();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   increment_cursor_pos__will_move_the_cursor_forward_by_one)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   increment_cursor_pos__will_loop_around_to_the_front_when_greater_than_the_number_of_keys)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   decrement_cursor_pos__will_move_the_cursor_backward_by_one)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   decrement_cursor_pos__will_loop_around_to_the_back_when_less_than_zero)
{
   // TODO
}


