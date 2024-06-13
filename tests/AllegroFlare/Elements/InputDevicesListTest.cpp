
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventEmitter.hpp>


class AllegroFlare_Elements_InputDevicesListTest : public ::testing::Test
{};

class AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/InputDevicesList.hpp>


TEST_F(AllegroFlare_Elements_InputDevicesListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::InputDevicesList input_devices_list;
}


TEST_F(AllegroFlare_Elements_InputDevicesListTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::InputDevicesList input_devices_list;
   EXPECT_THROW_GUARD_ERROR(
      input_devices_list.render(),
      "AllegroFlare::Elements::InputDevicesList::render",
      "initialized"
   );
}


TEST_F(AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::InputDevicesList input_devices_list(&get_font_bin_ref());
   input_devices_list.initialize();
   input_devices_list.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture, CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::InputDevicesList input_devices_list(&get_font_bin_ref());
   input_devices_list.initialize();
   input_devices_list.set_input_devices(AllegroFlare::Elements::InputDevicesList::build_placeholder_input_devices());
   input_devices_list.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}

TEST_F(AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_offset_the_list_of_items_by__scrollbar_position)
{
   AllegroFlare::Elements::InputDevicesList input_devices_list(&get_font_bin_ref());
   input_devices_list.initialize();
   input_devices_list.set_input_devices(AllegroFlare::Elements::InputDevicesList::build_placeholder_input_devices());

   int num_scrolls = 120;
   float amount_per_scroll = 2.6;
   for (int i=0; i<num_scrolls; i++)
   {
      input_devices_list.set_scrollbar_position(i * amount_per_scroll);

      clear();
      input_devices_list.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_hide_the_scrollbar_if_the_height_of_items_in_the_list_is_smaller_than_the_container_height)
{
   std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>>
      input_devices_elements = AllegroFlare::Elements::InputDevicesList::build_placeholder_input_devices();
   input_devices_elements.resize(4);
   AllegroFlare::Elements::InputDevicesList input_devices_list(&get_font_bin_ref(), input_devices_elements);
   input_devices_list.initialize();

   clear();
   input_devices_list.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_InputDevicesListTestWithAllegroRenderingFixture,
   // TODO: Convert this to a TIMED_INTERACTIVE test
   DISABLED__INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::Elements::InputDevicesList input_devices_list(&get_font_bin_ref());
   input_devices_list.initialize();
   input_devices_list.set_input_devices(AllegroFlare::Elements::InputDevicesList::build_placeholder_input_devices());

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
               case ALLEGRO_KEY_PGUP:
                  input_devices_list.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
               case ALLEGRO_KEY_PGDN:
                  input_devices_list.move_cursor_down();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            input_devices_list.update();
            input_devices_list.render();
            al_flip_display();
         break;
      }

      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


