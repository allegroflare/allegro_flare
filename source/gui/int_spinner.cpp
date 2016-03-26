




#include <allegro_flare/gui/widgets/int_spinner.h>

#include <allegro_flare/useful.h> // for tostring

#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/gui/widgets/button.h>





FGUIIntSpinner::FGUIIntSpinner(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUISpinner(parent, x, y, w, h)
   , val(0)
{
   text_input->set_text(tostring(val));
}




void FGUIIntSpinner::set_val(std::string strval)
{
   val = atoi(strval.c_str());
   text_input->set_text(tostring(val));
   on_change();
}




int FGUIIntSpinner::get_val()
{
   return val;
}




void FGUIIntSpinner::increment()
{
   val++;
   text_input->set_text(tostring(val));
   on_change();
}




void FGUIIntSpinner::decrement()
{
   val--;
   text_input->set_text(tostring(val));
   on_change();
}



