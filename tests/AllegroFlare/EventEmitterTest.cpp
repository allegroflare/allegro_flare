
#include <gtest/gtest.h>

#include <AllegroFlare/EventEmitter.hpp>


bool tracking = false;
int alloc_count = 0;
int dealloc_count = 0;

// Override global new and delete operators
void* operator new(std::size_t size)
{
    void* ptr = std::malloc(size);
    if (tracking) alloc_count++;
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    if (tracking) dealloc_count++;
    std::free(ptr);
}


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
   al_init();

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   tracking = true;
   event_emitter.emit_dialog_open_event("Foobar");
   tracking = false;

   ALLEGRO_EVENT this_event;
   ASSERT_EQ(true, al_get_next_event(event_queue, &this_event));

   tracking = true;
   AllegroFlare::EventEmitter::destroy_dialog_open_event_data(&this_event.user);
   tracking = false;

   EXPECT_EQ(alloc_count, dealloc_count);

   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
   al_uninstall_system();
}


