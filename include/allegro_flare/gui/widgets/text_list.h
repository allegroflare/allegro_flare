#ifndef __UI_TEXT_LIST_HEADER
#define __UI_TEXT_LIST_HEADER




#include <string>
#include <vector>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/gui/widget.h>
#include <allegro_flare/Vec2D.hpp>




class UIListItem // TODO: maybe.. abstract UITextList into a UIList<T> template 
{
protected:
   std::string item;

public:
   UIListItem();
   virtual ~UIListItem();

   virtual vec2d draw_item(vec2d position) = 0; // returns the width/height of the item
};




class UITextList : public UIWidget
{
public:
   float item_padding;
   float item_height;
   int currently_selected_item;
   std::vector<std::string> items;

public:
   UITextList(UIWidget *parent, float x, float y, float w);
   virtual ~UITextList();

   void add_item(std::string item);
   void select_item(int index);
   std::string *get_item(int index);
   std::string *get_selected_item();
   void move_selected_item(int delta);
   float get_item_height(int index);
   int get_item_index_at(float x, float y);
   bool select_at(float x, float y);
   bool select_at_mouse_cursor();
   void draw_item(vec2d position, int index);

   void joy_down_func() override;
   void mouse_down_func() override;

   virtual void on_select();

   void on_key_char() override;
   void on_draw() override;
};




#endif
