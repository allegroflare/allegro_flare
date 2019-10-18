



#include <allegro_flare/labeled_checkbox.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/box.h>
#include <allegro_flare/checkbox.h>
#include <allegro_flare/text.h>
#include <AllegroFlare/Useful.hpp> // for to_string




namespace allegro_flare
{
   UILabeledCheckbox::UILabeledCheckbox(UIWidget *parent, float x, float y, std::string label_text)
      : UIWidget(parent, "UILabeledCheckbox", new UISurfaceAreaBox(x, y, 100, 12*2 + 24))
      , padding(12)
      , checkbox(new UICheckbox(this, padding+12, padding+12, 24))
      , label(new UIText(this, padding*2+24, place.size.y*0.5, label_text))
   {
      place.size.x = padding + checkbox->place.size.x + padding + label->place.size.x + padding;
   }




   void UILabeledCheckbox::on_click()
   {
      // if the user clicks on anything *other* than the checkbox, toggle it manually
      if (!checkbox->is_mouse_over()) checkbox->toggle();
   }   




   void UILabeledCheckbox::on_draw()
   {
      al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 2, 2, AllegroFlare::color::color(AllegroFlare::color::white, 0.2), 2.0);
   }




   void UILabeledCheckbox::on_message(UIWidget *sender, std::string message)
   {
      // pass the message up the tree
      send_message_to_parent(message);
   }
}



