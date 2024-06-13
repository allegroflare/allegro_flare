
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/VirtualControlsProcessor.hpp>

#include <AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData.hpp>
#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMappingFactory.hpp> // TODO: Remove this as dependency
#include <AllegroFlare/VirtualControllers/GenericController.hpp> // TODO: Remove this as dependency
#include <AllegroFlare/VirtualController.hpp>
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
      al_uninstall_joystick();
      al_uninstall_system();
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


TEST_F(AllegroFlare_VirtualControlsProcessorTest, 
   physical_input_device_to_virtual_control_mappings__is_empty_before_initialization)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_EQ(true, virtual_control_processor.get_physical_input_device_to_virtual_control_mappings_ref().empty());
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest, initialize__when_allegro_is_not_installed__will_throw_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "AllegroFlare::VirtualControlsProcessor::initialize",
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
      "AllegroFlare::VirtualControlsProcessor::initialize",
      "al_is_joystick_installed()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__without_an_input_devices_list__will_throw_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "AllegroFlare::VirtualControlsProcessor::initialize",
      "input_devices_list"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__without_an_event_emitter__will_throw_an_error)
{
   AllegroFlare::InputDevicesList input_devices_list;
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "AllegroFlare::VirtualControlsProcessor::initialize",
      "event_emitter"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__does_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::InputDevicesList input_devices_list;
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_event_emitter(&event_emitter);
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   virtual_control_processor.initialize();
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   DISABLED__initialize__will_assign_sensible_defaults_to_the_keyboard_button_map)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.initialize();

   //int PLAYER_0 = 0;
   //std::map<uint32_t, std::pair<int, int>> expected_keyboard_button_map = {
     //{ ALLEGRO_KEY_ENTER, { PLAYER_0, AllegroFlare::VirtualController::BUTTON_START } },
     //{ ALLEGRO_KEY_SPACE, { PLAYER_0, AllegroFlare::VirtualController::BUTTON_A } },
     //{ ALLEGRO_KEY_A,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_A } },
     //{ ALLEGRO_KEY_B,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_B } },
     //{ ALLEGRO_KEY_X,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_X } },
     //{ ALLEGRO_KEY_Y,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_Y } },
     //{ ALLEGRO_KEY_UP,    { PLAYER_0, AllegroFlare::VirtualController::BUTTON_UP } },
     //{ ALLEGRO_KEY_DOWN,  { PLAYER_0, AllegroFlare::VirtualController::BUTTON_DOWN } },
     //{ ALLEGRO_KEY_LEFT,  { PLAYER_0, AllegroFlare::VirtualController::BUTTON_LEFT } },
     //{ ALLEGRO_KEY_RIGHT, { PLAYER_0, AllegroFlare::VirtualController::BUTTON_RIGHT } },
     //{ ALLEGRO_KEY_R,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_RIGHT_BUMPER } },
     //{ ALLEGRO_KEY_E,     { PLAYER_0, AllegroFlare::VirtualController::BUTTON_LEFT_BUMPER } },
   //};

   //EXPECT_EQ(expected_keyboard_button_map, virtual_control_processor.get_keyboard_button_map());
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__will_set_initialized_to_true)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::InputDevicesList input_devices_list;
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_event_emitter(&event_emitter);
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   virtual_control_processor.initialize();

   EXPECT_EQ(true, virtual_control_processor.get_initialized());
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   initialize__when_called_more_than_once__throws_an_error)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::InputDevicesList input_devices_list;
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_event_emitter(&event_emitter);
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   virtual_control_processor.initialize();

   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.initialize(),
      "AllegroFlare::VirtualControlsProcessor::initialize",
      "(!initialized)"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_down_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.handle_raw_joystick_button_down_event(),
      "AllegroFlare::VirtualControlsProcessor::handle_raw_joystick_button_down_event",
      "initialized"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_button_up_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.handle_raw_joystick_button_up_event(),
      "AllegroFlare::VirtualControlsProcessor::handle_raw_joystick_button_up_event",
      "initialized"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_joystick_axis_change_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.handle_raw_joystick_axis_change_event(),
      "AllegroFlare::VirtualControlsProcessor::handle_raw_joystick_axis_change_event",
      "initialized"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_down_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.handle_raw_keyboard_key_down_event(),
      "AllegroFlare::VirtualControlsProcessor::handle_raw_keyboard_key_down_event",
      "initialized"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorTest,
   handle_raw_keyboard_key_up_event__without_initialization__throws_an_error)
{
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   EXPECT_THROW_GUARD_ERROR(
      virtual_control_processor.handle_raw_keyboard_key_up_event(),
      "AllegroFlare::VirtualControlsProcessor::handle_raw_keyboard_key_up_event",
      "initialized"
   );
}


