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
#include <allegro5/allegro_color.h> // for al_color_name();
#include <AllegroFlare/EventEmitter.hpp> // for al_color_name();


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


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.render();
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


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__will_mark_the_key_as_pressed_at_the_current_time)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__if_the_key_does_not_exist__will_do_nothing)
{
   // TODO
   // TODO: consider capturing a cout warning
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   CAPTURE__render__will_work_as_expected)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimentions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimentions();
   software_keyboard.set_keyboard_dimentions(keyboard_dimentions.x, keyboard_dimentions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   //software_keyboard.set_font_name("Lora-MediumItalic.ttf");
   software_keyboard.set_font_name("Lora-Medium.ttf");
   software_keyboard.set_font_name("ChronoTrigger.ttf");
   software_keyboard.set_prompt_text("Enter your name");



   //std::vector<std::string> key_names_to_press = { "C", "h", "a", "r", "BACKSPACE", "r", "l", "i", "e", };
   std::vector<std::string> key_names_to_press = { "P", "r", "i", "n", "c", "e", "s", "s", };

   //sleep_for(0.2);

   for (auto &key_name_to_press : key_names_to_press)
   {
      software_keyboard.press_key_by_name(key_name_to_press);

      clear();
      software_keyboard.render();
      al_flip_display();
      //sleep_for(0.3);
   }

   //sleep_for(0.2);
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimentions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimentions();
   software_keyboard.set_keyboard_dimentions(keyboard_dimentions.x, keyboard_dimentions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);

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
               case ALLEGRO_KEY_RIGHT:
                  software_keyboard.increment_cursor_pos();
               break;

               case ALLEGRO_KEY_LEFT:
                  software_keyboard.decrement_cursor_pos();
               break;

               case ALLEGRO_KEY_ENTER:
                  software_keyboard.press_key_under_cursor();
               break;

               case ALLEGRO_KEY_BACKSPACE:
                  software_keyboard.press_key_by_name("BACKSPACE");
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            software_keyboard.render();
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



