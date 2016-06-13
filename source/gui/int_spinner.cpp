



#include <allegro_flare/gui/widgets/int_spinner.h>

#include <allegro_flare/gui/widgets/button.h>
#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/useful.h> // for tostring




UIIntSpinner::UIIntSpinner(UIWidget *parent, float x, float y, float w, float h)
   : UISpinner(parent, x, y, w, h)
   , val(0)
{
   attr.set(UI_ATTR__UI_WIDGET_TYPE, "UIIntSpinner");
   attr.set("id", "IntSpinner" + tostring(get_num_created_widgets()));

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




