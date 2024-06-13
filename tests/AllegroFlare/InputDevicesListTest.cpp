
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/InputDevicesList.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Color.hpp> // for AllegroFlare::Color::Aquamarine as test result


#include <allegro5/allegro.h>


class AllegroFlare_InputDevicesListTest : public ::testing::Test
{
public:
   AllegroFlare_InputDevicesListTest() {}
};

class AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture() {}
};


TEST_F(AllegroFlare_InputDevicesListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InputDevicesList physical_input_device_list;
}


TEST_F(AllegroFlare_InputDevicesListTest, initialize__without_allegro_installed__will_throw_an_error)
{
   AllegroFlare::InputDevicesList physical_input_device_list;
   EXPECT_THROW_GUARD_ERROR(
      physical_input_device_list.initialize(),
      "AllegroFlare::InputDevicesList::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_InputDevicesListTest, initialize__will_not_blow_up)
{
   al_init();
   AllegroFlare::InputDevicesList physical_input_device_list;
   physical_input_device_list.initialize();
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest,
   initialize__when_the_keyboard_is_not_installed__will_not_create_a_keybord_device)
{
   al_init();
   AllegroFlare::InputDevicesList physical_input_device_list;
   physical_input_device_list.initialize();
   EXPECT_EQ(0, physical_input_device_list.num_keyboard_devices());
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest, initialize__when_the_keyboard_is_installed__will_create_a_keybord_device)
{
   al_init();
   al_install_keyboard();
   AllegroFlare::InputDevicesList physical_input_device_list;
   physical_input_device_list.initialize();
   EXPECT_EQ(true, physical_input_device_list.num_keyboard_devices());
   al_uninstall_keyboard();
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest,
   initialize__when_allegro_joystick_is_not_installed__will_not_create_joystick_devices)
{
   al_init();
   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   EXPECT_EQ(0, input_device_list.num_joystick_devices());
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   INTERACTIVE__initialize__when_no_joysticks_are_connected__will_not_create_joystick_devices)
{
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *timer = al_create_timer(1.0f / 60.0f);
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   ALLEGRO_FONT *font = get_user_prompt_font();
   ALLEGRO_FONT *any_font = get_any_font(-30);

   static const uint32_t STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES = 0;
   uint32_t test_state = STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES;

   AllegroFlare::InputDevicesList input_device_list;
   float updated_at_before_initialization = input_device_list.get_updated_at();
   float updated_at_after_initialization = 0;
   int expected_num_connected_joysticks_after_initialization = 0;
   int num_connected_joystick_devices_after_initialization = 0;

   bool abort_tester_prompts = false;
   bool test_conditions_successfully_triggered = false;
   bool counting_down_to_abort = true;
   float duration_to_abort = 10.0f;
   float test_started_at = al_get_time();
   al_start_timer(timer);

   while(!abort_tester_prompts)
   {
      ALLEGRO_EVENT allegro_event;
      al_wait_for_event(event_queue, &allegro_event);

      switch(allegro_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            clear();

            std::string prompt_message = "Press ENTER to confirm that no joysticks are connected.";

            al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{0.8f, 0.8f, 0.8f, 0.8f},
               1920/2,
               1080/2 - 50,
               1000,
               al_get_font_line_height(font),
               ALLEGRO_ALIGN_CENTER,
               prompt_message.c_str()
            );

            if (counting_down_to_abort)
            {
               float time_remaining = duration_to_abort - (al_get_time() - test_started_at);
               if (time_remaining < 0.0f)
               {
                  time_remaining = 0.0f;
                  counting_down_to_abort = false;
                  abort_tester_prompts = true;
               }
                  al_draw_multiline_textf(
                  any_font,
                  AllegroFlare::Color::LemonChiffon,
                  1920/2,
                  1080/2+50,
                  1000,
                  al_get_font_line_height(any_font),
                  ALLEGRO_ALIGN_CENTER,
                  "This test will automatically be skipped in %d seconds.",
                  (int)(time_remaining + 1)
               );
            }

            al_draw_multiline_text(
               any_font,
               ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f},
               1920/2,
               1080/2+150,
               1000,
               al_get_font_line_height(any_font),
               ALLEGRO_ALIGN_CENTER,
               counting_down_to_abort ? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
                                      : "Press ESC if you wish to skip the test."
            );

            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_DOWN:
            switch(allegro_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  else abort_tester_prompts = true;
               break;

               case ALLEGRO_KEY_ENTER:
                  if (counting_down_to_abort) counting_down_to_abort = false;

                  // Perform the test event
                  input_device_list.initialize();

                  // Capture the test result
                  num_connected_joystick_devices_after_initialization = input_device_list.num_joystick_devices();
                  updated_at_after_initialization = input_device_list.get_updated_at();

                  // Set the flags to continue test
                  test_conditions_successfully_triggered = true;
                  abort_tester_prompts = true;
               break;
            }
         break;
      }
   }

   if (test_conditions_successfully_triggered)
   {
      // Check the number of connected devices
      EXPECT_EQ(0, num_connected_joystick_devices_after_initialization);

      // TODO: Test the "updated_at" values are set
      EXPECT_NE(updated_at_before_initialization, updated_at_after_initialization);

      bool test_succeeded = !HasNonfatalFailure();
      ALLEGRO_COLOR test_result_color = test_succeeded ? AllegroFlare::Color::Aquamarine
                                                       : AllegroFlare::Color::Crimson;
      std::string test_result_message = test_succeeded ? "Successful"
                                                       : "Failure";
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         test_result_message.c_str()
      );
      al_flip_display();
      al_rest(1.5);
   }
   else
   {
      ALLEGRO_COLOR test_result_color = AllegroFlare::Color::LemonChiffon;
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         "Skipped"
      );

      al_flip_display();
      al_rest(0.25);
      al_stop_timer(timer);
      al_destroy_event_queue(event_queue);
      al_uninstall_keyboard();
      al_uninstall_joystick();
      GTEST_SKIP() << "This interactive test requires user interaction with joystick configuration change. Please "
                   << "look into the test comments for more information.";
   }

   al_stop_timer(timer);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_joystick();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   INTERACTIVE__initialize__when_joysticks_are_connected__will_create_connected_joystick_devices)
{
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *timer = al_create_timer(1.0f / 60.0f);
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   ALLEGRO_FONT *font = get_user_prompt_font();
   ALLEGRO_FONT *any_font = get_any_font(-30);

   static const uint32_t STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES = 0;
   uint32_t test_state = STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES;

   AllegroFlare::InputDevicesList input_device_list;
   float updated_at_before_initialization = input_device_list.get_updated_at();
   float updated_at_after_initialization = 0;
   int expected_num_connected_joysticks_after_initialization = 1;
   int num_connected_joystick_devices_after_initialization = 0;

   bool abort_tester_prompts = false;
   bool test_conditions_successfully_triggered = false;
   bool counting_down_to_abort = true;
   float duration_to_abort = 10.0f;
   float test_started_at = al_get_time();
   al_start_timer(timer);

   while(!abort_tester_prompts)
   {
      ALLEGRO_EVENT allegro_event;
      al_wait_for_event(event_queue, &allegro_event);

      switch(allegro_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            clear();

            std::string prompt_message = "Press ENTER to confirm that joysticks are connected.";

            al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{0.8f, 0.8f, 0.8f, 0.8f},
               1920/2,
               1080/2 - 50,
               1000,
               al_get_font_line_height(font),
               ALLEGRO_ALIGN_CENTER,
               prompt_message.c_str()
            );

            if (counting_down_to_abort)
            {
               float time_remaining = duration_to_abort - (al_get_time() - test_started_at);
               if (time_remaining < 0.0f)
               {
                  time_remaining = 0.0f;
                  counting_down_to_abort = false;
                  abort_tester_prompts = true;
               }
                  al_draw_multiline_textf(
                  any_font,
                  AllegroFlare::Color::LemonChiffon,
                  1920/2,
                  1080/2+50,
                  1000,
                  al_get_font_line_height(any_font),
                  ALLEGRO_ALIGN_CENTER,
                  "This test will automatically be skipped in %d seconds.",
                  (int)(time_remaining + 1)
               );
            }

            al_draw_multiline_text(
               any_font,
               ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f},
               1920/2,
               1080/2+150,
               1000,
               al_get_font_line_height(any_font),
               ALLEGRO_ALIGN_CENTER,
               counting_down_to_abort ? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
                                      : "Press ESC if you wish to skip the test."
            );

            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_DOWN:
            switch(allegro_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  else abort_tester_prompts = true;
               break;

               case ALLEGRO_KEY_ENTER:
                  if (counting_down_to_abort) counting_down_to_abort = false;

                  // Perform the test event
                  input_device_list.initialize();

                  // Capture the test result
                  num_connected_joystick_devices_after_initialization = input_device_list.num_joystick_devices();
                  updated_at_after_initialization = input_device_list.get_updated_at();

                  // Set the flags to continue test
                  test_conditions_successfully_triggered = true;
                  abort_tester_prompts = true;
               break;
            }
         break;
      }
   }

   if (test_conditions_successfully_triggered)
   {
      // Check the number of connected devices
      EXPECT_NE(0, num_connected_joystick_devices_after_initialization);

      // TODO: Test the "updated_at" values are set
      EXPECT_NE(updated_at_before_initialization, updated_at_after_initialization);

      bool test_succeeded = !HasNonfatalFailure();
      ALLEGRO_COLOR test_result_color = test_succeeded ? AllegroFlare::Color::Aquamarine
                                                       : AllegroFlare::Color::Crimson;
      std::string test_result_message = test_succeeded ? "Successful"
                                                       : "Failure";
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         test_result_message.c_str()
      );
      al_flip_display();
      al_rest(1.5);
   }
   else
   {
      ALLEGRO_COLOR test_result_color = AllegroFlare::Color::LemonChiffon;
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         "Skipped"
      );

      al_flip_display();
      al_rest(0.25);
      al_stop_timer(timer);
      al_destroy_event_queue(event_queue);
      al_uninstall_keyboard();
      al_uninstall_joystick();
      GTEST_SKIP() << "This interactive test requires user interaction with joystick configuration change. Please "
                   << "look into the test comments for more information.";
   }

   al_stop_timer(timer);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_joystick();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   INTERACTIVE__handle_reconfigured_joystick__when_a_joystick_connects_to_the_os_that_was_not_previously_\
