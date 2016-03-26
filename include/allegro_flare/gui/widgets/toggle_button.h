#ifndef __FGUI_TOGGLE_BUTTON_HEADER
#define __FGUI_TOGGLE_BUTTON_HEADER




#include <string>

#include <allegro_flare/gui/widget.h>




class FGUIToggleButton : public FGUIWidget
{
protected:
   bool pressed;
   std::string text;

public:
   FGUIToggleButton(FGUIWidget *parent, float x, float y, float w, float h, std::string _text="");

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

