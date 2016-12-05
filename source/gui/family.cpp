



#include <allegro_flare/gui/family.h>

#include <iostream>
#include <allegro_flare/gui/widget.h>




int UIFamily::_index_count = 0;




UIFamily::UIFamily(UIWidget *parent)
   : progenitor(nullptr)
   , parent(parent)
{}




void UIFamily::register_as_child(UIWidget *widget)
{
   if (!widget) return;

   if (!has_child(widget))
   {
      children.push_back(widget);
      //widget->parent = this; // yikes! just took this out
   }
}




void UIFamily::unregister_as_child(UIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
   {
      if (children[i] == widget)
      {
         children.erase(children.begin()+i);
         std::cout << "[UIFamily::detach_widget()] widget found and detached successfully." << std::endl;
         return;
      }
   }
   std::cout << "[UIFamily::detach_widget()] error - widget not found." << std::endl;
}




bool UIFamily::has_child(UIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
      if (widget == children[i]) return true;
   return false;
}




bool UIFamily::assign_child_to_new_parent(UIWidget *child_widget, UIWidget *new_parent)
{
   // have the current parent remove this child
   if (!child_widget) { std::cout << "err1" << std::endl; return false; } // TODO: fix crappy error messages

   if (child_widget->family.parent)
   {
      child_widget->family.parent->family.unregister_as_child(child_widget);
   }

   // assign the parent to the new parent
   if (new_parent)
   {
      new_parent->family.register_as_child(child_widget);
   }
   else
   {
      std::cout << "warning: registering a child to a NULL parent - (TODO: implement this functionality)" << std::endl;
      new_parent->family.register_as_child(NULL); //< is this ok?? right now, nothing really happens with this functionality
      // it's akin to a dangling pointer and the child is left without
   }

   return true;
}




bool UIFamily::set_focus_to_child(UIWidget *widget)
{
   // make sure the child is not already focused
   if (widget && widget->is_focused()) return false;

   // if there are other widgets that have focus, blur them
   for (unsigned i=0; i<this->children.size(); i++)
   {
      if (children[i]->is_focused())
         children[i]->set_as_unfocused();
   }

   if (widget)
   {
      widget->focused = true;
      widget->on_focus();
   }

   return true;
}




void UIFamily::delete_all()
{
   for (unsigned i=0; i<children.size(); i++)
      delete children[i];

   children.clear();
}




void UIFamily::unfocus_all()
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->is_focused()) children[i]->set_as_unfocused();
}




UIWidget *UIFamily::get_element_by_id(std::string id)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->exists("id", id)) return children[i];

   return NULL;
}




UIWidget *UIFamily::get_1st_element_with_attr(std::string key)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->exists(key)) return children[i];

   return NULL;
}




UIWidget *UIFamily::get_1st_element_with_attr_val(std::string key, std::string val)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->exists(key, val)) return children[i];

   return NULL;
}




UIWidget *UIFamily::get_nth_descendant(int n)
{
   _index_count = 0;
   // note: the 0th child is the owner of this UIFamily.
   // TODO: perhaps this function should be promoted up to the Parent that calls it.
   return __get_nth_descendant_r(*this, n);
}




UIWidget *UIFamily::__get_nth_descendant_r(UIFamily &children, int n)
{
   UIWidget *widget = NULL;
   for (unsigned i=0; i<children.children.size(); i++)
   {
      _index_count++;
      UIWidget *p = children.children[i];
      widget = UIFamily::__get_nth_descendant_r(p->family, n);
      if (widget) return widget;
   }
   return NULL;
}




int UIFamily::get_num_descendants()
{
   _index_count = 0;
   return __get_num_descendants_r(*this);
}




int UIFamily::__get_num_descendants_r(UIFamily &children)
{
   for (unsigned i=0; i<children.children.size(); i++)
   {
      _index_count++;

      UIWidget *p = children.children[i];
      UIFamily::__get_num_descendants_r(p->family);
   }
   return _index_count;
}




bool UIFamily::has_descendant(UIWidget *widget)
{
   int num_desc = get_num_descendants();

   for (unsigned i=0; i<num_desc; i++)
      if (get_nth_descendant(i) == widget) return true;
   return false;
}




void UIFamily::draw_all()
{
   for (unsigned i=0; i<children.size(); i++)
      children[i]->draw_func();
}




void UIFamily::draw_all_except(UIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
   {
      if (children[i] != widget) children[i]->draw_func();
   }
}




