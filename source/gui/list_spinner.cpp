



#include <allegro_flare/gui/widgets/list_spinner.h>

#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/gui/widgets/button.h>





FGUIListSpinner::FGUIListSpinner(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUISpinner(parent, x, y, w, h)
   , items()
   , it(items.begin())
{}




int FGUIListSpinner::add_item(std::string item)
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




int FGUIListSpinner::add_items(std::vector<std::string> new_items)
{
   items.insert(items.end(), new_items.begin(), new_items.end());
   // refresh the iterator (important)
   it = items.begin();
      text_input->set_text(*it);
   return items.size();
}




void FGUIListSpinner::sort()
{
   std::sort(items.begin(), items.end());
}




std::string FGUIListSpinner::get_val()
{
   if (items.empty()) return "";
   return (*it);
}




void FGUIListSpinner::set_val(std::string strval)
{
   // the behavior of this function will do nothing
}




void FGUIListSpinner::increment()
{
   if (items.empty()) return;

   it--;
   if (it < items.begin()) it = items.end()-1;
   text_input->set_text(*it);
   on_change();
}




void FGUIListSpinner::decrement()
{
   if (items.empty()) return;

   it++;
   if (it >= items.end()) it = items.begin();
   text_input->set_text(*it);
   on_change();
}   





