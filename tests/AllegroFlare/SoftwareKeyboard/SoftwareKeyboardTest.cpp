#include <gtest/gtest.h>

#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <allegro5/allegro_color.h> // for al_color_name();
#include <AllegroFlare/EventEmitter.hpp> // for al_color_name();
#include <AllegroFlare/EventNames.hpp> // for ALLEGRO_FLARE_EVENT_GAME_EVENT
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Logger.hpp>


class AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest : public ::testing::Test {};
class AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


static void my_on_submit_callback_func(
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard *software_keyboard,
      void *on_submit_callback_func_user_data=nullptr
   )
{
   if (!on_submit_callback_func_user_data) std::runtime_error("test error");

   std::pair<std::string, int> &as_my_user_data = *(std::pair<std::string, int>*)(on_submit_callback_func_user_data);
   // This first value will represent the data captured from the keyboard:
   as_my_user_data.first = software_keyboard->get_result_string();
   // This second value will represent the call count
   as_my_user_data.second++;
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   bonk_sound_effect_identifier__is_initialized_to_the_default_value)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_bonk_sound_effect_identifier = 
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_BONK_SOUND_EFFECT_IDENTIFIER;
   EXPECT_EQ(expected_bonk_sound_effect_identifier, software_keyboard.get_bonk_sound_effect_identifier());
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   showing_input_error_frame__is_initialized_to_the_expected_default_value)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   EXPECT_EQ(false, software_keyboard.get_showing_input_error_frame());
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   DEFAULT_BONK_SOUND_EFFECT_IDENTIFIER__has_the_expected_default_value)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_bonk_sound_effect_identifier = "ui-input-bonk-01.ogg";
   EXPECT_EQ(
      expected_bonk_sound_effect_identifier, 
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_BONK_SOUND_EFFECT_IDENTIFIER
   );
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::initialize",
      "al_is_system_installed()"
   );
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::initialize",
      "al_is_primitives_addon_initialized()"
   );
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest, initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::initialize",
      "al_is_font_addon_initialized()"
   );
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
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::initialize",
      "font_bin"
   );
   EXPECT_THROW_WITH_MESSAGE(software_keyboard.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.render();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   increment_cursor_pos__when_there_are_no_keys__will_emit_a_bonk_sound_effect_event)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_bonk_sound_effect_identifier("my-custom-sound-effect.ogg");

   ASSERT_EQ(true, software_keyboard.get_keys_ref().empty());

   software_keyboard.increment_cursor_pos();

   ALLEGRO_EVENT emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &emitted_event));

   EXPECT_EQ(ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT, emitted_event.type);
   std::string *emitted_event_data = (std::string *)emitted_event.user.data1;
   ASSERT_NE(nullptr, emitted_event_data);
   EXPECT_EQ("my-custom-sound-effect.ogg", *emitted_event_data);

   // teardown
   al_destroy_event_queue(event_queue);
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
   reset__will_clear_the_input_error_frame__and__will_clear_input_error_frame_error_messages)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();

   software_keyboard.show_input_error_frame({ "a test error" });
   EXPECT_EQ(true, software_keyboard.get_showing_input_error_frame()); // Sanity check, consider removing and relying
                                                                       // on other tests
   EXPECT_EQ(true, software_keyboard.has_input_error_frame_error_messages()); // Sanity check, consider removing and
                                                                              // relying on other tests

   software_keyboard.reset();
   EXPECT_EQ(false, software_keyboard.get_showing_input_error_frame());
   EXPECT_EQ(false, software_keyboard.has_input_error_frame_error_messages());
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   press_key_by_name__when_pressing_the_SUBMIT_key__will_emit_an_AllegroFlare_GameEvent_with_a_type_\
event_to_emit_on_pressing_submit_key)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   // Setup keyboard to use the default keys
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());

   software_keyboard.set_result_string("Foobar");
   software_keyboard.press_key_by_name("SUBMIT");

   ALLEGRO_EVENT emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &emitted_event));

   // TODO: Grab event and extract data
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_GAME_EVENT, emitted_event.type);
   AllegroFlare::GameEvent *game_event_data = static_cast<AllegroFlare::GameEvent *>((void *)emitted_event.user.data1);
   if (!game_event_data) throw std::runtime_error("Unexpected GameEvent error");
   EXPECT_EQ(
      game_event_data->get_type(),
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_EVENT_TO_EMIT_ON_PRESSING_SUBMIT_KEY
   );

   // teardown
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   press_key_by_name__when_pressing_the_SUBMIT_key__when_an_on_submit_callback_func_is_set__will_call_the_callback)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   // Setup keyboard to use the default keys
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   // Set some valid input data
   std::string user_input_string = "User input";
   software_keyboard.set_result_string(user_input_string);

   std::pair<std::string, int> my_on_submit_callback_func_user_data = {"", 0};
   software_keyboard.set_on_submit_callback_func(my_on_submit_callback_func);
   software_keyboard.set_on_submit_callback_func_user_data(&my_on_submit_callback_func_user_data);

   software_keyboard.press_key_by_name("SUBMIT");

   // Assert that the callback was called, and was passed and processed the expected data
   EXPECT_EQ(user_input_string, my_on_submit_callback_func_user_data.first);
   EXPECT_EQ(1, my_on_submit_callback_func_user_data.second);

   // teardown
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__when_pressing_the_SUBMIT_key__when_the_result_string_is_blank__will_not_emit_an_event)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__when_pressing_the_SPACE_key__when_the_result_string_is_empty__will_not_append_a_space)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__when_pressing_the_SPACE_key__when_last_char_in_result_string_is_space__will_not_append_a_space)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTest,
   press_key_by_name__when_pressing_the_SPACE_key__will_append_a_space)
{
   // TODO
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   when_submitting_an_empty_text__will_set_showing_input_error_frame_to_true)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   software_keyboard.set_font_name("Lora-MediumItalic.ttf");

   // Input (with blank text)
   software_keyboard.press_key_by_name("SUBMIT");

   EXPECT_EQ(true, software_keyboard.get_showing_input_error_frame());
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   CAPTURE__when_showing_input_error_frame_is_true__will_render_the_input_error_frame)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   software_keyboard.set_font_name("Lora-MediumItalic.ttf");

   software_keyboard.show_input_error_frame({ "cannot be blank" });

   // Render
   clear();
   software_keyboard.render();
   al_flip_display();
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   CAPTURE__will_work_as_expected)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   software_keyboard.set_font_name("Lora-MediumItalic.ttf");

   std::vector<std::string> key_names_to_press =
      { "P", "r", "i", "n", "BACKSPACE", "n", "c", "e", "s", "s", "SPACE", "1" };

   for (auto &key_name_to_press : key_names_to_press)
   {
      software_keyboard.press_key_by_name(key_name_to_press);

      clear();
      software_keyboard.render();
      al_flip_display();
   }

   EXPECT_EQ("Princess 1", software_keyboard.get_result_string());
}


TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   // TODO: modify this to a TIMED_INTERACTIVE test
   DISABLED__INTERACTIVE__will_work_as_expected)
   //INTERACTIVE__will_work_as_expected)
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
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
      AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
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
               case ALLEGRO_KEY_UP:
                  software_keyboard.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  software_keyboard.move_cursor_down();
               break;

               case ALLEGRO_KEY_RIGHT:
                  software_keyboard.increment_cursor_pos();
               break;

               case ALLEGRO_KEY_LEFT:
                  software_keyboard.decrement_cursor_pos();
               break;

               case ALLEGRO_KEY_ENTER:
                  {
                     bool shift = (event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
                     if (shift) { software_keyboard.press_key_by_name("SUBMIT"); }
                     else { software_keyboard.press_key_under_cursor(); }
                  }
               break;

               case ALLEGRO_KEY_BACKSPACE:
                  software_keyboard.press_key_by_name("BACKSPACE");
               break;

               case ALLEGRO_KEY_SPACE:
                  software_keyboard.press_key_by_name("SPACE");
               break;

               default:
                  std::string s(1, event.keyboard.unichar);
                  software_keyboard.press_key_by_name(s);
               break;
            }
         }
         break;

         case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
            {
               std::string *emitted_event_data = (std::string *)event.user.data1;
               if (!emitted_event_data) throw std::runtime_error("Unexpected nullptr sound effect data error");
               std::cout << "INFO: emitted sound effect event for sound \"" << *emitted_event_data << "\"" << std::endl;
            }
         break;

         case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            {
               AllegroFlare::GameEvent *data = static_cast<AllegroFlare::GameEvent *>((void *)event.user.data1);
               if (!data) throw std::runtime_error("Unexpected GameEvent error");
               if (data->is_type(
                  AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_EVENT_TO_EMIT_ON_PRESSING_SUBMIT_KEY
               )) abort = true;
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



