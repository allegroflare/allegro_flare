
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp> // TODO: replace this usage with an in-test defined
                                                                // child class of PhysicalInputDevice/Base

class AllegroFlare_Elements_InputDeviceConfigurationListTest : public ::testing::Test
{};

class AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/InputDeviceConfigurationList.hpp>


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::InputDeviceConfigurationList achievements;
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTest, render__before_initialization__raises_an_error)
{
   AllegroFlare::Elements::InputDeviceConfigurationList achievements;
   std::string expected_error_message =
      "InputDeviceConfigurationList::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(achievements.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture, update__will_not_blow_up)
{
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.initialize();
   achievements.update();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements.initialize();
   achievements.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   set_joystick_configuration_mapping__will_reset_the_cursor_pos_back_to_0)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.set_physical_input_device(&generic_joystick_physical_input_device);

   achievements.set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );

   achievements.move_cursor_down();
   achievements.move_cursor_down();
   achievements.move_cursor_down();

   ASSERT_NE(0, achievements.get_cursor_pos()); // TODO: remove this assertion and have this case tested in another test

   achievements.set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );

   EXPECT_EQ(0, achievements.get_cursor_pos());
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );
   achievements.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements.initialize();
   achievements.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   CAPTURE__render__when_no_joystick_configuration_mapping_elements_are_present__will_show_an_empty_state)
{
   // NOTE: When in empty state:
   //  - Will render text in the center of the screen with a empty state message
   //  - Will not render the cursor
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements.initialize();
   achievements.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_offset_the_list_of_items_by__scrollbar_position)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements(&get_font_bin_ref());
   achievements.set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );
   achievements.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements.initialize();

   int num_scrolls = 120;
   float amount_per_scroll = 2.6;
   for (int i=0; i<num_scrolls; i++)
   {
      achievements.set_scrollbar_position(i * amount_per_scroll);

      clear();
      achievements.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_hide_the_scrollbar_if_the_height_of_items_in_the_list_is_smaller_than_the_container_height)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   std::vector<std::tuple<std::string, uint32_t>> achievements =
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping();
   achievements.resize(4);
   AllegroFlare::Elements::InputDeviceConfigurationList achievements_list(&get_font_bin_ref());
   achievements_list.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements_list.set_joystick_configuration_mapping(achievements);
   achievements_list.initialize();

   clear();
   achievements_list.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_InputDeviceConfigurationListTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject (add a joystick configuration mapping)
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick_physical_input_device;
   AllegroFlare::Elements::InputDeviceConfigurationList achievements_list(&get_font_bin_ref());
   achievements_list.set_joystick_configuration_mapping(
      AllegroFlare::Elements::InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
   );
   achievements_list.set_physical_input_device(&generic_joystick_physical_input_device);
   achievements_list.initialize();

   // run the interactive test
   al_start_timer(primary_timer);
   float duration_until_abort_sec = 3.0f;
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;
   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
         {
            abort_timer_in_effect = false;
            if (achievements_list.is_waiting_user_input_for_remap())
            {
               int button_pressed = event.joystick.button;
               if (achievements_list.is_waiting_user_input_for_remap())
               {
                  achievements_list.submit_mapping_on_currently_selected_option(button_pressed);
               }
            }
         }

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            if (achievements_list.is_waiting_user_input_for_remap())
            {
               switch(event.keyboard.keycode)
               {
                  case ALLEGRO_KEY_ESCAPE:
                     achievements_list.abort_current_option_for_remapping();
                  break;
               }
               // TODO: handle the case of submittting a mapping
            }
            else
            {
               switch(event.keyboard.keycode)
               {
                  case ALLEGRO_KEY_UP:
                     achievements_list.move_cursor_up();
                  break;

                  case ALLEGRO_KEY_DOWN:
                     achievements_list.move_cursor_down();
                  break;

                  case ALLEGRO_KEY_PGUP:
                     // NOTE: Note the scrollbar will be repositioned on any cursor movement - when the screen's
                     // scrollbar_movement_mode is in SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL, which it is by default
                     achievements_list.move_scrollbar_position(-20.0);
                  break;

                  case ALLEGRO_KEY_PGDN:
                     // NOTE: Note the scrollbar will be repositioned on any cursor movement - when the screen's
                     // scrollbar_movement_mode is in SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL, which it is by default
                     achievements_list.move_scrollbar_position(20.0);
                  break;

                  case ALLEGRO_KEY_ENTER:
                     achievements_list.select_current_option_for_remapping();
                  break;
               }
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            achievements_list.update();
            achievements_list.render();
            al_flip_display();
         break;
      }

      // TODO: fix this test case when in the middle of remapping a key
      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


