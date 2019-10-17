#ifndef __UI_TOGGLE_BUTTON_HEADER
#define __UI_TOGGLE_BUTTON_HEADER




#include <string>
#include <allegro_flare/widget.h>




class UIToggleButton : public UIWidget
{
protected:
   bool pressed;
   std::string text;

public:
   UIToggleButton(UIWidget *parent, float x, float y, float w, float h, std::string _text="");

   void set_text(std::string text);

   bool toggle();
   bool set_as_pressed();
   bool set_as_unpressed();
   void silently_set_as_pressed();
   void silently_set_as_unpressed();

   bool is_pressed();

   void on_draw() override;
   void on_click() override;
   void on_change() override;
};




#endif
