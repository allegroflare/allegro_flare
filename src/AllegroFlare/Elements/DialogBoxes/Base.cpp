

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Base::Base(std::string type, std::vector<std::string> pages)
   : type(type)
   , pages(pages)
   , current_page_num(-1)
   , finished(false)
   , num_revealed_characters(9999)
   , created_at(0)
{
}


Base::~Base()
{
}


void Base::set_created_at(float created_at)
{
   this->created_at = created_at;
}


std::string Base::get_type()
{
   return type;
}


std::vector<std::string> Base::get_pages()
{
   return pages;
}


int Base::get_current_page_num()
{
   return current_page_num;
}


bool Base::get_finished()
{
   return finished;
}


int Base::get_num_revealed_characters()
{
   return num_revealed_characters;
}


float Base::get_created_at()
{
   return created_at;
}


void Base::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
   reset();
   return;
}

void Base::reset()
{
   current_page_num = 0;
   num_revealed_characters = 0;
   finished = false;
   return;
}

void Base::update()
{
   num_revealed_characters++;
   return;
}

std::string Base::get_current_page_text()
{
   if (!current_page_is_valid()) return "[null]";
   return pages[current_page_num];
}

bool Base::next_page()
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

int Base::num_pages()
{
   return pages.size();
}

bool Base::has_no_pages()
{
   return pages.empty();
}

bool Base::at_last_page()
{
   return (current_page_num == (num_pages() - 1));
}

bool Base::current_page_is_valid()
{
   if (pages.empty()) return false;
   if (current_page_num < 0) return false;
   if (current_page_num >= pages.size()) return false;
   return true;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

void Base::reveal_all_characters()
{
   num_revealed_characters = 9999;
}
} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