connected__will_create_the_device)
{
   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that a new device becomes connected in the middle of the test while it is waiting.

   // TODO: Modify this test to interactively prompt the tester to connect one (or some) devices.

   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *timer = al_create_timer(1.0f / 60.0f);
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   ALLEGRO_FONT *font = get_user_prompt_font();
   ALLEGRO_FONT *any_font = get_any_font(-30);

   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   int num_joystick_devices_at_start = input_device_list.num_joystick_devices();
   int expected_num_joysticks_after_reconfiguration = num_joystick_devices_at_start + 1;
   int num_joystick_devices_after_reconfiguration = 0;

   bool abort = false;
   bool test_conditions_successfully_triggered = false;
   bool counting_down_to_abort = true;
   float duration_to_abort = 10.0f;
   float test_started_at = al_get_time();
   al_start_timer(timer);
   while(!abort)
   {
      ALLEGRO_EVENT allegro_event;
      al_wait_for_event(event_queue, &allegro_event);

      switch(allegro_event.type)
      {
         case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            input_device_list.handle_reconfigured_joystick();
            num_joystick_devices_after_reconfiguration = input_device_list.num_joystick_devices();
            expected_num_joysticks_after_reconfiguration = num_joystick_devices_at_start + 1;
            test_conditions_successfully_triggered = true;
            abort = true;
         break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{0.8f, 0.8f, 0.8f, 0.8f},
               1920/2,
               1080/2 - 50,
               800,
               al_get_font_line_height(font),
               ALLEGRO_ALIGN_CENTER,
               "Please connect in a controller."
            );
            if (counting_down_to_abort)
            {
               float time_remaining = duration_to_abort - (al_get_time() - test_started_at);
               if (time_remaining < 0.0f)
               {
                  time_remaining = 0.0f;
                  counting_down_to_abort = false;
                  abort = true;
               }
               al_draw_multiline_textf(
                  any_font,
                  AllegroFlare::Color::LemonChiffon,
                  1920/2,
                  1080/2+50,
                  800,
                  al_get_font_line_height(any_font),
                  ALLEGRO_ALIGN_CENTER,
                  "This test will automatically be skipped in %d seconds.",
                  (int)(time_remaining + 1)
               );
            }

            al_draw_multiline_text(
               any_font,
               ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f},
               1920/2,
               1080/2+150,
               800,
               al_get_font_line_height(any_font),
               ALLEGRO_ALIGN_CENTER,
               counting_down_to_abort ? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
                                      : "Press ESC if you wish to skip the test."
            );

            al_flip_display();
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
            if (allegro_event.keyboard.keycode != ALLEGRO_KEY_ESCAPE) break;

            if (counting_down_to_abort) counting_down_to_abort = false;
            else abort = true;
         break;
      }
   }

   if (test_conditions_successfully_triggered)
   {
      EXPECT_EQ(num_joystick_devices_after_reconfiguration, expected_num_joysticks_after_reconfiguration);

      bool test_succeeded = !HasNonfatalFailure();
      ALLEGRO_COLOR test_result_color = test_succeeded ? AllegroFlare::Color::Aquamarine
                                                       : AllegroFlare::Color::Crimson;
      std::string test_result_message = test_succeeded ? "Successful"
                                                       : "Failure";
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         800,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         test_result_message.c_str()
      );
      al_flip_display();
      al_rest(1.5);
   }
   else
   {
      ALLEGRO_COLOR test_result_color = AllegroFlare::Color::LemonChiffon;
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         800,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         "Skipped"
      );

      al_flip_display();
      al_rest(1.5);
      al_stop_timer(timer);
      al_destroy_event_queue(event_queue);
      al_uninstall_keyboard();
      al_uninstall_joystick();
      GTEST_SKIP() << "This interactive test requires user interaction with joystick configuration change. Please "
                   << "look into the test comments for more information.";
   }

   al_stop_timer(timer);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_joystick();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   INTERACTIVE__handle_reconfigured_joysticks__when_a_joystick_is_disconnected_that_was_previously_connected\
