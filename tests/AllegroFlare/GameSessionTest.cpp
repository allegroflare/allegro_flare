
#include <gtest/gtest.h>

#include <AllegroFlare/GameSession.hpp>


TEST(AllegroFlare_GameSessionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameSession game_session;
}


TEST(AllegroFlare_GameSessionTest, start_session__will_set_started_at)
{
   AllegroFlare::GameSession game_session;
   game_session.start_session(123.0f);
   EXPECT_EQ(123.0f, game_session.get_started_at());
}


TEST(AllegroFlare_GameSessionTest, end_session__will_set_ended_at)
{
   AllegroFlare::GameSession game_session;
   game_session.start_session(123.0f);
   game_session.end_session(456.0f);
   EXPECT_EQ(456.0f, game_session.get_ended_at());
}


