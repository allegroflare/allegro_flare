#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/SuspendedJoystickState.hpp>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Camera2D.hpp>
#include <sstream>


class AllegroFlare_SuspendedJoystickStateTest : public ::testing::Test {};
class AllegroFlare_SuspendedJoystickStateTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   ALLEGRO_JOYSTICK *joystick;
   AllegroFlare_SuspendedJoystickStateTestWithAllegroRenderingFixture()
     : joystick(nullptr)
   {}
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      al_install_joystick(); // TODO: Check return value
      al_reconfigure_joysticks();
      if (al_get_num_joysticks() == 0)
      {
         display_skipping_joystick_test_message();
         GTEST_SKIP() << "There are no joysticks connected to perform this test. To run this test, plug in a joystick "
                         "and rerun the test.";
      }
      joystick = al_get_joystick(0);
   }
   virtual void TearDown() override
   {
      joystick = nullptr;
      al_uninstall_joystick();
      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
   void display_skipping_joystick_test_message()
   {
      clear();
      AllegroFlare::Camera2D camera;
      camera.size = { 1920, 1080 };
      ALLEGRO_FONT *font = get_user_prompt_font();
      std::string skip_message = "There are no joysticks connected to perform this test. To run this test, plug in a "
                                 "joystick and rerun the test.";
      camera.start_reverse_transform();
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, ALLEGRO_ALIGN_CENTER, skip_message.c_str());
      camera.restore_transform();

      al_flip_display();
      al_rest(1);
   }
   void draw_joystick_status_column(
         std::string label,
         float x,
         float y,
         std::map<std::pair<int, int>, std::pair<float, float>> sticks_moved,
         std::vector<uint32_t> buttons_pressed = {},
         std::vector<uint32_t> buttons_released = {}
      )
   {
      ALLEGRO_FONT *font = get_user_prompt_font();
      int line_spacing = 40;
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 0.85, 1}, x, y, ALLEGRO_ALIGN_CENTER, label.c_str());

      y += line_spacing;
      int axes_status_vertical_height = draw_joystick_axes_vertically(x, y, sticks_moved);
      y += axes_status_vertical_height;
      if (!buttons_pressed.empty())
      {
         draw_joystick_buttons_horizontally("pressed", x, y, buttons_pressed);
         y += line_spacing * 2.5;
      }
      if (!buttons_released.empty())
      {
         draw_joystick_buttons_horizontally("released", x, y, buttons_released);
      }
   }
   void draw_joystick_buttons_horizontally(std::string label, float x, float y, std::vector<uint32_t> buttons)
   {
      ALLEGRO_FONT *font = get_user_prompt_font();
      int line_spacing = 40;
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 0.85, 1}, x, y, ALLEGRO_ALIGN_CENTER, label.c_str());
      std::stringstream buttons_listed;
      for (auto &button : buttons)
      {
         buttons_listed << button;
         if (button != buttons.back()) buttons_listed << ", ";
      }
      al_draw_text(
            font,
            ALLEGRO_COLOR{1, 1, 0.85, 1},
            x,
            y+line_spacing,
            ALLEGRO_ALIGN_LEFT,
            buttons_listed.str().c_str()
         );
   }
   void draw_joystick_buttons_vertically(std::string label, float x, float y, std::vector<uint32_t> buttons)
   {
      ALLEGRO_FONT *font = get_user_prompt_font();
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 0.85, 1}, x, y, ALLEGRO_ALIGN_CENTER, label.c_str());

      int line_spacing = 40;
      int line = 0;
      for (auto &button : buttons)
      {
         al_draw_text(
               font,
               ALLEGRO_COLOR{0.85, 1, 1, 1},
               x,
               y + 50 + line_spacing * line,
               ALLEGRO_ALIGN_CENTER,
               al_get_joystick_button_name(joystick, button)
            );
         line++;
      }
   }
   int draw_joystick_axes_vertically(
         float x,
         float y,
         std::map<std::pair<int, int>, std::pair<float, float>> sticks
      )
   {
      ALLEGRO_FONT *font = get_any_font();

      int line_spacing = 100;
      int radius = 40;
      float inner_radius = radius * 0.5;
      int line = 0;
      int stick_num, axis_num;
      float axis_delta, axis_position;
      for (auto &stick : sticks)
      {
         std::tie(stick_num, axis_num) = stick.first;
         std::tie(axis_delta, axis_position) = stick.second;
         float circle_x = x;
         float circle_y = y + line_spacing / 2 + line_spacing * line;
         float delta_position_offset_x = (axis_position - axis_delta) * radius;
         float current_position_offset_x = axis_position * radius;
         al_draw_circle(circle_x, circle_y, radius, ALLEGRO_COLOR{0.35, 0.55, 0.8, 0.8}, 1.5);
         al_draw_circle(
               circle_x + delta_position_offset_x,
               circle_y,
               inner_radius-3,
               ALLEGRO_COLOR{0.85, 0.75, 0.2, 1},
               3.0
            );
         al_draw_circle(
               circle_x + current_position_offset_x,
               circle_y,
               inner_radius,
               ALLEGRO_COLOR{0.55, 0.75, 1, 1},
               3.0
            );

         std::stringstream label;
         label << "stick: " << stick_num << " axis: " << axis_num << "\npos: " << axis_position
               << "\ndelta: " << axis_delta<< std::endl;
         int text_line_height = al_get_font_line_height(font) - 1;
         al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{1, 1, 0.85, 1},
               x + radius * 2,
               y + line_spacing / 2 - text_line_height * 1.25 + line * line_spacing,
               1000,
               text_line_height,
               ALLEGRO_ALIGN_LEFT,
               label.str().c_str()
            );
         line++;
      }
      return line * line_spacing;
   }
};



