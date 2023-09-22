

#include <AllegroFlare/Elements/ListBox.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ListBox::ListBox()
   : items({})
   , cursor_position(0)
   , wrap_at_edges(false)
{
}


ListBox::~ListBox()
{
}


void ListBox::set_wrap_at_edges(bool wrap_at_edges)
{
   this->wrap_at_edges = wrap_at_edges;
}


std::vector<std::pair<std::string, std::string>> ListBox::get_items() const
{
   return items;
}


int ListBox::get_cursor_position() const
{
   return cursor_position;
}


bool ListBox::get_wrap_at_edges() const
{
   return wrap_at_edges;
}


void ListBox::set_items(std::vector<std::pair<std::string, std::string>> items)
{
   cursor_position = 0;
   return;
}

bool ListBox::has_valid_currently_selected_item()
{
   if (items.empty()) return false;
   return true;
}

std::string ListBox::get_currently_selected_item_value()
{
   if (!(has_valid_currently_selected_item()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::get_currently_selected_item_value]: error: guard \"has_valid_currently_selected_item()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::get_currently_selected_item_value: error: guard \"has_valid_currently_selected_item()\" not met");
   }
   return items[cursor_position].second;
}

void ListBox::move_cursor_up()
{
   cursor_position--;
   if (cursor_position < 0)
   {
      if (wrap_at_edges) cursor_position = (items.size() - 1);
      else cursor_position = 0;
   }
   return;
}

void ListBox::move_cursor_down()
{
   cursor_position++;
   if (cursor_position >= items.size())
   {
      if (wrap_at_edges) cursor_position = 0;
      else cursor_position = (items.size() - 1);
   }
   return;
}


} // namespace Elements
} // namespace AllegroFlare


