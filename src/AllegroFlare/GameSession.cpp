

#include <AllegroFlare/GameSession.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


GameSession::GameSession()
   : started_at(0.0f)
   , ended_at(0.0f)
   , level_progress({})
{
}


GameSession::~GameSession()
{
}


void GameSession::set_level_progress(std::set<std::string> level_progress)
{
   this->level_progress = level_progress;
}


float GameSession::get_started_at() const
{
   return started_at;
}


float GameSession::get_ended_at() const
{
   return ended_at;
}


std::set<std::string> GameSession::get_level_progress() const
{
   return level_progress;
}


void GameSession::start_session(float started_at)
{
   if (!((!is_active())))
   {
      std::stringstream error_message;
      error_message << "[GameSession::start_session]: error: guard \"(!is_active())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameSession::start_session: error: guard \"(!is_active())\" not met");
   }
   this->started_at = started_at;
   return;
}

void GameSession::end_session(float ended_at)
{
   if (!(is_active()))
   {
      std::stringstream error_message;
      error_message << "[GameSession::end_session]: error: guard \"is_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameSession::end_session: error: guard \"is_active()\" not met");
   }
   this->ended_at = ended_at;
   return;
}

bool GameSession::is_active()
{
   return started_at != 0.0f && ended_at == 0.0f;
}

void GameSession::mark_level_as_finished(std::string level_identifier)
{
   // NOTE: Granted, this is a very basic way to record progress. A more advanced version might have levels
   // with specific objectives, or a "completed_at" time, so on.
   level_progress.insert(level_identifier);
   return;
}

bool GameSession::is_level_as_finished(std::string level_identifier)
{
   // TODO: Test this
   return level_progress.count(level_identifier) >= 1;
}


} // namespace AllegroFlare


