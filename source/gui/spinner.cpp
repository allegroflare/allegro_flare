



#include <allegro_flare/gui/widgets/spinner.h>

#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/gui/widgets/button.h>

#include <allegro_flare/gui/surface_areas/box.h>

#include <allegro_flare/framework.h> // for af::current_event 




FGUISpinner::FGUISpinner(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
{
   float button_width = 29;

   text_input = new FGUITextInput(this, 0, 0, w, h);
   text_input->place.align = 0;

   up_button = new FGUIButton(this, w-button_width/2, h/4, button_width, h/2, "-");
   up_button->place.align = vec2d(0.5, 0.5);

   down_button = new FGUIButton(this, w-button_width/2, h/4*3, button_width, h/2, "-");
   down_button->place.align = vec2d(0.5, 0.5);
}




void FGUISpinner::on_draw() {}




void FGUISpinner::on_message(FGUIWidget *sender, std::string message)
{
   if (sender == up_button) increment();
   else if (sender == down_button) decrement();
   else if (sender == text_input)
   {
      // this functionality will require some refactoring internally
      set_val(text_input->get_text());
   }
}




void FGUISpinner::on_key_char()
{
   if (!focused) return;

   switch(af::current_event->keyboard.keycode)
   {
   case ALLEGRO_KEY_UP:
   case ALLEGRO_KEY_PAD_PLUS:
      increment();
      break;
   case ALLEGRO_KEY_DOWN:
   case ALLEGRO_KEY_PAD_MINUS:
      decrement();
      break;
   }
}




void FGUISpinner::on_change()
{
   if (family.parent) family.parent->on_message(this, "on_change");
}








