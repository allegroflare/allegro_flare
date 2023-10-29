

#include <AllegroFlare/Elements/ListBox.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ListBox::ListBox()
   : items({})
   , created_at(0)
   , cursor_position(0)
   , wrap_at_edges(false)
{
}


ListBox::~ListBox()
{
}


void ListBox::set_created_at(float created_at)
{
   this->created_at = created_at;
}


void ListBox::set_wrap_at_edges(bool wrap_at_edges)
{
   this->wrap_at_edges = wrap_at_edges;
}


std::vector<std::pair<std::string, std::string>> ListBox::get_items() const
{
   return items;
}


float ListBox::get_created_at() const
{
   return created_at;
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
   this->items = items;
   cursor_position = 0;
   return;
}

std::vector<std::string> ListBox::get_item_labels()
{
   std::vector<std::string> result;
   for (auto &item : items)
   {
      result.push_back(item.first);
   }
   return result;
}

int ListBox::num_items()
{
   return items.size();
}

bool ListBox::has_valid_currently_selected_item()
{
   if (items.empty()) return false;
   return true;
}

std::string ListBox::get_currently_selected_item_label()
{
   if (!(has_valid_currently_selected_item()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::get_currently_selected_item_label]: error: guard \"has_valid_currently_selected_item()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::get_currently_selected_item_label: error: guard \"has_valid_currently_selected_item()\" not met");
   }
   return items[cursor_position].first;
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

float ListBox::infer_age(float time_now)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::infer_age]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::infer_age: error: guard \"al_is_system_installed()\" not met");
   }
   return time_now - get_created_at();
}

void ListBox::set_cursor_position(int cursor_position)
{
   if (!((cursor_position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[ListBox::set_cursor_position]: error: guard \"(cursor_position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::set_cursor_position: error: guard \"(cursor_position >= 0)\" not met");
   }
   if (!(((cursor_position < items.size()) || (cursor_position == 0))))
   {
      std::stringstream error_message;
      error_message << "[ListBox::set_cursor_position]: error: guard \"((cursor_position < items.size()) || (cursor_position == 0))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::set_cursor_position: error: guard \"((cursor_position < items.size()) || (cursor_position == 0))\" not met");
   }
   // TODO: Test this method
   this->cursor_position = cursor_position;
   return;
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


