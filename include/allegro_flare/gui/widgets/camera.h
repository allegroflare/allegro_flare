#pragma once




#include <allegro_flare/gui/widget.h>




class UICamera : public UIWidget
{
public:
   UICamera(UIWidget *parent, float x, float y, float w, float h);

   void on_message(UIWidget *sender, std::string message) override;
};




