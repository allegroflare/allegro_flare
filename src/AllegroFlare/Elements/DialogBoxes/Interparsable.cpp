

#include <AllegroFlare/Elements/DialogBoxes/Interparsable.hpp>

#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Interparsable::Interparsable(std::vector<std::string> pages)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::Interparsable::TYPE)
   , pages(pages)
   , speaking_character("")
   , current_page_num(-1)
   , num_revealed_characters(9999)
   , finished_at(0)
   , page_finished(false)
   , page_finished_at(0.0f)
{
}


Interparsable::~Interparsable()
{
}


void Interparsable::set_speaking_character(std::string speaking_character)
{
   this->speaking_character = speaking_character;
}


std::vector<std::string> Interparsable::get_pages() const
{
   return pages;
}


std::string Interparsable::get_speaking_character() const
{
   return speaking_character;
}


int Interparsable::get_current_page_num() const
{
   return current_page_num;
}


int Interparsable::get_num_revealed_characters() const
{
   return num_revealed_characters;
}


float Interparsable::get_finished_at() const
{
   return finished_at;
}


bool Interparsable::get_page_finished() const
{
   return page_finished;
}


float Interparsable::get_page_finished_at() const
{
   return page_finished_at;
}


void Interparsable::start()
{
   AllegroFlare::Logger::throw_error("AllegroFlare::Elements::DialogBoxes::Interparsable::start", "No implemented");
   //reset();
   //created_at = al_get_time();
   // TODO: Implement this, considering its relationship to "created_at"
   return;
}

bool Interparsable::has_speaking_character()
{
   return (!speaking_character.empty());
}

void Interparsable::update()
{
   if (get_finished()) return;
   if (!page_finished) num_revealed_characters++;
   if (!page_finished && all_characters_are_revealed())
   {
      page_finished = true;
      page_finished_at = al_get_time();
   }
   return;
}

void Interparsable::advance()
{
   if (get_finished()) return;
   if (!page_finished) reveal_all_characters();
   else next_page();
   return;
}

void Interparsable::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
   reset();
   return;
}

void Interparsable::reset()
{
   current_page_num = 0;
   set_finished(false);
   finished_at = 0;
   reset_current_page_counters();
   return;
}

std::string Interparsable::get_current_page_text()
{
   if (!current_page_is_valid()) return "[null]";
   return pages[current_page_num];
}

int Interparsable::get_current_page_num_chars()
{
   if (!current_page_is_valid()) return 0;
   return pages[current_page_num].size();
}

bool Interparsable::next_page()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Interparsable::next_page]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Interparsable::next_page]: error: guard \"al_is_system_installed()\" not met");
   }
   //if (at_last_page()) return false;
   if (get_finished()) return false;

   current_page_num++;
   reset_current_page_counters();

   if (current_page_num >= num_pages())
   {
      set_finished(true);
      finished_at = al_get_time();
      current_page_num = -1;
   }
   return true;
}

void Interparsable::reset_current_page_counters()
{
   page_finished = false;
   page_finished_at = 0;
   num_revealed_characters = 0;
   return;
}

int Interparsable::num_pages()
{
   return pages.size();
}

bool Interparsable::has_no_pages()
{
   return pages.empty();
}

bool Interparsable::at_last_page()
{
   return (current_page_num == (num_pages() - 1));
}

bool Interparsable::current_page_is_valid()
{
   if (pages.empty()) return false;
   if (current_page_num < 0) return false;
   if (current_page_num >= pages.size()) return false;
   return true;
}

void Interparsable::reveal_all_characters()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Interparsable::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Interparsable::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met");
   }
   num_revealed_characters = 9999;
   page_finished = true;
   page_finished_at = al_get_time();
}

bool Interparsable::all_characters_are_revealed()
{
   if (!current_page_is_valid()) return true;
   return num_revealed_characters >= get_current_page_num_chars();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