__will_mark_the_device_as_disconnected)
{
   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that a new device becomes connected in the middle of the test while it is waiting.

   // TODO: Test updated_at property with these changes

   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *timer = al_create_timer(1.0f / 60.0f);
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   ALLEGRO_FONT *font = get_user_prompt_font();
   ALLEGRO_FONT *any_font = get_any_font(-30);

   static const uint32_t STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES = 0;
   static const uint32_t STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE = 1;
   uint32_t test_state = STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES;

   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   int num_connected_joystick_devices_before_reconfiguration = 0;
   float updated_at_before_reconfiguration = 0;
   float updated_at_after_reconfiguration = 0;
   int expected_num_connected_joysticks_after_reconfiguration = 0;
   int num_connected_joystick_devices_after_reconfiguration = 0;

   bool abort = false;
   bool test_conditions_successfully_triggered = false;
   bool counting_down_to_abort = true;
   float duration_to_abort = 10.0f;
   float test_started_at = al_get_time();
   al_start_timer(timer);

   while(!abort)
   {
      ALLEGRO_EVENT allegro_event;
      al_wait_for_event(event_queue, &allegro_event);

      switch(allegro_event.type)
      {
         case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            switch(test_state)
            {
               case STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES:
                  input_device_list.handle_reconfigured_joystick();
               break;

               case STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE:
                  updated_at_before_reconfiguration = input_device_list.get_updated_at();
                  input_device_list.handle_reconfigured_joystick();
                  updated_at_after_reconfiguration = input_device_list.get_updated_at();
                  num_connected_joystick_devices_after_reconfiguration = input_device_list.num_connected_joysticks();
                  test_conditions_successfully_triggered = true;
                  abort = true;
               break;
            }
         break;

         case ALLEGRO_EVENT_TIMER: {
            clear();

            std::string prompt_message;

            switch(test_state)
            {
               case STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES:
                 prompt_message = "Press ENTER to confirm that joysticks are connected.";
               break;

               case STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE:
                 prompt_message = "Please disconnect one joystick.";
               break;
            }

            al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{0.8f, 0.8f, 0.8f, 0.8f},
               1920/2,
               1080/2 - 50,
               1000,
               al_get_font_line_height(font),
               ALLEGRO_ALIGN_CENTER,
               prompt_message.c_str()
            );

            if (counting_down_to_abort)
            {
               float time_remaining = duration_to_abort - (al_get_time() - test_started_at);
               if (time_remaining < 0.0f)
               {
                  time_remaining = 0.0f;
                  counting_down_to_abort = false;
                  abort = true;
               }
                  al_draw_multiline_textf(
                  any_font,
                  AllegroFlare::Color::LemonChiffon,
                  1920/2,
                  1080/2+50,
                  1000,
                  al_get_font_line_height(any_font),
                  ALLEGRO_ALIGN_CENTER,
                  "This test will automatically be skipped in %d seconds.",
                  (int)(time_remaining + 1)
               );
            }

            al_draw_multiline_text(
               any_font,
               ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f},
               1920/2,
               1080/2+150,
               1000,
               al_get_font_line_height(any_font),
               ALLEGRO_ALIGN_CENTER,
               counting_down_to_abort ? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
                                      : "Press ESC if you wish to skip the test."
            );

            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_DOWN:
            switch(allegro_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  else abort = true;
               break;

               case ALLEGRO_KEY_ENTER:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  if (test_state == STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES)
                  {
                     num_connected_joystick_devices_before_reconfiguration =
                        input_device_list.num_connected_joysticks();
                     expected_num_connected_joysticks_after_reconfiguration =
                        num_connected_joystick_devices_before_reconfiguration - 1;

                     test_state = STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE;
                  }
               break;
            }
         break;
      }
   }

   if (test_conditions_successfully_triggered)
   {
      // Check the number of connected devices
      EXPECT_EQ(
         expected_num_connected_joysticks_after_reconfiguration,
         num_connected_joystick_devices_after_reconfiguration
      );

      // Check the number updated at values
      EXPECT_NE(updated_at_before_reconfiguration, updated_at_after_reconfiguration);

      bool test_succeeded = !HasNonfatalFailure();
      ALLEGRO_COLOR test_result_color = test_succeeded ? AllegroFlare::Color::Aquamarine
                                                       : AllegroFlare::Color::Crimson;
      std::string test_result_message = test_succeeded ? "Successful"
                                                       : "Failure";
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         test_result_message.c_str()
      );
      al_flip_display();
      al_rest(1.5);
   }
   else
   {
      ALLEGRO_COLOR test_result_color = AllegroFlare::Color::LemonChiffon;
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         "Skipped"
      );

      al_flip_display();
      al_rest(0.25);
      al_stop_timer(timer);
      al_destroy_event_queue(event_queue);
      al_uninstall_keyboard();
      al_uninstall_joystick();
      GTEST_SKIP() << "This interactive test requires user interaction with joystick configuration change. Please "
                   << "look into the test comments for more information.";
   }

   al_stop_timer(timer);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_joystick();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__handle_reconfigured_joysticks__when_a_known_disconnected_joystick_is_reconnected__will_mark_\
