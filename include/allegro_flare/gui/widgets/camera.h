#pragma once




#include <allegro_flare/gui/widget.h>




class UICamera : public UIWidget
{
public:
   UICamera(UIWidget *parent, float x, float y, float w, float h);

   // will simply pass message up through to the above parent
   void on_message(UIWidget *sender, std::string message) override;
};




