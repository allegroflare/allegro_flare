

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
   , current_page_chunks({})
   , on_operational_chunk_func({})
   , on_operational_chunk_func_user_data(nullptr)
   , num_revealed_printable_characters(9999)
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


void Interparsable::set_on_operational_chunk_func(std::function<void(std::string, AllegroFlare::Elements::DialogBoxes::Interparsable*, void*)> on_operational_chunk_func)
{
   this->on_operational_chunk_func = on_operational_chunk_func;
}


void Interparsable::set_on_operational_chunk_func_user_data(void* on_operational_chunk_func_user_data)
{
   this->on_operational_chunk_func_user_data = on_operational_chunk_func_user_data;
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


std::vector<std::pair<bool, std::string>> Interparsable::get_current_page_chunks() const
{
   return current_page_chunks;
}


std::function<void(std::string, AllegroFlare::Elements::DialogBoxes::Interparsable*, void*)> Interparsable::get_on_operational_chunk_func() const
{
   return on_operational_chunk_func;
}


void* Interparsable::get_on_operational_chunk_func_user_data() const
{
   return on_operational_chunk_func_user_data;
}


int Interparsable::get_num_revealed_printable_characters() const
{
   return num_revealed_printable_characters;
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


std::vector<std::pair<bool, std::string>> Interparsable::parse_into_chunks(std::string raw_text_source)
{
   std::vector<std::pair<bool, std::string>> parsed_chunks;
   bool in_parens = false;
   std::string current_chunk;
   int open_paren_count = 0;

   for (size_t i=0; i<raw_text_source.size(); ++i)
   {
      char ch = raw_text_source[i];

      if (ch == '(')
      {
         if (in_parens)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
               "Nested parentheses were found in the text \"" + raw_text_source + "\". Nested parens are not "
                  "supported."
            );
         }

         // If entering parentheses, save current chunk if it exists
         if (!current_chunk.empty())
         {
            parsed_chunks.emplace_back(in_parens, current_chunk);
            current_chunk.clear();
         }
         in_parens = true;
         open_paren_count++;
      }
      else if (ch == ')')
      {
         if (!in_parens)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
               "There was an open paren that does not have a matching closing paren in the text \""
                  + raw_text_source + "\""
            );
         }

         // If leaving parentheses, save current chunk
         if (!current_chunk.empty())
         {
            parsed_chunks.emplace_back(in_parens, current_chunk);
            current_chunk.clear();
         }
         in_parens = false;
         open_paren_count--;
      }
      else
      {
         // Add character to the current chunk
         current_chunk += ch;
      }
   }

   // Add any remaining chunk
   if (!current_chunk.empty())
   {
      parsed_chunks.emplace_back(in_parens, current_chunk);
   }

   // Check for unmatched opening parenthesis
   if (open_paren_count != 0)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks",
         "Unmatched opening parenthesis found in text \"" + raw_text_source + "\""
      );
   }

   return parsed_chunks;
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
   if (!page_finished)
   {
      int num_revealed_printable_characters_before = num_revealed_printable_characters;
      num_revealed_printable_characters++;
      // HERE:
      // TODO: See if printable_characters overlapped an operational text chunk and call callback
      // FOR NOW:
      if (num_revealed_printable_characters_before == 26 && on_operational_chunk_func)
      {
         on_operational_chunk_func("placeholder-operational-func-text", this, on_operational_chunk_func_user_data);
      }
   }
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
   current_page_chunks = {}; // TODO: Test this
   return;
}

std::string Interparsable::get_current_page_text()
{
   if (!current_page_is_valid()) return "[null]";
   return pages[current_page_num];
}

int Interparsable::get_current_page_num_printable_chars()
{
   if (!current_page_is_valid()) return 0;
   return pages[current_page_num].size(); // TODO: have this calculated from text chunks
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
   else
   {
      // TODO: Test this
      current_page_chunks = parse_into_chunks(pages[current_page_num]);
   }
   return true;
}

void Interparsable::reset_current_page_counters()
{
   page_finished = false;
   page_finished_at = 0;
   num_revealed_printable_characters = 0;
   current_page_chunks = {};
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
   num_revealed_printable_characters = 9999;
   // TODO: Go through all command-like chunks
   page_finished = true;
   page_finished_at = al_get_time();
}

bool Interparsable::all_characters_are_revealed()
{
   if (!current_page_is_valid()) return true;
   return num_revealed_printable_characters >= get_current_page_num_printable_chars();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


