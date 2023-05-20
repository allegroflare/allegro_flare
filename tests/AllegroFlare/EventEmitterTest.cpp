
#include <gtest/gtest.h>

#include <AllegroFlare/EventEmitter.hpp>

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>



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
   emit_dialog_open_event__and__destroy_dialog_open_event__will_allocate_and_deallocate_without_leaks)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver::reset();

   al_init();

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::Testing::MemoryAllocationDeallocationObserver::enable_memory_tracking();
   event_emitter.emit_dialog_open_event("my_dialog_432");
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver::disable_memory_tracking();
   // Check that an allocation occurred
   EXPECT_EQ(1, AllegroFlare::Testing::MemoryAllocationDeallocationObserver::get_num_allocations());

   ALLEGRO_EVENT this_event;
   ASSERT_EQ(true, al_get_next_event(event_queue, &this_event));

   AllegroFlare::Testing::MemoryAllocationDeallocationObserver::enable_memory_tracking();
   AllegroFlare::EventEmitter::destroy_dialog_open_event_data(&this_event.user);
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver::disable_memory_tracking();
   // Check that a deallocation occurred
   EXPECT_EQ(1, AllegroFlare::Testing::MemoryAllocationDeallocationObserver::get_num_deallocations());

   // Check that an an equivelent of allocation and deallocation occurred
   EXPECT_EQ(
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::get_num_allocations(),
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::get_num_deallocations()
   );

   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
   al_uninstall_system();
}


