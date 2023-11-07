

#include <AllegroFlare/Elements/DialogBoxes/Intertitle.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Intertitle::Intertitle(std::string text)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE)
   , text(text)
   , revealed_characters_count(0)
   , all_characters_revealed_at(0.0f)
   , wait_duration_after_all_characters_are_revealed(3.0f)
{
}


Intertitle::~Intertitle()
{
}


void Intertitle::set_text(std::string text)
{
   this->text = text;
}


std::string Intertitle::get_text() const
{
   return text;
}


int Intertitle::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


float Intertitle::get_all_characters_revealed_at() const
{
   return all_characters_revealed_at;
}


float Intertitle::get_wait_duration_after_all_characters_are_revealed() const
{
   return wait_duration_after_all_characters_are_revealed;
}


void Intertitle::start()
{
   revealed_characters_count = 0;
   all_characters_revealed_at = 0.0f;
   set_finished(false);
   return;
}

void Intertitle::update()
{
   if (get_finished()) return;

   float time_now = al_get_time();

   if (!all_characters_are_revealed())
   {
      revealed_characters_count++;
      if (revealed_characters_count >= text.size())
      {
         all_characters_revealed_at = time_now;
      }
   }
   else // all characters are revealed
   {
      float all_characters_revealed_age = time_now - all_characters_revealed_at;

      bool should_finish = (all_characters_revealed_age > wait_duration_after_all_characters_are_revealed);

      if (should_finish)
      {
         set_finished(true);
      }
   }
   return;
}

void Intertitle::advance()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Intertitle::advance]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Intertitle::advance: error: guard \"al_is_system_installed()\" not met");
   }
   if (get_finished()) return;

   float time_now = al_get_time(); // TODO: Consider injected alternative

   if (!all_characters_are_revealed())
   {
      reveal_all_characters();
      all_characters_revealed_at = time_now;
   }
   else // all characters are revealed
   {
      // TODO: Consider triggering a fade out
      set_finished(true);
   }

   // TODO - should this also finished = true?
   return;
}

std::string Intertitle::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

void Intertitle::reveal_all_characters()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Intertitle::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Intertitle::reveal_all_characters: error: guard \"al_is_system_installed()\" not met");
   }
   if (all_characters_are_revealed()) return;

   float time_now = al_get_time(); // TODO: Consider injected alternative

   all_characters_revealed_at = time_now;
   revealed_characters_count = text.size();
}

bool Intertitle::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


