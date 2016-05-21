#ifndef __UI_SPINNER_HEADER
#define __UI_SPINNER_HEADER




#include <allegro_flare/gui/widget.h>



class UITextInput;
class UIButton;


class UISpinner : public UIWidget
{
protected:
   UITextInput *text_input;
   UIButton *up_button;
   UIButton *down_button;

public:
   UISpinner(UIWidget *parent, float x, float y, float w, float h);

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