the_known_device_as_connected)
{
   // TODO: This test is disabled because the "reconnecting disconnected" joystick feature is not supported in Allegro.

   // TODO: include "udpated_at" in test

   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that a new device becomes connected in the middle of the test while it is waiting.
   // TODO: Consider having a test that interactively prompts the interactive tester to connect one (or some) devices.

   // TODO: Test updated_at property with these changes

   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *timer = al_create_timer(1.0f / 60.0f);
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   ALLEGRO_FONT *font = get_user_prompt_font();
   ALLEGRO_FONT *any_font = get_any_font(-30);

   static const uint32_t STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES = 0;
   static const uint32_t STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE = 1;
   static const uint32_t STATE_AWAITING_RECONNECTION_OF_A_DISCONNECTED_KNOWN_DEVICE = 2;
   uint32_t test_state = STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES;

   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();

   int num_joystick_devices_before_reconfiguration = 0;
   int num_connected_joystick_devices_before_reconfiguration = 0;
   int num_joystick_devices_after_reconfiguration = 0;
   int num_connected_joystick_devices_after_reconfiguration = 0;
   AllegroFlare::PhysicalInputDevices::Base* test_device = nullptr;

   bool abort = false;
   bool test_conditions_successfully_triggered = false;
   bool counting_down_to_abort = true;
   float duration_to_abort = 10.0f;
   float test_started_at = al_get_time();
   al_start_timer(timer);

   while(!abort)
   {
      ALLEGRO_EVENT allegro_event;
      al_wait_for_event(event_queue, &allegro_event);

      switch(allegro_event.type)
      {
         case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            switch(test_state)
            {
               case STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES:
                  input_device_list.handle_reconfigured_joystick();
               break;

               case STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE: {
                  // TODO: Consider adding a slight pause after the confirmation, or a list of checkmarks
                  // showing steps in the test.
                  // TODO: These assertions are a bit brittle, could be made a little more bullet-proof. Specifically,
                  // asserting that all_devices_are_connected may not be true if the tester has connected/disconnected
                  // several devices before confirming that there are connected joysticks. There could be disconnected
                  // devices.
                  ASSERT_EQ(true, input_device_list.all_devices_are_connected());

                  input_device_list.handle_reconfigured_joystick();

                  std::vector<AllegroFlare::PhysicalInputDevices::Base*> disconnected_joysticks =
                     input_device_list.get_disconnected_joysticks();
                  ASSERT_EQ(1, disconnected_joysticks.size());

                  // Set our test device (so we can later confirm it is the device that becomes reconnected)
                  test_device = disconnected_joysticks[0];
                  ASSERT_EQ(false, test_device->get_connected());

                  test_state = STATE_AWAITING_RECONNECTION_OF_A_DISCONNECTED_KNOWN_DEVICE;
               } break;

               case STATE_AWAITING_RECONNECTION_OF_A_DISCONNECTED_KNOWN_DEVICE:
                  num_joystick_devices_before_reconfiguration = input_device_list.num_joystick_devices();
                  num_connected_joystick_devices_before_reconfiguration = input_device_list.num_connected_joysticks();
                  input_device_list.handle_reconfigured_joystick();
                  num_joystick_devices_after_reconfiguration = input_device_list.num_joystick_devices();
                  num_connected_joystick_devices_after_reconfiguration = input_device_list.num_connected_joysticks();
                  test_conditions_successfully_triggered = true;
                  abort = true;
               break;
            }
         break;

         case ALLEGRO_EVENT_TIMER: {
            clear();

            std::string prompt_message;

            switch(test_state)
            {
               case STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES:
                 prompt_message = "Press ENTER to confirm that joysticks are connected.";
               break;

               case STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE:
                 prompt_message = "Please disconnect one joystick.";
               break;

               case STATE_AWAITING_RECONNECTION_OF_A_DISCONNECTED_KNOWN_DEVICE:
                 prompt_message = "Please reconnect the joystick that you disconnected.";
               break;
            }

            al_draw_multiline_text(
               font,
               ALLEGRO_COLOR{0.8f, 0.8f, 0.8f, 0.8f},
               1920/2,
               1080/2 - 50,
               1000,
               al_get_font_line_height(font),
               ALLEGRO_ALIGN_CENTER,
               prompt_message.c_str()
            );

            if (counting_down_to_abort)
            {
               float time_remaining = duration_to_abort - (al_get_time() - test_started_at);
               if (time_remaining < 0.0f)
               {
                  time_remaining = 0.0f;
                  counting_down_to_abort = false;
                  abort = true;
               }
                  al_draw_multiline_textf(
                  any_font,
                  AllegroFlare::Color::LemonChiffon,
                  1920/2,
                  1080/2+50,
                  1000,
                  al_get_font_line_height(any_font),
                  ALLEGRO_ALIGN_CENTER,
                  "This test will automatically be skipped in %d seconds.",
                  (int)(time_remaining + 1)
               );
            }

            al_draw_multiline_text(
               any_font,
               ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f},
               1920/2,
               1080/2+150,
               1000,
               al_get_font_line_height(any_font),
               ALLEGRO_ALIGN_CENTER,
               counting_down_to_abort ? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
                                      : "Press ESC if you wish to skip the test."
            );

            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_DOWN:
            switch(allegro_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  else abort = true;
               break;

               case ALLEGRO_KEY_ENTER:
                  if (counting_down_to_abort) counting_down_to_abort = false;
                  if (test_state == STATE_AWAITING_CONFIRMATION_OF_CONNECTED_DEVICES)
                  {
                     test_state = STATE_AWAITING_DISCONNECTION_OF_A_CONNECTED_DEVICE;
                  }
               break;
            }
         break;
      }
   }

   if (test_conditions_successfully_triggered)
   {
      // Check the number of connected devices

      //int num_joystick_devices_before_reconfiguration = 0;
      //int num_connected_joystick_devices_before_reconfiguration = 0;
      //int num_joystick_devices_after_reconfiguration = 0;
      //int num_connected_joystick_devices_after_reconfiguration = 0;

      int expected_num_connected_joysticks_after_reconfiguration = num_joystick_devices_before_reconfiguration;

      // The same number of devices are present after the reconnection (no new devices have been created)
      EXPECT_EQ(
         expected_num_connected_joysticks_after_reconfiguration,
         num_connected_joystick_devices_after_reconfiguration
      );

      ASSERT_NE(nullptr, test_device); // TODO: Remove this line, it's excessive & paranoid

      // Check that our known test device has become connected
      EXPECT_EQ(true, test_device->get_connected());

      EXPECT_EQ(true, input_device_list.all_devices_are_connected()); // TODO: Consider removing this line, excessive

      // Check the number updated at values
      //EXPECT_NE(updated_at_before_reconfiguration, updated_at_after_reconfiguration);

      bool test_succeeded = !HasNonfatalFailure();
      ALLEGRO_COLOR test_result_color = test_succeeded ? AllegroFlare::Color::Aquamarine
                                                       : AllegroFlare::Color::Crimson;
      std::string test_result_message = test_succeeded ? "Successful"
                                                       : "Failure";
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         test_result_message.c_str()
      );
      al_flip_display();
      al_rest(1.5);
   }
   else
   {
      ALLEGRO_COLOR test_result_color = AllegroFlare::Color::LemonChiffon;
      clear();
      al_draw_multiline_text(
         font,
         test_result_color,
         1920/2,
         1080/2-50,
         1000,
         al_get_font_line_height(font),
         ALLEGRO_ALIGN_CENTER,
         "Skipped"
      );

      al_flip_display();
      al_rest(0.25);
      al_stop_timer(timer);
      al_destroy_event_queue(event_queue);
      al_uninstall_keyboard();
      al_uninstall_joystick();
      GTEST_SKIP() << "This interactive test requires user interaction with joystick configuration change. Please "
                   << "look into the test comments for more information.";
   }

   al_stop_timer(timer);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_joystick();
}