TEST_F(AllegroFlare_VirtualControlsProcessorWithAllegroJoystickInstallTest,
   handle_raw_keyboard_key_down_event__on_an_event_with_a_mapped_button__will_emit_a_ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN)
{
   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();
   ASSERT_NE(nullptr, event_queue);
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::InputDevicesList input_devices_list;
   input_devices_list.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_event_emitter(&event_emitter);
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   virtual_control_processor.initialize();

   // Create our devices and their mappings
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMappingFactory factory; // TODO: remove factory as dependency
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping mapping =
      factory.create_single_player_keyboard_mapping_from_scratch();

   // Add our mapping to the virtual control processor
   virtual_control_processor.get_physical_input_device_to_virtual_control_mappings_ref() = { mapping };

   // Build a raw event
   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_KEY_DOWN;
   raw_event.keyboard.keycode = ALLEGRO_KEY_R;

   virtual_control_processor.handle_raw_keyboard_key_down_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT_BUMPER;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, actual_emitted_event.user.type);

   // Extract our event_data at data1
   void *data1 = (void*)actual_emitted_event.user.data1;
   ASSERT_NE(nullptr, data1);
   AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData
      *data_as_virtual_controller_button_pressed_event_data =
        static_cast<AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData*>(data1);

   // Verify the event_data is of the expected type
   ASSERT_EQ(
      AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData::TYPE,
      data_as_virtual_controller_button_pressed_event_data->get_type()
   );

   // Test our event_data
   EXPECT_EQ(
      expected_mapped_button,
      data_as_virtual_controller_button_pressed_event_data->get_virtual_controller_button_num()
   );

   // TODO: test additional data passed in through the event data

   // Cleanup
   delete data_as_virtual_controller_button_pressed_event_data;

   // TODO: add proper cleanup for remaining items (items created by factory)

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
   AllegroFlare::InputDevicesList input_devices_list;
   input_devices_list.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::VirtualControlsProcessor virtual_control_processor;
   virtual_control_processor.set_event_emitter(&event_emitter);
   virtual_control_processor.set_input_devices_list(&input_devices_list);
   virtual_control_processor.initialize();

   // Create our devices and their mappings
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMappingFactory factory; // TODO: remove factory as dependency
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping mapping =
      factory.create_single_player_keyboard_mapping_from_scratch();

   // Add our mapping to the virtual control processor
   virtual_control_processor.get_physical_input_device_to_virtual_control_mappings_ref() = { mapping };

   ALLEGRO_EVENT raw_event;
   raw_event.type = ALLEGRO_EVENT_KEY_UP;
   raw_event.keyboard.keycode = ALLEGRO_KEY_SPACE;

   virtual_control_processor.handle_raw_keyboard_key_up_event(&raw_event);

   int expected_mapped_button = AllegroFlare::VirtualControllers::GenericController::BUTTON_A;

   ALLEGRO_EVENT actual_emitted_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_emitted_event));

   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.type);
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, actual_emitted_event.user.type);

   // Extract our event_data at data1
   void *data1 = (void*)actual_emitted_event.user.data1;
   ASSERT_NE(nullptr, data1);
   AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData
      *data_as_virtual_controller_button_pressed_event_data =
        static_cast<AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData*>(data1);

   // Verify the event_data is of the expected type
   ASSERT_EQ(
      AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData::TYPE,
      data_as_virtual_controller_button_pressed_event_data->get_type()
   );

   // Test our event_data
   EXPECT_EQ(
      expected_mapped_button,
      data_as_virtual_controller_button_pressed_event_data->get_virtual_controller_button_num()
   );

   // TODO: test additional data passed in through the event data

   // Cleanup
   delete data_as_virtual_controller_button_pressed_event_data;

   // NOTE: not sure why this unregister line below is needed, but it seems that the deletion of one of the event 
   // emitting objects is not scheduled correctly, causing a crash (seems to only be happening during this test
   // on MacMini).
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}


