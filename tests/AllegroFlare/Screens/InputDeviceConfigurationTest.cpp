
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/InputDeviceConfiguration.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Screens_InputDeviceConfigurationTest : public ::testing::Test {};
class AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_InputDeviceConfigurationTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


TEST_F(AllegroFlare_Screens_InputDeviceConfigurationTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::InputDeviceConfiguration input_device_configuration_screen;
}


TEST_F(AllegroFlare_Screens_InputDeviceConfigurationTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::InputDeviceConfiguration input_device_configuration_screen;
   EXPECT_EQ("AllegroFlare/Screens/InputDeviceConfiguration", input_device_configuration_screen.get_type());
}


TEST_F(AllegroFlare_Screens_InputDeviceConfigurationTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::InputDeviceConfiguration input_device_configuration_screen;
   EXPECT_EQ(AllegroFlare::Screens::InputDeviceConfiguration::TYPE, input_device_configuration_screen.get_type());
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture,
   FOCUS__INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   //al_init_primitives_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::Screens::InputDeviceConfiguration input_device_configuration_screen;
   input_device_configuration_screen.set_font_bin(&get_font_bin_ref());
   input_device_configuration_screen.set_bitmap_bin(&get_bitmap_bin_ref());
   input_device_configuration_screen.set_event_emitter(&event_emitter);
   input_device_configuration_screen.initialize();

   // set some default placeholder button mappings for this test
   input_device_configuration_screen.get_input_device_configuration_element_ref().set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );

   // run the interactive test
   al_start_timer(primary_timer);

   // activate the screen (typically this is done by the framework)
   input_device_configuration_screen.on_activate();
   float duration_until_abort_sec = 3.0f;
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;
   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            int button_num = 0;
            //if (event.keyboard.keycode == ALLEGRO_KEY_UP) button_num = AllegroFlare::VirtualController::BUTTON_UP;
            //if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) button_num = AllegroFlare::VirtualController::BUTTON_DOWN;
            //if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) button_num = AllegroFlare::VirtualController::BUTTON_A;
            if (button_num != 0)
            {
               input_device_configuration_screen.virtual_control_button_down_func(nullptr, nullptr, button_num, event.keyboard.repeat);
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
            input_device_configuration_screen.primary_timer_func();
            al_flip_display();
         break;

         // TODO: Add event handling for sound effects
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
            //std::cout << "Event emitted to play sound effect." << std::endl;
         //break;

         //case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            //abort = true;
         //break;
      }

      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_Screens_InputDeviceConfigurationTestWithAllegroFrameworksFullFixture,
   DISABLED__TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::InputDeviceConfiguration input_device_configuration_screen;
   input_device_configuration_screen.set_event_emitter(get_framework_event_emitter());
   input_device_configuration_screen.set_bitmap_bin(get_framework_bitmap_bin());
   input_device_configuration_screen.set_font_bin(get_framework_font_bin());
   input_device_configuration_screen.initialize();

   framework_register_and_activate_screen("input_device_configuration_screen", &input_device_configuration_screen);

   framework_run_loop(3);
}


