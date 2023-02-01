
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/VirtualControlsProcessor.hpp>

#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/EventNames.hpp>

class AllegroFlare_VirtualControlsProcessorTest : public ::testing::Test {};
class AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest : public ::testing::Test
{
   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(false, al_is_joystick_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_install_joystick());
   }

   virtual void TearDown() override
   {
      std::cout << "XXX" << std::endl;
      al_uninstall_joystick();
      std::cout << "YYY" << std::endl;
      al_uninstall_system();
      std::cout << "ZZZ" << std::endl;
   }
};


TEST_F(AllegroFlare_VirtualControlsProcessorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest, initialized__has_the_expected_default_value)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(false, virtual_control_processor.get_initialized());
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest, keyboard_button_map__is_empty_before_initialization)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(true, virtual_control_processor.get_keyboard_button_map().empty());
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest, joystick_button_map__is_empty_before_initialization)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(true, virtual_control_processor.get_joystick_button_map().empty());
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest, initialize__when_allegro_is_not_installed__will_throw_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "VirtualControlsProcessor::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   initialize__when_allegro_joysticks_have_not_been_installed__will_throw_an_error)
{
   al_init();
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "VirtualControlsProcessor::initialize",
      "al_is_joystick_installed()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__does_not_blow_up)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__will_assign_sensible_defaults_to_the_keyboard_button_map)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   /*
   int PLAYER_0 = 0;
   std::map<uint32_t, std::pair<int, int>> expected_keyboard_button_map = {
     { ALLEGRO_KEY_ENTER, { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_START } },
     { ALLEGRO_KEY_SPACE, { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_A } },
     { ALLEGRO_KEY_A,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_A } },
     { ALLEGRO_KEY_B,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_B } },
     { ALLEGRO_KEY_X,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_X } },
     { ALLEGRO_KEY_Y,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_Y } },
     { ALLEGRO_KEY_UP,    { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_UP } },
     { ALLEGRO_KEY_DOWN,  { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_DOWN } },
     { ALLEGRO_KEY_LEFT,  { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_LEFT } },
     { ALLEGRO_KEY_RIGHT, { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_RIGHT } },
     { ALLEGRO_KEY_R,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_RIGHT_BUMPER } },
     { ALLEGRO_KEY_E,     { PLAYER_0, AllegroFlare::VirtualControls::BUTTON_LEFT_BUMPER } },
   };
   */

   //EXPECT_EQ(expected_keyboard_button_map, virtual_control_processor.get_keyboard_button_map());
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__will_assign_sensible_defaults_to_the_joystick_button_map)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   /*
   std::map<int, int> expected_joystick_button_map = {
     { 1, AllegroFlare::VirtualControls::BUTTON_A },
     { 0, AllegroFlare::VirtualControls::BUTTON_B },
     { 4, AllegroFlare::VirtualControls::BUTTON_X },
     { 3, AllegroFlare::VirtualControls::BUTTON_Y },
     { 6, AllegroFlare::VirtualControls::BUTTON_LEFT_BUMPER },
     { 7, AllegroFlare::VirtualControls::BUTTON_RIGHT_BUMPER },
     { 11, AllegroFlare::VirtualControls::BUTTON_START },
   };
   */

   //EXPECT_EQ(expected_joystick_button_map, virtual_control_processor.get_joystick_button_map());
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__will_set_initialized_to_true)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();
   EXPECT_EQ(true, virtual_control_processor.get_initialized());
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__when_called_more_than_once__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "VirtualControlsProcessor::initialize",
      "(!initialized)"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
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


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_joystick_button_down_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN)
{
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
   raw_event.joystick.id = (ALLEGRO_JOYSTICK*)(nullptr);
   raw_event.joystick.button = 1;

   virtual_control_processor.handle_raw_joystick_button_down_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControls::BUTTON_A;
      std::cout << "GG" << std::endl;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));
      std::cout << "HH" << std::endl;

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.type);
      std::cout << "II" << std::endl;
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.user.type);
      std::cout << "JJ" << std::endl;
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);
      std::cout << "KK" << std::endl;

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_joystick_button_up_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP)
{
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

   int expected_mapped_button = AllegroFlare::VirtualControls::BUTTON_X;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_joystick_axis_change_event__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE)
{
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
   ASSERT_EQ(-1, actual_emitted_event.user.data1); // TODO: handle the mapping of the player number, which could
                                                   // flake if an actual joystick is connected during the test.
   ASSERT_EQ(3, actual_emitted_event.user.data2);
   ASSERT_EQ(2, actual_emitted_event.user.data3);
   ASSERT_EQ(127, actual_emitted_event.user.data4);

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_keyboard_key_down_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN)
{
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

   int expected_mapped_button = AllegroFlare::VirtualControls::BUTTON_RIGHT_BUMPER;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_keyboard_key_up_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP)
{
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

   int expected_mapped_button = AllegroFlare::VirtualControls::BUTTON_A;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.user.type);
   ASSERT_EQ(expected_mapped_button, actual_emitted_event.user.data2);

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


