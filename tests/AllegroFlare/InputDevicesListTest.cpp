
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/InputDevicesList.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
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
   std::string expected_error_message =
      "InputDevicesList::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(physical_input_device_list.initialize(), std::runtime_error, expected_error_message);
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
   EXPECT_EQ(0, physical_input_device_list.count_num_keyboard_devices());
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest, initialize__when_the_keyboard_is_installed__will_create_a_keybord_device)
{
   al_init();
   al_install_keyboard();
   AllegroFlare::InputDevicesList physical_input_device_list;
   physical_input_device_list.initialize();
   EXPECT_EQ(true, physical_input_device_list.count_num_keyboard_devices());
   al_uninstall_keyboard();
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest,
   initialize__when_allegro_joystick_is_not_installed__will_not_create_joystick_devices)
{
   al_init();
   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   EXPECT_EQ(0, input_device_list.count_num_joystick_devices());
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest,
   DISABLED__INTERACTIVE__initialize__when_no_joysticks_are_connected__will_not_create_joystick_devices)
{
   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that *no* joystick devices are currently connected on the OS.

   // NOTE: This test appears flakey!  They will work, then not work, then stall.  I think it's related to
   // some bug in Allegro5. Needs to be investigated.
   // TODO: Fix this flakey test

   al_init();
   al_install_joystick();
   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   EXPECT_EQ(0, input_device_list.count_num_joystick_devices());
   al_uninstall_joystick();
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTest,
   DISABLED__INTERACTIVE__initialize__when_joysticks_are_connected__will_create_joystick_devices)
{
   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that SOME joystick devices are currently connected on the OS.
   // TODO: Consider having a test that interactively prompts the interactive tester to disconnect all devices
   // before running the test.

   // NOTE: This test appears flakey!  They will work, then not work, then stall.  I think it's related to
   // some bug in Allegro5. Needs to be investigated.
   // TODO: Fix this flakey test

   al_init();
   al_install_joystick();
   AllegroFlare::InputDevicesList input_device_list;
   input_device_list.initialize();
   EXPECT_NE(0, input_device_list.count_num_joystick_devices());
   al_uninstall_joystick();
   al_uninstall_system();
}


TEST_F(AllegroFlare_InputDevicesListTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__when_a_joystick_connects_to_the_os_that_was_not_previously_connected__will_create_the_device)
{
   // NOTE: This test is contingent on the status of *actually phyiscally connected* devices on the system.
   // This test assumes that a new device becomes connected in the middle of the test while it is waiting.
   // TODO: Consider having a test that interactively prompts the interactive tester to connect one (or some) devices.

   // NOTE: This test appears flakey!  They will work, then not work, then stall.  I think it's related to
   // some bug in Allegro5. Needs to be investigated.
   // TODO: Fix this flakey test

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
   int num_joystick_devices_at_start = input_device_list.count_num_joystick_devices();
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
            num_joystick_devices_after_reconfiguration = input_device_list.count_num_joystick_devices();
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
               counting_down_to_abort? "Press the ESC key to stop countdown.\nPress ESC again to skip the test."
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


