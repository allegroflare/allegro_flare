#ifndef __UI_SPINNER_BASE_HEADER
#define __UI_SPINNER_BASE_HEADER




#include <allegro_flare/widget.h>




class UITextInput;
class UIButton;




class UISpinnerBase : public UIWidget
{
protected:
   UITextInput *text_input;
   UIButton *up_button;
   UIButton *down_button;

public:
   UISpinnerBase(UIWidget *parent, std::string widget_typename, float x, float y, float w, float h);

   void on_draw() override;
   void on_message(UIWidget *sender, std::string message) override;
   void on_key_char() override;
   void on_change() override;

   // these are the pure virtual functions that require implementation
   // in the derived classes
   virtual void set_val(std::string strval) = 0;
   virtual void increment() = 0;
   virtual void decrement() = 0;
};




#endif
