#ifndef __UI_INT_SPINNER_HEADER
#define __UI_INT_SPINNER_HEADER




#include <allegro_flare/spinner_base.h>




class UIIntSpinner : public UISpinnerBase
{
private:
   int val;

public:
   UIIntSpinner(UIWidget *parent, float x, float y, float w, float h);

   void set_val(std::string strval) override;
   void increment() override;
   void decrement() override;

   int get_val();
};




#endif
