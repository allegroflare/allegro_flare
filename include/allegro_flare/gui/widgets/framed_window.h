#ifndef __UI_FRAMED_WINDOW_HEADER
#define __UI_FRAMED_WINDOW_HEADER




#include <allegro_flare/gui/widget.h>
#include <allegro_flare/gui/widgets/button.h>
#include <allegro_flare/gui/widgets/draggable_region.h>




class UIFramedWindow : public UIWidget
{
protected:
   UIDraggableRegion *titlebar_dragger;
   float titlebar_height;
   float frame_thickness;
   std::string window_title;
   UIButton *close_button;

   void draw_window_frame_around(float x1, float y1, float x2, float y2);

public:
   UIFramedWindow(UIWidget *parent, float x, float y, float w, float h);

   void set_title(std::string title);

   void on_message(UIWidget *sender, std::string message) override;
   void on_draw() override;
   void on_focus() override;
};




#endif
