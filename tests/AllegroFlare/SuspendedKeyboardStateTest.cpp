#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/SuspendedKeyboardState.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


static void draw_key_names_vertically(ALLEGRO_FONT *font, std::string label, float x, float y, std::vector<uint32_t> keycodes)
{
   // Draw column label
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 0.85, 1}, x, 0, ALLEGRO_ALIGN_CENTER, label.c_str());

   // Draw key names
   int line_spacing = 40;
   int line = 0;
   for (auto &key : keycodes)
   {
      al_draw_text(
            font,
            ALLEGRO_COLOR{0.85, 1, 1, 1},
            x,
            y + 50 + line_spacing * line,
            ALLEGRO_ALIGN_CENTER,
            al_keycode_to_name(key)
         );
      line++;
   }
}


class AllegroFlare_SuspendedKeyboardStateTest : public ::testing::Test {};
class AllegroFlare_SuspendedKeyboardStateTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};
class AllegroFlare_SuspendedKeyboardStateTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture {};


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SuspendedKeyboardState input_state;
}


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, capture_initial_keyboard_state__will_not_blow_up)
{
   al_init();
   al_install_keyboard();

   AllegroFlare::SuspendedKeyboardState input_state;
   input_state.capture_initial_keyboard_state();

   al_uninstall_keyboard();
   al_uninstall_system();
}


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, capture_subsequent_keyboard_state__will_not_blow_up)
{
   al_init();
   al_install_keyboard();

   AllegroFlare::SuspendedKeyboardState input_state;
   input_state.capture_subsequent_keyboard_state();

   al_uninstall_keyboard();
   al_uninstall_system();
}


/*
TEST_F(AllegroFlare_SuspendedKeyboardStateTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::SuspendedKeyboardState input_state;
   std::string expected_error_message =
      "InputState::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(input_state.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::SuspendedKeyboardState input_state;
   std::string expected_error_message =
      "InputState::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(input_state.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::SuspendedKeyboardState input_state;
   std::string expected_error_message =
      "InputState::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(input_state.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_SuspendedKeyboardStateTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::SuspendedKeyboardState input_state;
   std::string expected_error_message =
      "InputState::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(input_state.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


/*
TEST_F(AllegroFlare_SuspendedKeyboardStateTestWithAllegroRenderingFixture,
   INTERACTIVE__will_work_capture_keyboard_states_as_expected)
{
   AllegroFlare::Placement2D subject_placement;
   subject_placement.size = { 1920, 1080, };
   subject_placement.align = { 0.5, 0.5 };
   subject_placement.position = { 0, 0 };

   ALLEGRO_FONT *font = get_user_prompt_font();
   AllegroFlare::SuspendedKeyboardState input_state;

   clear();

   // Draw prompt text
   subject_placement.start_reverse_transform();
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, ALLEGRO_ALIGN_CENTER, "Press any key(s)");
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 26, ALLEGRO_ALIGN_CENTER, "Press ENTER when keys are pressed");
   subject_placement.restore_transform();

   al_flip_display();
   sleep_for(1);
}
*/


#include <AllegroFlare/Camera2D.hpp>

TEST_F(AllegroFlare_SuspendedKeyboardStateTestWithInteractionFixture,
   INTERACTIVE__will_capture_keyboard_state_changes_as_expected)
{
   // Setup our resources
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = get_user_prompt_font();

   // Build our subject
   AllegroFlare::SuspendedKeyboardState input_state;

   // Setup camera variables
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };

   while(!interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update the current pressed keys
            ALLEGRO_KEYBOARD_STATE current_keyboard_state;
            al_get_keyboard_state(&current_keyboard_state);
            std::vector<uint32_t> keys_pressed;
            uint32_t key_min = 0;
            for (int al_keycode=key_min; al_keycode<ALLEGRO_KEY_MAX; al_keycode++)
            {
               if (al_key_down(&current_keyboard_state, al_keycode)) keys_pressed.push_back(al_keycode);
            }

            // Clear the surface and setup the camera
            clear();
            camera.start_reverse_transform();

            // Show prompt text and keys pressed
            al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, -200, ALLEGRO_ALIGN_CENTER, "Press any key(s)");
            al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, -200+34, ALLEGRO_ALIGN_CENTER, "Press ENTER when keys are pressed");

            // Show the currently pressed key names
            draw_key_names_vertically(font, "now", -600, 50, keys_pressed);

            // Show the initial state key names
            if (input_state.get_initial_keyboard_state_is_captured())
            {
               draw_key_names_vertically(font, "initial", -300, 50, input_state.get_keys_pressed_in_initial_keyboard_state());
            }

            // Show the subsequent state key names
            if (input_state.get_subsequent_keyboard_state_is_captured())
            {
               draw_key_names_vertically(font, "subsequent", 0, 50, input_state.get_keys_pressed_in_subsequent_keyboard_state());
            }

            if (input_state.get_keyboard_state_changes_are_calculated())
            {
               draw_key_names_vertically(font, "pressed", 300, 50, input_state.get_keys_pressed());

               draw_key_names_vertically(font, "released", 600, 50, input_state.get_keys_released());
            }

            // Draw the interactive test text
            interactive_test_render_status();

            // Restore the camera
            camera.restore_transform();

            // Flip the display
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ENTER:
                  if (!input_state.get_initial_keyboard_state_is_captured())
                  {
                     input_state.capture_initial_keyboard_state();
                  }
                  else if (!input_state.get_subsequent_keyboard_state_is_captured())
                  {
                     input_state.capture_subsequent_keyboard_state();
                     input_state.calculate_keyboard_state_changes();
                  }
               break;
            }
         }
         break;
      }
   }

   //al_destroy_timer(primary_timer);
}


