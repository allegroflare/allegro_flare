#ifndef __FGUI_SPINNER_HEADER
#define __FGUI_SPINNER_HEADER




#include <allegro_flare/gui/widget.h>



class FGUITextInput;
class FGUIButton;


class FGUISpinner : public FGUIWidget
{
protected:
   FGUITextInput *text_input;
   FGUIButton *up_button;
   FGUIButton *down_button;

public:
   FGUISpinner(FGUIWidget *parent, float x, float y, float w, float h);

   void on_draw() override;
   void on_message(FGUIWidget *sender, std::string message) override;
   void on_key_char() override;
   void on_change() override;

   // these are the pure virtual functions that require implementation
   // in the derived classes
   virtual void set_val(std::string strval) = 0;
   virtual void increment() = 0;
   virtual void decrement() = 0;
};






#endif

