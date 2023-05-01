
#include <gtest/gtest.h>

#include <AllegroFlare/Routers/Standard.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/EventNames.hpp>


class ScreenATestClass : public AllegroFlare::Screens::Base
{
public:
   int activation_count;
   ScreenATestClass()
      : AllegroFlare::Screens::Base("TitleScreenTestClass")
      , activation_count(0)
   {}
   virtual void on_activate() { activation_count++; }
};


class AllegroFlare_Routers_StandardTest : public ::testing::Test
{
public:
   AllegroFlare_Routers_StandardTest() : ::testing::Test() {}
};


class AllegroFlare_Routers_StandardTestWithSetup : public ::testing::Test
{
protected:
   ALLEGRO_EVENT_QUEUE *event_queue;
   AllegroFlare::ScreenManagers::Dictionary screen_manager;
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Routers::Standard router;

public:
   AllegroFlare_Routers_StandardTestWithSetup()
      : ::testing::Test()
      , event_queue(nullptr)
      , screen_manager()
      , event_emitter()
      , router()
   {}
   virtual void SetUp() override
   {
      al_init();
      event_queue = al_create_event_queue();
      event_emitter.initialize();
      al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
      router.set_screen_manager(&screen_manager);
      router.set_event_emitter(&event_emitter);
   }
   void TEST_EXPECTED_ROUTE_EVENT(uint32_t emitted_event, uint32_t response_event)
   {
      router.on_route_event(emitted_event);
      ALLEGRO_EVENT actual_event;
      ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_event));
      ASSERT_EQ(true, ALLEGRO_EVENT_TYPE_IS_USER(actual_event.type));
      ASSERT_EQ(ALLEGRO_FLARE_EVENT_ROUTER, actual_event.type);
      EXPECT_EQ(response_event, actual_event.user.data1);
   }
   virtual void TearDown() override
   {
      // TODO: Proper teardown of EventEmitter
      al_destroy_event_queue(event_queue);
      al_uninstall_system();
   }
};


TEST_F(AllegroFlare_Routers_StandardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Routers::Standard basic;
}


TEST_F(AllegroFlare_Routers_StandardTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Routers/Standard",
     AllegroFlare::Routers::Standard::TYPE
   );
}


TEST_F(AllegroFlare_Routers_StandardTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Routers::Standard basic;
   EXPECT_EQ(AllegroFlare::Routers::Standard::TYPE, basic.get_type());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup, game_session__is_not_active_by_default)
{
   EXPECT_EQ(false, router.get_game_session_ref().is_active());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__on_an_unknown_event__will_throw_an_error)
{
   EXPECT_THROW_WITH_MESSAGE(
      router.on_route_event(123),
      std::runtime_error,
      "[AllegroFlare::Routers::Standard::on_route_event]: error: Unable to handle event of type 123."
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_INITIALIZE_event__will_emit_an_EVENT_ACTIVATE_INTRO_LOGOS_SCREEN_route_event)
{
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_INITIALIZE,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_INTRO_LOGOS_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_START_NEW_GAME_event__will_start_the_session)
{
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_START_NEW_GAME);
   EXPECT_EQ(true, router.get_game_session_ref().is_active());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_ACTIVATE_INTRO_LOGOS_SCREEN_event__will_activate_the_\
INTRO_LOGOS_SCREEN_IDENTIFIER_screen)
{
   ScreenATestClass screen_a;
   router.register_screen(AllegroFlare::Routers::Standard::INTRO_LOGOS_SCREEN_IDENTIFIER, &screen_a);

   EXPECT_EQ(0, screen_a.activation_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_ACTIVATE_INTRO_LOGOS_SCREEN);
   EXPECT_EQ(1, screen_a.activation_count);
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_WIN_GAME_event__when_a_session_is_not_active__will_throw_an_error)
{
   EXPECT_THROW_WITH_MESSAGE(
      router.on_route_event(AllegroFlare::Routers::Standard::EVENT_WIN_GAME),
      std::runtime_error,
      "[AllegroFlare::Routers::Standard::on_route_event]: error: When handling an EVENT_WIN_GAME, the game_session "
         "is expected to be active but it was not."
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_WIN_GAME__when_a_session_is_active__will_end_the_session)
{
   router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_WIN_GAME);
   EXPECT_EQ(false, router.get_game_session_ref().is_active());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_WIN_GAME_event__will_emit_an_\
EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_WIN_GAME,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_LOSE_GAME_event__when_a_session_is_not_active__will_throw_an_error)
{
   EXPECT_THROW_WITH_MESSAGE(
      router.on_route_event(AllegroFlare::Routers::Standard::EVENT_LOSE_GAME),
      std::runtime_error,
      "[AllegroFlare::Routers::Standard::on_route_event]: error: When handling an EVENT_LOSE_GAME, the game_session "
         "is expected to be active but it was not."
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_LOSE_GAME__when_a_session_is_active__will_end_the_session)
{
   router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_LOSE_GAME);
   EXPECT_EQ(false, router.get_game_session_ref().is_active());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_LOSE_GAME_event__will_emit_an_\
EVENT_ACTIVATE_GAME_OVER_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_LOSE_GAME,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_GAME_OVER_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_EXIT_GAME_event__if_a_session_is_active__will_end_the_session)
{
   router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_EXIT_GAME);
   EXPECT_EQ(false, router.get_game_session_ref().is_active());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_EXIT_GAME_event__will_emit_an_ALLEGRO_FLARE_EVENT_EXIT_GAME_event)
{
   router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_EXIT_GAME);
   EXPECT_EQ(false, router.get_game_session_ref().is_active());

   ALLEGRO_EVENT actual_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &actual_event));
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_EXIT_GAME, actual_event.type);
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_EXIT_TO_TITLE_SCREEN_event__when_a_session_is_not_active__will_throw_an_error)
{
   EXPECT_THROW_WITH_MESSAGE(
      router.on_route_event(AllegroFlare::Routers::Standard::EVENT_EXIT_TO_TITLE_SCREEN),
      std::runtime_error,
      "[AllegroFlare::Routers::Standard::on_route_event]: error: When handling an EVENT_EXIT_TO_TITLE_SCREEN, the "
         "game_session is expected to be active but it was not."
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_EXIT_TO_TITLE_SCREEN_event__if_a_session_is_active__will_end_the_session)
{
   router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_EXIT_TO_TITLE_SCREEN);
   EXPECT_EQ(false, router.get_game_session_ref().is_active());
}



TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_INTRO_LOGOS_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_INTRO_LOGOS_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_INTRO_STORYBOARD_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_TITLE_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_INTRO_STORYBOARD_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_LEVEL_SELECT_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_LEVEL_SELECT_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_LEVEL_SELECT_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_CREDITS_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_CREDITS_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_LEVEL_SELECT_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_CREDITS_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_GAME_WON_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_TITLE_SCREEN_FINISHED_event__will_emit_an_\
EVENT_ACTIVATE_INTRO_LOGOS_SCREEN_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_TITLE_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_INTRO_LOGOS_SCREEN
   );
}


