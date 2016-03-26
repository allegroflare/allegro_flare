#ifndef FGUI_DRAGGABLE_REGION_HEADER
#define FGUI_DRAGGABLE_REGION_HEADER




#include <allegro_flare/gui/widget.h>




class FGUIDraggableRegion : public FGUIWidget
{
protected:
   ALLEGRO_COLOR background_color;

public:
   FGUIDraggableRegion(FGUIWidget *parent, float x, float y, float w, float h);

   void set_color(ALLEGRO_COLOR col);

   void on_draw() override;
   void on_drag(float x, float y, float dx, float dy) override;
};





#endif
