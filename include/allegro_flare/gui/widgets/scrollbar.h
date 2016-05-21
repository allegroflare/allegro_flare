#ifndef __UI_SCROLLBAR_HEADER
#define __UI_SCROLLBAR_HEADER




#include <allegro_flare/gui/widget.h>




class UIScrollBar : public UIWidget
{
protected:

   class UpButton : public UIWidget
   {
   public:
      UpButton(UIWidget *parent, float x, float y, float w, float h);
      void on_click() override;
      void on_draw() override;
   };

   class DownButton : public UIWidget
   {
   public:
      DownButton(UIWidget *parent, float x, float y, float w, float h);
      void on_click() override;
      void on_draw() override;
   };

   class Rail : public UIWidget
   {
   public:
      float current_mouse_y;
      Rail(UIWidget *parent, float x, float y, float w, float h);
      void on_draw() override;
      void on_mouse_move(float x, float y, float dx, float dy) override;
      void on_click() override;
   };

   class Handle : public UIWidget
   {
   private:
      float min_y, max_y;
   public:
      Handle(UIWidget *parent, float x, float y, float w, float h);
      void set_min_max_coordinate_position(float min_val, float max_val);
      void on_drag(float x, float y, float dx, float dy);
      void on_draw();
      float get_position();
      void set_position(float position_in_unit_value);
   };

   Rail *rail;
   Handle *handle;
   UpButton *up_button;
   DownButton *down_button;

public:
   UIScrollBar(UIWidget *parent, float x, float y, float w, float h);

   void step_up();
   void step_down();
   void jump_down();
   void jump_up();
   float get_position();
   void set_position(float position_in_unit_value);

   void on_key_down() override;
   void on_draw() override;
   void on_change() override;
};



#endif

