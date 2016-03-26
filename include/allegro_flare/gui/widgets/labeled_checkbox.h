#ifndef __FGUI_LABELED_CHECKBOX_HEADER
#define __FGUI_LABELED_CHECKBOX_HEADER


#include <allegro_flare/gui/widget.h>


class FGUICheckbox;
class FGUIText;


class FGUILabeledCheckbox : public FGUIWidget
{
private:
   float padding;
   FGUICheckbox *checkbox;
   FGUIText *label;

public:
   FGUILabeledCheckbox(FGUIWidget *parent, float x, float y, std::string label_text);

   void on_click() override;
   void on_draw() override;
   void on_message(FGUIWidget *sender, std::string message) override;
};



#endif

