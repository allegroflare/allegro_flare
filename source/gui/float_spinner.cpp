




#include <allegro_flare/gui/widgets/float_spinner.h>

#include <allegro_flare/useful.h> // for tostring

#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/gui/widgets/button.h>





FGUIFloatSpinner::FGUIFloatSpinner(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUISpinner(parent, x, y, w, h)
   , val(0.0)
   , increment_amount(0.1)
{
   text_input->set_text(tostring(val));
}




void FGUIFloatSpinner::set_val(std::string strval)
{
   val = atof(strval.c_str());
   text_input->set_text(tostring(val));
   on_change();
}




void FGUIFloatSpinner::set_increment(float increment_amount)
{
   this->increment_amount = increment_amount;
}




float FGUIFloatSpinner::get_val()
{
   return val;
}




void FGUIFloatSpinner::increment()
{
   val += increment_amount;
   text_input->set_text(tostring(val));
   on_change();
}




void FGUIFloatSpinner::decrement()
{
   val -= increment_amount;
   text_input->set_text(tostring(val));
   on_change();
}



