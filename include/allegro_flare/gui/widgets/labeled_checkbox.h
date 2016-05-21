#ifndef __UI_LABELED_CHECKBOX_HEADER
#define __UI_LABELED_CHECKBOX_HEADER


#include <allegro_flare/gui/widget.h>


class UICheckbox;
class UIText;


class UILabeledCheckbox : public UIWidget
{
private:
   float padding;
   UICheckbox *checkbox;
   UIText *label;

public:
   UILabeledCheckbox(UIWidget *parent, float x, float y, std::string label_text);

   void on_click() override;
   void on_draw() override;
   void on_message(UIWidget *sender, std::string message) override;
};



#endif

