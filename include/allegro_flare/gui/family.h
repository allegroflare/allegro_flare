#ifndef __FGUI_FAMILY_HEADER
#define __FGUI_FAMILY_HEADER




#include <deque>
#include <vector>
#include <string>

class FGUIWidget;



class FGUIFamily
{
private:
   static int _index_count; // used internally for counting nodes in the tree

public:
   std::deque<FGUIWidget *> children; // hmm... some type of protection eventually maybe (not public)?

public:
   FGUIWidget *progenitor;
   FGUIWidget *parent;

   FGUIFamily(FGUIWidget *parent);

   bool has_child(FGUIWidget *widget);
   void register_as_child(FGUIWidget *widget);
   void unregister_as_child(FGUIWidget *widget);
   static bool assign_child_to_new_parent(FGUIWidget *child_widget, FGUIWidget *new_parent); // warning, this function may require some 
                                                                                             // safety usage guidelines
                                                                                             // reassigning a parent in the middle of
                                                                                             // a loop in the children could cause
                                                                                             // unintended consequences, for example

   bool set_focus_to_child(FGUIWidget *child);

   void unfocus_all();
   void delete_all();
   void draw_all();
   void draw_all_except(FGUIWidget *widget); // hmm... a solution to a scroll-view and/or portal view draw-func access problem.
                                   // I'm not sure about the appropriate solution to this one.

   // selection:
   int get_num_descendants();
   FGUIWidget *get_element_by_id(std::string id);
   FGUIWidget *get_1st_element_with_attr(std::string key); // not tested
   FGUIWidget *get_1st_element_with_attr_val(std::string key, std::string val); // not tested
   FGUIWidget *get_nth_descendant(int n);

private:
   // these are recursive search functions, they're entirely intended for internal use
   static FGUIWidget *__get_nth_descendant_r(FGUIFamily &children, int n); // todo: eliminate these static functions
   static int __get_num_descendants_r(FGUIFamily &children);
};




#endif
