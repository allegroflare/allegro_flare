#ifndef __UI_FAMILY_HEADER
#define __UI_FAMILY_HEADER




#include <deque>
#include <vector>
#include <string>

class UIWidget;



class UIFamily
{
private:
   static int _index_count; // used internally for counting nodes in the tree

public:
   std::deque<UIWidget *> children; // hmm... some type of protection eventually maybe (not public)?

public:
   UIWidget *progenitor;
   UIWidget *parent;

   UIFamily(UIWidget *parent);

   bool has_child(UIWidget *widget);
   void register_as_child(UIWidget *widget);
   void unregister_as_child(UIWidget *widget);
   static bool assign_child_to_new_parent(UIWidget *child_widget, UIWidget *new_parent); // warning, this function may require some 
                                                                                             // safety usage guidelines
                                                                                             // reassigning a parent in the middle of
                                                                                             // a loop in the children could cause
                                                                                             // unintended consequences, for example

   bool set_focus_to_child(UIWidget *child);

   void unfocus_all();
   void delete_all();
   void draw_all();
   void draw_all_except(UIWidget *widget); // hmm... a solution to a scroll-view and/or portal view draw-func access problem.
                                   // I'm not sure about the appropriate solution to this one.

   // selection:
   int get_num_descendants();
   UIWidget *get_element_by_id(std::string id);
   UIWidget *get_1st_element_with_attr(std::string key); // not tested
   UIWidget *get_1st_element_with_attr_val(std::string key, std::string val); // not tested
   UIWidget *get_nth_descendant(int n);

private:
   // these are recursive search functions, they're entirely intended for internal use
   static UIWidget *__get_nth_descendant_r(UIFamily &children, int n); // todo: eliminate these static functions
   static int __get_num_descendants_r(UIFamily &children);
};




#endif
