

#include <allegro_flare/gui/family.h>

#include <allegro_flare/gui/widget.h>





FGUIFamily::FGUIFamily(FGUIWidget *parent)
   : progenitor(NULL)
   , parent(parent)
{}




void FGUIFamily::register_as_child(FGUIWidget *widget)
{
   if (!widget) return;

   if (!has_child(widget))
   {
      children.push_back(widget);
      //widget->parent = this; // yikes! just took this out
   }
}



#include <iostream>
void FGUIFamily::unregister_as_child(FGUIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
   {
      if (children[i] == widget)
      {
         children.erase(children.begin()+i);
         std::cout << "[FGUIFamily::detach_widget()] widget found and detached successfully." << std::endl;
         return;
      }
   }
   std::cout << "[FGUIFamily::detach_widget()] error - widget not found." << std::endl;
}




bool FGUIFamily::has_child(FGUIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
      if (widget == children[i]) return true;
   return false;
}



bool FGUIFamily::assign_child_to_new_parent(FGUIWidget *child_widget, FGUIWidget *new_parent)
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






bool FGUIFamily::set_focus_to_child(FGUIWidget *widget)
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





void FGUIFamily::delete_all()
{
   for (unsigned i=0; i<children.size(); i++)
      delete children[i];

   children.clear();
}



void FGUIFamily::unfocus_all()
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->is_focused()) children[i]->set_as_unfocused();
}



FGUIWidget *FGUIFamily::get_element_by_id(std::string id)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->attr.matches("id", id)) return children[i];

   return NULL;
}



FGUIWidget *FGUIFamily::get_1st_element_with_attr(std::string key)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->attr.has(key)) return children[i];

   return NULL;
}



FGUIWidget *FGUIFamily::get_1st_element_with_attr_val(std::string key, std::string val)
{
   for (unsigned i=0; i<children.size(); i++)
      if (children[i]->attr.matches(key, val)) return children[i];

   return NULL;
}






int FGUIFamily::_index_count = 0;




FGUIWidget *FGUIFamily::get_nth_descendant(int n)
{
   _index_count = 0;
   // note: the 0th child is the owner of this FGUIFamily.
   // TODO: perhaps this function should be promoted up to the Parent that calls it.
   return __get_nth_descendant_r(*this, n);
}

FGUIWidget *FGUIFamily::__get_nth_descendant_r(FGUIFamily &children, int n)
{
   FGUIWidget *widget = NULL;
   for (unsigned i=0; i<children.children.size(); i++)
   {
      _index_count++;
      FGUIWidget *p = children.children[i];
      widget = FGUIFamily::__get_nth_descendant_r(p->family, n);
      if (widget) return widget;
   }
   return NULL;
}





int FGUIFamily::get_num_descendants()
{
   _index_count = 1;
   return __get_num_descendants_r(*this);
}

int FGUIFamily::__get_num_descendants_r(FGUIFamily &children)
{
   for (unsigned i=0; i<children.children.size(); i++)
   {
      _index_count++;

      FGUIWidget *p = children.children[i];
      FGUIFamily::__get_num_descendants_r(p->family);
   }
   return _index_count;
}





void FGUIFamily::draw_all()
{
   for (unsigned i=0; i<children.size(); i++)
      children[i]->draw_func();
}




void FGUIFamily::draw_all_except(FGUIWidget *widget)
{
   for (unsigned i=0; i<children.size(); i++)
   {
      if (children[i] != widget) children[i]->draw_func();
   }
}