TEST_F(AllegroFlare_SuspendedJoystickStateTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SuspendedJoystickState suspended_joystick_state;
}


/*
TEST_F(AllegroFlare_SuspendedJoystickStateTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::SuspendedJoystickState suspended_joystick_state;
   std::string expected_error_message =
      "SuspendedJoystickState::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(suspended_joystick_state.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_SuspendedJoystickStateTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::SuspendedJoystickState suspended_joystick_state;
   std::string expected_error_message =
      "SuspendedJoystickState::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(suspended_joystick_state.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_SuspendedJoystickStateTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::SuspendedJoystickState suspended_joystick_state;
   std::string expected_error_message =
      "SuspendedJoystickState::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(suspended_joystick_state.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_SuspendedJoystickStateTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::SuspendedJoystickState suspended_joystick_state;
   std::string expected_error_message =
      "SuspendedJoystickState::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(suspended_joystick_state.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


TEST_F(AllegroFlare_SuspendedJoystickStateTestWithAllegroRenderingFixture,
   CAPTURE__INTERACTIVE__will_capture_joystick_state_changes_as_expected)
{
   al_install_keyboard(); // TODO: Check return value
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_joystick_event_source());

   // Setup our resources
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = get_user_prompt_font();

   // Build our subject
   AllegroFlare::SuspendedJoystickState input_state;
   input_state.set_joystick(joystick);

   // Setup camera variables
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update the current pressed keys
            static std::map<std::pair<int, int>, std::pair<float, float>> current_sticks;
            ALLEGRO_JOYSTICK_STATE current_joystick_state;
            al_get_joystick_state(joystick, &current_joystick_state);
            std::vector<uint32_t> current_buttons_pressed;
            int num_buttons = al_get_joystick_num_buttons(joystick);
            for (int button_num=0; button_num<num_buttons; button_num++)
            {
               if (current_joystick_state.button[button_num]) current_buttons_pressed.push_back(button_num);
            }
            int num_sticks = al_get_joystick_num_sticks(joystick);
            for (int stick_num=0; stick_num<num_sticks; stick_num++)
            {
               int num_axes = al_get_joystick_num_axes(joystick, stick_num);
               for (int axis_num=0; axis_num<num_axes; axis_num++)
               {
                  static float previous_pos = current_joystick_state.stick[stick_num].axis[axis_num];
                  float current_pos = current_joystick_state.stick[stick_num].axis[axis_num];
                  float delta = current_pos; // TODO: Consider showing a delta on the current
                  current_sticks[std::make_pair(stick_num, axis_num)] = { delta, current_pos };
               }
            }

            // Clear the surface and setup the camera
            clear();
            camera.start_reverse_transform();

            float column_1 = -800;
            float column_2 = -300;
            float column_3 = 100;
            float column_4 = 500;
            float status_row_y = -250;

            // Show prompt text and keys pressed
            al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, -450, ALLEGRO_ALIGN_CENTER,
                  "On the test joystick, position any sticks and press any buttons, then press ENTER."
               );
            al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, -450+50, ALLEGRO_ALIGN_CENTER,
                  "Change the stick positions and buttons, then press ENTER again."
               );

            // Show the currently pressed key names
            draw_joystick_status_column("current", column_1, status_row_y, current_sticks, current_buttons_pressed);

            // Show the initial state button names
            if (input_state.get_initial_joystick_state_is_captured())
            {
               draw_joystick_status_column(
                     "initial",
                     column_2,
                     -250, 
                     input_state.get_sticks_moved_in_initial_joystick_state(),
                     input_state.get_buttons_pressed_in_initial_joystick_state()
                  );
            }

            // Show the subsequent state key names
            if (input_state.get_subsequent_joystick_state_is_captured())
            {
               draw_joystick_status_column(
                     "subsequent",
                     column_3,
                     status_row_y, 
                     input_state.get_sticks_moved_in_subsequent_joystick_state(),
                     input_state.get_buttons_pressed_in_subsequent_joystick_state()
                  );
            }

            // Show the change state
            if (input_state.get_joystick_state_changes_are_calculated())
            {
               draw_joystick_status_column(
                     "difference",
                     column_4,
                     status_row_y, 
                     input_state.get_sticks_moved(),
                     input_state.get_buttons_pressed(),
                     input_state.get_buttons_released()
                  );
            }

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
                  if (!input_state.get_initial_joystick_state_is_captured())
                  {
                     input_state.capture_initial_joystick_state();
                  }
                  else if (!input_state.get_subsequent_joystick_state_is_captured())
                  {
                     input_state.capture_subsequent_joystick_state();
                     input_state.calculate_joystick_state_changes();
                  }
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


