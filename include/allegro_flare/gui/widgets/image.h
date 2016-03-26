#ifndef __AF_IMAGE_HEADER
#define __AF_IMAGE_HEADER




#include <allegro_flare/gui/widget.h>




class FGUIImage : public FGUIWidget
{
protected:
   ALLEGRO_COLOR color;
   ALLEGRO_BITMAP *bitmap;

public:
   FGUIImage(FGUIWidget *parent, float x, float y, ALLEGRO_BITMAP *bitmap);

   void set_bitmap(ALLEGRO_BITMAP *bitmap);
   void set_color(ALLEGRO_COLOR color);

   void on_draw() override;
};




#endif
