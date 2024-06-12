

#include <AllegroFlare/Elements/AdvancingText.hpp>

#include <algorithm>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


AdvancingText::AdvancingText(std::string text)
   : text(text)
   , revealed_characters_count(0)
   , reveal_started_at(0.0f)
   , reveal_ended_at(0.0f)
   , reveal_rate_characters_per_second(DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND)
   , all_characters_are_revealed(false)
{
}


AdvancingText::~AdvancingText()
{
}


void AdvancingText::set_text(std::string text)
{
   this->text = text;
}


std::string AdvancingText::get_text() const
{
   return text;
}


int AdvancingText::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


float AdvancingText::get_reveal_started_at() const
{
   return reveal_started_at;
}


float AdvancingText::get_reveal_ended_at() const
{
   return reveal_ended_at;
}


float AdvancingText::get_reveal_rate_characters_per_second() const
{
   return reveal_rate_characters_per_second;
}


bool AdvancingText::get_all_characters_are_revealed() const
{
   return all_characters_are_revealed;
}


void AdvancingText::start()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AdvancingText::start]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AdvancingText::start]: error: guard \"al_is_system_installed()\" not met");
   }
   reveal_started_at = al_get_time(); // TODO: Replace with injected "time_now"
   reveal_ended_at = 0;
   revealed_characters_count = 0;
   all_characters_are_revealed = false;
   return;
}

void AdvancingText::set_reveal_rate_characters_per_second(float reveal_rate_characters_per_second)
{
   if (!((reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AdvancingText::set_reveal_rate_characters_per_second]: error: guard \"(reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AdvancingText::set_reveal_rate_characters_per_second]: error: guard \"(reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)\" not met");
   }
   this->reveal_rate_characters_per_second = reveal_rate_characters_per_second;
   return;
}

void AdvancingText::update()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AdvancingText::update]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AdvancingText::update]: error: guard \"al_is_system_installed()\" not met");
   }
   if (all_characters_are_revealed) return;

   float time_now = al_get_time(); // TODO: Replace with injected "time_now"
   float age = (time_now - reveal_started_at);
   int theoretical_revealed_characters_count = (int)(age * reveal_rate_characters_per_second);
   revealed_characters_count = std::min(theoretical_revealed_characters_count, (int)text.size());
   if (revealed_characters_count >= text.size())
   {
      all_characters_are_revealed = true;
      reveal_ended_at = time_now;
   }

   return;
}

void AdvancingText::reveal_all_characters()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AdvancingText::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AdvancingText::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met");
   }
   revealed_characters_count = text.size();
   all_characters_are_revealed = true;
   reveal_ended_at = al_get_time(); // TODO: Consider passing a "time_now"
}

std::string AdvancingText::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}


} // namespace Elements
} // namespace AllegroFlare


