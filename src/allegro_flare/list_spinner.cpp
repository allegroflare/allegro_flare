



#include <allegro_flare/list_spinner.h>

#include <allegro_flare/button.h>
#include <allegro_flare/text_input.h>
#include <AllegroFlare/Useful.hpp> // for to_string




UIListSpinner::UIListSpinner(UIWidget *parent, float x, float y, float w, float h)
   : UISpinnerBase(parent, "UIListSpinner", x, y, w, h)
   , items()
   , it(items.begin())
{}





int UIListSpinner::add_item(std::string item)
{
   items.push_back(item);
   // note: whenever an item is added or removed, it's important that
   // the iterator is refreshed.  Because the container is a vector,
   // it can potentially reallocate itself in memory when resizing,
   // potentially leaving the iterator dangling.
   it = items.begin();
   text_input->set_text(*it);
   return items.size();
}




int UIListSpinner::add_items(std::vector<std::string> new_items)
{
   items.insert(items.end(), new_items.begin(), new_items.end());
   // refresh the iterator (important)
   it = items.begin();
   text_input->set_text(*it);
   return items.size();
}




void UIListSpinner::sort()
{
   std::sort(items.begin(), items.end());
}




std::string UIListSpinner::get_val()
{
   if (items.empty()) return "";
   return (*it);
}




void UIListSpinner::set_val(std::string strval)
{
   // the behavior of this function will do nothing
}




void UIListSpinner::increment()
{
   if (items.empty()) return;

   it--;
   if (it < items.begin()) it = items.end()-1;
   text_input->set_text(*it);
   on_change();
}




void UIListSpinner::decrement()
{
   if (items.empty()) return;

   it++;
   if (it >= items.end()) it = items.begin();
   text_input->set_text(*it);
   on_change();
}   




