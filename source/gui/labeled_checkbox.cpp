


#include <allegro_flare/gui/widgets/labeled_checkbox.h>

#include <allegro5/allegro_primitives.h>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/widgets/checkbox.h>
#include <allegro_flare/gui/widgets/text.h>



FGUILabeledCheckbox::FGUILabeledCheckbox(FGUIWidget *parent, float x, float y, std::string label_text)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 100, 12*2 + 24))
   , padding(12)
   , checkbox(new FGUICheckbox(this, padding+12, padding+12, 24))
   , label(new FGUIText(this, padding*2+24, place.size.y*0.5, label_text))
{
   place.size.x = padding + checkbox->place.size.x + padding + label->place.size.x + padding;
}




void FGUILabeledCheckbox::on_click()
{
   // if the user clicks on anything *other* than the checkbox, toggle it manually
   if (!checkbox->is_mouse_over()) checkbox->toggle();
}   




void FGUILabeledCheckbox::on_draw()
{
   al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 2, 2, color::color(color::white, 0.2), 2.0);
}




void FGUILabeledCheckbox::on_message(FGUIWidget *sender, std::string message)
{
   // pass the message up the tree
   send_message_to_parent(message);
}




