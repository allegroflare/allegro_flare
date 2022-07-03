
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/VirtualControlsProcessor.hpp>


#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/EventNames.hpp>


TEST(AllegroFlare_VirtualControlsProcessorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialized__has_the_expected_default_value)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(false, virtual_control_processor.get_initialized());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, keyboard_button_map__is_empty_before_initialization)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(true, virtual_control_processor.get_keyboard_button_map().empty());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, joystick_button_map__is_empty_before_initialization)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(true, virtual_control_processor.get_joystick_button_map().empty());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialize__does_not_blow_up)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();
   SUCCEED();
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialize__will_assign_sensible_defaults_to_the_keyboard_button_map)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;

   virtual_control_processor.initialize();

   std::map<int, int> expected_keyboard_button_map = {
     { ALLEGRO_KEY_ENTER, AllegroFlare::VirtualControls::get_BUTTON_START() },
     { ALLEGRO_KEY_SPACE, AllegroFlare::VirtualControls::get_BUTTON_B() },
     { ALLEGRO_KEY_A, AllegroFlare::VirtualControls::get_BUTTON_A() },
     { ALLEGRO_KEY_B, AllegroFlare::VirtualControls::get_BUTTON_B() },
     { ALLEGRO_KEY_X, AllegroFlare::VirtualControls::get_BUTTON_X() },
     { ALLEGRO_KEY_Y, AllegroFlare::VirtualControls::get_BUTTON_Y() },
     { ALLEGRO_KEY_UP, AllegroFlare::VirtualControls::get_BUTTON_UP() },
     { ALLEGRO_KEY_DOWN, AllegroFlare::VirtualControls::get_BUTTON_DOWN() },
     { ALLEGRO_KEY_LEFT, AllegroFlare::VirtualControls::get_BUTTON_LEFT() },
     { ALLEGRO_KEY_RIGHT, AllegroFlare::VirtualControls::get_BUTTON_RIGHT() },
     { ALLEGRO_KEY_R, AllegroFlare::VirtualControls::get_BUTTON_RIGHT_BUMPER() },
     { ALLEGRO_KEY_E, AllegroFlare::VirtualControls::get_BUTTON_LEFT_BUMPER() },
   };

   EXPECT_EQ(expected_keyboard_button_map, virtual_control_processor.get_keyboard_button_map());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialize__will_assign_sensible_defaults_to_the_joystick_button_map)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;

   virtual_control_processor.initialize();

   std::map<int, int> expected_joystick_button_map = {
     { 1, AllegroFlare::VirtualControls::get_BUTTON_A() },
     { 0, AllegroFlare::VirtualControls::get_BUTTON_B() },
     { 4, AllegroFlare::VirtualControls::get_BUTTON_X() },
     { 3, AllegroFlare::VirtualControls::get_BUTTON_Y() },
     { 6, AllegroFlare::VirtualControls::get_BUTTON_LEFT_BUMPER() },
     { 7, AllegroFlare::VirtualControls::get_BUTTON_RIGHT_BUMPER() },
     { 11, AllegroFlare::VirtualControls::get_BUTTON_START() },
   };

   EXPECT_EQ(expected_joystick_button_map, virtual_control_processor.get_joystick_button_map());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialize__will_set_initialized_to_true)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();
   EXPECT_EQ(true, virtual_control_processor.get_initialized());
}


TEST(AllegroFlare_VirtualControlsProcessorTest, initialize__when_called_more_than_once__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "foo";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.initialize(),
      std::runtime_error,
      "VirtualControlsProcessor::initialize: error: guard \"(!initialized)\" not met"
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_down_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_button_down_event: "
                                        "error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_button_down_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_down_event__without_an_event_emitter__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_button_down_event: "
                                        "error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_button_down_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_up_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_button_up_event: "
                                        "error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_button_up_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_up_event__without_an_event_emitter__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_button_up_event: "
                                        "error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_button_up_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_axis_change_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_axis_change_event: "
                                        "error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_axis_change_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_axis_change_event__without_an_event_emitter__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_joystick_axis_change_event: "
                                        "error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_joystick_axis_change_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_kwy_down_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_keyboard_key_down_event: "
                                        "error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_keyboard_key_down_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_down_event__without_an_event_emitter__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_keyboard_key_down_event: "
                                        "error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_keyboard_key_down_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_up_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_keyboard_key_up_event: "
                                        "error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_keyboard_key_up_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_up_event__without_an_event_emitter__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   std::string expected_error_message = "VirtualControlsProcessor::handle_raw_keyboard_key_up_event: "
                                        "error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      virtual_control_processor.handle_raw_keyboard_key_up_event(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_down_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor(&event_emitter);
   virtual_control_processor.initialize();

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN;
   raw_event.joystick.button = 1;

   virtual_control_processor.handle_raw_joystick_button_down_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControls::get_BUTTON_A();

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   al_uninstall_system();
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_up_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor(&event_emitter);
   virtual_control_processor.initialize();

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_JOYSTICK_BUTTON_UP;
   raw_event.joystick.button = 4;

   virtual_control_processor.handle_raw_joystick_button_up_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControls::get_BUTTON_X();

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   al_uninstall_system();
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_axis_change_event__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor(&event_emitter);
   virtual_control_processor.initialize();

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_JOYSTICK_AXIS;
   raw_event.joystick.stick = 3;
   raw_event.joystick.axis = 2;
   raw_event.joystick.pos = 0.5;

   virtual_control_processor.handle_raw_joystick_axis_change_event(&raw_event);

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE, actual_emitted_event.user.type);
   ASSERT_EQ(3, actual_emitted_event.user.data1);
   ASSERT_EQ(2, actual_emitted_event.user.data2);
   ASSERT_EQ(127, actual_emitted_event.user.data3);

   al_uninstall_system();
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_down_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor(&event_emitter);
   virtual_control_processor.initialize();

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_KEY_DOWN;
   raw_event.keyboard.keycode = ALLEGRO_KEY_R;

   virtual_control_processor.handle_raw_keyboard_key_down_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControls::get_BUTTON_RIGHT_BUMPER();

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   al_uninstall_system();
}


TEST(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_up_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor(&event_emitter);
   virtual_control_processor.initialize();

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_KEY_UP;
   raw_event.keyboard.keycode = ALLEGRO_KEY_SPACE;

   virtual_control_processor.handle_raw_keyboard_key_up_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControls::get_BUTTON_B();

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   al_uninstall_system();
}


