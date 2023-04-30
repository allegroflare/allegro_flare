
#include <gtest/gtest.h>

#include <AllegroFlare/Routers/Standard.hpp>

#include <AllegroFlare/EventNames.hpp>


class TitleScreenTestClass : public AllegroFlare::Screens::Base
{
public:
   TitleScreenTestClass() : AllegroFlare::Screens::Base("TitleScreenTestClass") {}
};


TEST(AllegroFlare_Routers_StandardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Routers::Standard basic;
}


TEST(AllegroFlare_Routers_StandardTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Routers/Standard",
     AllegroFlare::Routers::Standard::TYPE
   );
}


TEST(AllegroFlare_Routers_StandardTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Routers::Standard basic;
   EXPECT_EQ(AllegroFlare::Routers::Standard::TYPE, basic.get_type());
}


TEST(AllegroFlare_Routers_StandardTest,
   on_route_event__with_an_EVENT_INITIALIZE_event__will_emit_an_EVENT_ACTIVATE_INTRO_LOGOS_SCREEN_event)
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::ScreenManagers::Dictionary screen_manager;
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::Routers::Standard router;
   router.set_screen_manager(&screen_manager);
   router.set_event_emitter(&event_emitter);
   
   using namespace AllegroFlare::Routers;
   router.on_route_event(Standard::EVENT_INITIALIZE);

   ALLEGRO_EVENT actual_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_event));
   ASSERT_EQ(true, ALLEGRO_EVENT_TYPE_IS_USER(actual_event.type));
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_ROUTER, actual_event.type);
   EXPECT_EQ(AllegroFlare::Routers::Standard::EVENT_ACTIVATE_INTRO_LOGOS_SCREEN, actual_event.user.data1);

   al_uninstall_system();
}


