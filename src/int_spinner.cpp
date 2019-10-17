



#include <allegro_flare/int_spinner.h>

#include <allegro_flare/button.h>
#include <allegro_flare/text_input.h>
#include <AllegroFlare/Useful.hpp> // for tostring




UIIntSpinner::UIIntSpinner(UIWidget *parent, float x, float y, float w, float h)
   : UISpinnerBase(parent, "UIIntSpinner", x, y, w, h)
   , val(0)
{
   text_input->set_text(tostring(val));
}




void UIIntSpinner::set_val(std::string strval)
{
   val = atoi(strval.c_str());
   text_input->set_text(tostring(val));
   on_change();
}




int UIIntSpinner::get_val()
{
   return val;
}




void UIIntSpinner::increment()
{
   val++;
   text_input->set_text(tostring(val));
   on_change();
}




void UIIntSpinner::decrement()
{
   val--;
   text_input->set_text(tostring(val));
   on_change();
}




