

#include <AllegroFlare/GameSession.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


GameSession::GameSession()
   : started_at(0.0f)
   , ended_at(0.0f)
   , active(false)
   , playtime_tracker()
   , game_progress_and_state_info(nullptr)
{
}


GameSession::~GameSession()
{
}


void GameSession::set_game_progress_and_state_info(AllegroFlare::GameProgressAndStateInfos::Base* game_progress_and_state_info)
{
   this->game_progress_and_state_info = game_progress_and_state_info;
}


float GameSession::get_started_at() const
{
   return started_at;
}


float GameSession::get_ended_at() const
{
   return ended_at;
}


bool GameSession::get_active() const
{
   return active;
}


AllegroFlare::GameProgressAndStateInfos::Base* GameSession::get_game_progress_and_state_info() const
{
   return game_progress_and_state_info;
}


AllegroFlare::PlaytimeTracker &GameSession::get_playtime_tracker_ref()
{
   return playtime_tracker;
}


void GameSession::start_or_resume_playtime_tracking()
{
   if (!(active))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameSession::start_or_resume_playtime_tracking]: error: guard \"active\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameSession::start_or_resume_playtime_tracking]: error: guard \"active\" not met");
   }
   AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME, "Starting (or resuming) playtime tracking.");
   playtime_tracker.start();
   return;
}

void GameSession::suspend_playtime_tracking()
{
   if (!(active))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameSession::suspend_playtime_tracking]: error: guard \"active\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameSession::suspend_playtime_tracking]: error: guard \"active\" not met");
   }
   AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME, "Suspending playtime tracking.");
   playtime_tracker.pause();
   return;
}

void GameSession::start_session(float started_at)
{
   if (!((!active)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameSession::start_session]: error: guard \"(!active)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameSession::start_session]: error: guard \"(!active)\" not met");
   }
   AllegroFlare::Logger::info_from("AllegroFlare::GameSession::start_session", "Starting session.");
   active = true;
   this->started_at = started_at;
   return;
}

void GameSession::end_session(float ended_at)
{
   if (!(active))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameSession::end_session]: error: guard \"active\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameSession::end_session]: error: guard \"active\" not met");
   }
   AllegroFlare::Logger::info_from("AllegroFlare::GameSession::start_session", "Ending session.");
   active = false;
   this->ended_at = ended_at;
   return;
}

bool GameSession::is_active()
{
   return active;
}


} // namespace AllegroFlare


