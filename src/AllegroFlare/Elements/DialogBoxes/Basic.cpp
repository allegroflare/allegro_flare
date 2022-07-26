

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Basic::Basic(std::vector<std::string> pages)
   : AllegroFlare::Elements::DialogBoxes::Base("Basic")
   , pages(pages)
   , current_page_num(-1)
   , finished(false)
   , num_revealed_characters(9999)
{
}


Basic::~Basic()
{
}


std::vector<std::string> Basic::get_pages()
{
   return pages;
}


int Basic::get_current_page_num()
{
   return current_page_num;
}


bool Basic::get_finished()
{
   return finished;
}


int Basic::get_num_revealed_characters()
{
   return num_revealed_characters;
}


void Basic::update()
{
   num_revealed_characters++;
   return;
}

void Basic::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
   reset();
   return;
}

void Basic::reset()
{
   current_page_num = 0;
   num_revealed_characters = 0;
   finished = false;
   return;
}

std::string Basic::get_current_page_text()
{
   if (!current_page_is_valid()) return "[null]";
   return pages[current_page_num];
}

bool Basic::next_page()
{
   //if (at_last_page()) return false;
   if (get_finished()) return false;
   current_page_num++;
   num_revealed_characters = 0;
   if (current_page_num >= num_pages())
   {
      finished = true;
      current_page_num = -1;
   }
   return true;
}

int Basic::num_pages()
{
   return pages.size();
}

bool Basic::has_no_pages()
{
   return pages.empty();
}

bool Basic::at_last_page()
{
   return (current_page_num == (num_pages() - 1));
}

bool Basic::current_page_is_valid()
{
   if (pages.empty()) return false;
   if (current_page_num < 0) return false;
   if (current_page_num >= pages.size()) return false;
   return true;
}

void Basic::reveal_all_characters()
{
   num_revealed_characters = 9999;
}
} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


