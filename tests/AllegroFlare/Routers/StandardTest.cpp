
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


class RouteEventDataTestClass : public AllegroFlare::RouteEventDatas::Base
{
public:
   int function_call_count;
   RouteEventDataTestClass()
      : AllegroFlare::RouteEventDatas::Base("RouteEventDataTestClass")
      , function_call_count(0)
   {}
};


//class GameplayScreenTestClass : public AllegroFlare::Screens::Gameplay
//{
//public:
   //int gameplay_suspend_func_call_count;
   //int gameplay_resume_func_call_count;
   //GameplayScreenTestClass()
      //: AllegroFlare::Screens::Gameplay()
      //, gameplay_suspend_func_call_count(0)
      //, gameplay_resume_func_call_count(0)
   //{}
   //void virtual gameplay_suspend_func() override
   //{
      //gameplay_suspend_func_call_count++;
   //}
   //void virtual gameplay_resume_func() override
   //{
      //gameplay_resume_func_call_count++;
   //}
//};


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
      screen_manager.set_event_emitter(&event_emitter);
      router.set_event_emitter(&event_emitter);
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
      std::string expected_response_event =
         AllegroFlare::Routers::Standard::name_for_route_event(response_event);
      std::string actual_response_event =
         AllegroFlare::Routers::Standard::name_for_route_event(actual_event.user.data1);
      EXPECT_EQ(response_event, actual_event.user.data1) << "Expected: " << expected_response_event << ", "
                                                         << "Actual: " << actual_response_event;
   }
   virtual void TearDown() override
   {
      // TODO: Proper teardown of EventEmitter
      al_destroy_event_queue(event_queue);
      al_uninstall_system();
   }
   static bool my_load_level_handler(AllegroFlare::RouteEventDatas::Base *route_event_data)
   {
      RouteEventDataTestClass *my_route_event_data = static_cast<RouteEventDataTestClass*>(route_event_data);
      my_route_event_data->function_call_count++;
      return true;
   }
   static bool my_load_level_handler_that_returns_true(AllegroFlare::RouteEventDatas::Base *route_event_data)
   {
      return true;
   }
   static bool my_load_level_handler_that_returns_false(AllegroFlare::RouteEventDatas::Base *route_event_data)
   {
      return false;
   }
   static bool my_on_route_event_unhandled_func_returns_true(
         uint32_t unhandled_event,
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      (*((int*)user_data))++;
      return true;
   }
   static bool my_on_route_event_unhandled_func_returns_false(
         uint32_t unhandled_event,
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      return false;
   }
   static bool my_on_route_event_unhandled_func_relays_unhandled_event(
         uint32_t unhandled_event,
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      (*((uint32_t*)user_data)) = unhandled_event;
      return true;
   }
   static bool my_on_create_new_session_func(
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      // TODO: Modify the game session Progress member:
      //AllegroFlare::GameProgressAndStateInfos::Base *game_progress =
      if (router->get_game_session_ref().get_game_progress_and_state_info())
      {
         // In your game, you might delete existing progress here
      }

      router->get_game_session_ref().set_game_progress_and_state_info(
         new AllegroFlare::GameProgressAndStateInfos::Base() // Use Base for now, to demonstrate creating new save info
      );
      (*((int*)user_data))++;
      return true;
   }
   static bool my_on_load_last_played_session_or_start_new_func(
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      // TODO: Modify the game session Progress member:
      //AllegroFlare::GameProgressAndStateInfos::Base *game_progress =
      if (router->get_game_session_ref().get_game_progress_and_state_info())
      {
         // In your game, you might delete existing progress here
      }

      router->get_game_session_ref().set_game_progress_and_state_info(
         new AllegroFlare::GameProgressAndStateInfos::Base() // Use Base for now, to demonstrate creating new save info
      );
      (*((int*)user_data))++;
      return true;
   }
   static bool my_on_primary_gameplay_screen_finished_func(
         AllegroFlare::Routers::Standard *router,
         void* user_data
      )
   {
      (*((int*)user_data))++;
      return true;
   }
   static void my_on_gameplay_paused_func(AllegroFlare::Routers::Standard *router, void* user_data)
   {
      (*((int*)user_data))++;
   }
   static void my_on_gameplay_unpaused_func(AllegroFlare::Routers::Standard *router, void* user_data)
   {
      (*((int*)user_data))++;
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
   on_route_event__when_a_callback_is_present__will_call_the_callback)
{
   uint32_t MY_CUSTOM_ROUTE_EVENT = AllegroFlare::Routers::Standard::EVENT_LAST_EVENT+1;
   int callback_count = 0;
   router.set_on_route_event_unhandled_func(my_on_route_event_unhandled_func_returns_true);
   router.set_on_route_event_unhandled_func_user_data(&callback_count);
   router.on_route_event(MY_CUSTOM_ROUTE_EVENT);
   EXPECT_EQ(1, callback_count);
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__when_a_callback_is_present_that_returns_false__will_raise_an_exception)
{
   router.set_on_route_event_unhandled_func(my_on_route_event_unhandled_func_returns_false);
   EXPECT_THROW_WITH_MESSAGE(
      router.on_route_event(123),
      std::runtime_error,
      "[AllegroFlare::Routers::Standard::on_route_event]: error: A user callback was used to handle an unknown "
            "event of type 123, but the callback returned false, indicating that there was a failure to handle "
            "the event."
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__when_a_callback_is_present_that_returns_true__will_pass_the_unhandled_event_to_the_callback)
{
   router.set_on_route_event_unhandled_func(my_on_route_event_unhandled_func_relays_unhandled_event);
   uint32_t MY_CUSTOM_ROUTE_EVENT = AllegroFlare::Routers::Standard::EVENT_LAST_EVENT+1;
   uint32_t relayed_unhandled_event = 0;
   router.set_on_route_event_unhandled_func(my_on_route_event_unhandled_func_relays_unhandled_event);
   router.set_on_route_event_unhandled_func_user_data(&relayed_unhandled_event);
   router.on_route_event(MY_CUSTOM_ROUTE_EVENT);
   EXPECT_EQ(MY_CUSTOM_ROUTE_EVENT, relayed_unhandled_event);
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
   on_route_event__with_an_EVENT_START_NEW_GAME_event__will_emit_an_EVENT_ACTIVATE_TITLE_SCREEN_route_event)
{
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_START_NEW_GAME,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_INITIALIZE_event__will_call_the__on_load_last_played_session_or_start_new_func__\
and_start_a_new_session)
{
   ASSERT_EQ(nullptr, router.get_game_session_ref().get_game_progress_and_state_info());

   int call_count = 0;
   router.set_on_create_new_session_func(my_on_create_new_session_func);
   router.set_on_create_new_session_func_user_data(&call_count);
   router.set_on_load_last_played_session_or_start_new_func(my_on_load_last_played_session_or_start_new_func);
   router.set_on_load_last_played_session_or_start_new_func_user_data(&call_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_INITIALIZE);

   EXPECT_EQ(1, call_count);
   EXPECT_EQ(true, router.get_game_session_ref().is_active());
   // For our example usage in this test, we will create new GameProgressAndStateInfo in the session
   EXPECT_NE(nullptr, router.get_game_session_ref().get_game_progress_and_state_info());
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_START_NEW_GAME_event__when_there_is_already_a_session_currently_active__\
will_stop_the_existing_session__call_the__on_create_new_session_func__and_start_a_new_session)
{
   router.get_game_session_ref().start_session();
   float initial_session_started_at = router.get_game_session_ref().get_started_at();
   al_rest(0.01);
   ASSERT_EQ(nullptr, router.get_game_session_ref().get_game_progress_and_state_info());

   int call_count = 0;
   router.set_on_create_new_session_func(my_on_create_new_session_func);
   router.set_on_create_new_session_func_user_data(&call_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_START_NEW_GAME);

   EXPECT_EQ(1, call_count);
   EXPECT_EQ(true, router.get_game_session_ref().is_active());
   EXPECT_NE(initial_session_started_at, router.get_game_session_ref().get_started_at());
   // For our example usage in this test, we will create new GameProgressAndStateInfo in the session
   EXPECT_NE(nullptr, router.get_game_session_ref().get_game_progress_and_state_info());
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
   DISABLED__on_route_event__with_an_EVENT_START_LEVEL_event__if_the_load_level_handler_returns_false__will_not_emit_\
an_EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN_route_event)
{
   // TODO: This test
   //router.get_game_session_ref().start_session();
   //router.set_load_level_handler(my_load_level_handler_that_returns_false);
   //TEST_EXPECTED_ROUTE_EVENT(
      //AllegroFlare::Routers::Standard::EVENT_START_LEVEL,
      //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN
   //);
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_START_LEVEL_event__if_the_load_level_handler_returns_true__will_emit_an_\
EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   router.set_load_level_handler(my_load_level_handler_that_returns_true);
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_START_LEVEL,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_START_LEVEL_event__when_a_load_level_handler_is_present__will_call_the_handler)
{
   // TODO: Assess this function call
   router.set_load_level_handler(my_load_level_handler);
   RouteEventDataTestClass route_event_data;
   // TODO: Validate session
   // router.get_game_session_ref().start_session();
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_START_LEVEL, &route_event_data);
   EXPECT_EQ(1, route_event_data.function_call_count);
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
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN
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
EVENT_ACTIVATE_GAME_WON_SCREEN_route_event)
{
   router.get_game_session_ref().start_session();
   TEST_EXPECTED_ROUTE_EVENT(
      AllegroFlare::Routers::Standard::EVENT_CREDITS_SCREEN_FINISHED,
      AllegroFlare::Routers::Standard::EVENT_ACTIVATE_GAME_WON_SCREEN
   );
}


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED_event__will_call_the__\
on_primary_gameplay_screen_finished_func)
{
   int call_count = 0;

   router.set_on_primary_gameplay_screen_finished_func(my_on_primary_gameplay_screen_finished_func);
   router.set_on_primary_gameplay_screen_finished_func_user_data(&call_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED);

   EXPECT_EQ(1, call_count);
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


/*
// NOTE: This behavior no longer exists
TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   DISABLED__on_route_event__with_an_EVENT_PAUSE_GAME_event__will_suspend_playtime_tracking)
{
   AllegroFlare::GameSession &game_session = router.get_game_session_ref();
   AllegroFlare::PlaytimeTracker &playtime_tracker = game_session.get_playtime_tracker_ref();

   game_session.start_session();
   playtime_tracker.start();

   ASSERT_EQ(true, playtime_tracker.is_tracking());

   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME);

   EXPECT_EQ(false, playtime_tracker.is_tracking());
}
*/


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_PAUSE_GAME_event__will_call_the_on_gameplay_paused_func)
{
   router.get_game_session_ref().start_session(); // TODO: Alternatively, add option to disable playtime tracking

   int call_count = 0;
   router.set_on_gameplay_paused_func(my_on_gameplay_paused_func);
   router.set_on_gameplay_paused_func_user_data(&call_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME);
   EXPECT_EQ(1, call_count);
}


/*
// NOTE: This behavior no longer exists
TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_UNPAUSE_GAME_event__will_resume_suspended_playtime_tracking)
{
   AllegroFlare::GameSession &game_session = router.get_game_session_ref();
   AllegroFlare::PlaytimeTracker &playtime_tracker = game_session.get_playtime_tracker_ref();

   game_session.start_session();

   ASSERT_EQ(false, playtime_tracker.is_tracking());

   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_UNPAUSE_GAME);

   EXPECT_EQ(true, playtime_tracker.is_tracking());
}
*/


TEST_F(AllegroFlare_Routers_StandardTestWithSetup,
   on_route_event__with_an_EVENT_UNPAUSE_GAME_event__will_call_the_on_gameplay_unpaused_func)
{
   router.get_game_session_ref().start_session(); // TODO: Alternatively, add option to disable playtime tracking
   int call_count = 0;
   router.set_on_gameplay_unpaused_func(my_on_gameplay_unpaused_func);
   router.set_on_gameplay_unpaused_func_user_data(&call_count);
   router.on_route_event(AllegroFlare::Routers::Standard::EVENT_UNPAUSE_GAME);
   EXPECT_EQ(1, call_count);
}


