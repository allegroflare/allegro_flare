
#include <gtest/gtest.h>

#include <AllegroFlare/EventEmitter.hpp>


TEST(AllegroFlare_EventEmitterTest, can_be_created_without_blowing_up)
{
   AllegroFlare::EventEmitter event_emitter;
}


TEST(AllegroFlare_EventEmitterTest, emit_event__without_initialization___raises_an_exception)
{
   // TODO
}


TEST(AllegroFlare_EventEmitterTest, emit_event__pushes_a_user_event_to_the_event_source_with_the_expected_parameters)
{
   // TODO
}


TEST(AllegroFlare_EventEmitterTest,
   emit_screen_switch_event__pushes_a_screen_switch_event_to_the_event_source_with_the_expected_parameters)
{
   // TODO
}


TEST(AllegroFlare_EventEmitterTest,
   emit_virtual_controls_button_up_event__will_push_a_WICKED_EVENT_VIRTUAL_BUTTON_UP_event_with_the_expected_params)
{
   // TODO
}


TEST(AllegroFlare_EventEmitterTest,
   emit_virtual_controls_button_down_event__will_push_a_WICKED_EVENT_VIRTUAL_BUTTON_DOWN_event_with_the_expected_params)
{
   // TODO
}


TEST(AllegroFlare_EventEmitterTest,
   emit_virtual_controls_axis_change_event__will_push_a_WICKED_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE_event_with_the_expected_params)
{
   // TODO
}


