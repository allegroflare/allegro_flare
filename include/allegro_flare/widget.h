#ifndef __UI_WIDGET_HEADER
#define __UI_WIDGET_HEADER




#include <allegro5/allegro.h>
#include <allegro_flare/surface_area_base.h>
#include <allegro_flare/element_id.h>
#include <allegro_flare/bit_flags.h>
#include <AllegroFlare/Color.hpp>


namespace AllegroFlare
{
   class Motion;
   class FontBin;
   class SampleBin;
}


namespace allegro_flare
{
   class UIScreen;




   /*
   enum WIDGET_FLAGS
   {
      // states
      UI_FLAG_MOUSE_OVER = 0x01,
      UI_FLAG_MOUSE_DOWN_ON_OVER = 0x02,
      UI_FLAG_FOCUSED = 0x04,
      UI_FLAG_CAN_BE_DELETED = 0x08,
      UI_FLAG_ANIMATING_DELETE = 0x10,
      UI_FLAG_SOMETHING_ELSE = 0x20,

      // behaviors
      UI_FLAG_BRING_TO_FRONT_ON_FOCUS = 0x40
   };
   */




#define UI_ATTR__UI_WIDGET_TYPE "UI_WIDGET_TYPE"




   class UIWidget : public ElementID
   {
   private:
      static int num_active_widgets; // holds the number of widgets that have been created but not destroyed
      static int widget_count; // a counter that is incremented each time a new widget is created

   protected:
      friend class UIScreen;
      friend class UIScrollArea;

      UISurfaceAreaBase *surface_area;

      // TODO these might need to be implemented in a flag system
      bool mouse_over;
      bool mouse_down_on_over;
      bool focused;
      bool dragging;
      bool no_focus; // possibly implemented in a flag system instead
      bool mouse_is_blocked;
      float local_mouse_x, local_mouse_y;
      bool disabled;
      // maybe will need to add:
      // bool skip_on_tab_focus (or no_focus);
      // bool no_jumpout_on_tab;

      // widget *developer* functions:
      virtual void draw_func();
      virtual void primary_timer_func();
      virtual void mouse_axes_func(float x, float y, float dx, float dy);
      virtual void mouse_down_func();
      virtual void mouse_up_func();
      virtual void key_down_func();
      virtual void key_up_func();
      virtual void key_char_func();
      virtual void joy_down_func();
      virtual void joy_up_func();
      virtual void joy_axis_func();

   public:
      //BitFlags<int16_t> flags;    // << this should be added eventually
      bool delete_me;
      placement2d &place;

      UIWidget(UIWidget *parent, std::string widget_typename, UISurfaceAreaBase *surface_area);
      virtual ~UIWidget();

      // ordering
      void bring_to_front();
      void send_message_to_parent(std::string message);
      void send_message_to_parent(std::string message, UIWidget *sender);

      // retrieval
      bool is_mouse_over();
      bool is_focused();
      bool is_disabled();
      void set_as_focused();
      void set_as_unfocused();
      void set_as_enabled();
      void set_as_disabled();

      //
      // widget behavior functions
      //

      // state
      virtual void on_change();
      virtual void on_message(UIWidget *sender, std::string message);
      virtual void on_focus();
      virtual void on_blur();

      // mouse
      virtual void on_mouse_enter();
      virtual void on_mouse_leave();
      virtual void on_mouse_move(float x, float y, float dx, float dy);
      virtual void on_mouse_down();
      virtual void on_mouse_up();
      virtual void on_mouse_wheel();
      virtual void on_click();
      virtual void on_drag(float x, float y, float dx, float dy);
      virtual void on_drop();

      // keyboard
      virtual void on_key_down();
      virtual void on_key_up();
      virtual void on_key_char();

      // joystick
      virtual void on_joy_down();
      virtual void on_joy_up();
      virtual void on_joy_axis();

      // other
      virtual void on_timer();
      virtual void on_draw();

      // static functions
      static int get_num_created_widgets();
      static int get_num_active_widgets();
   };
}



#endif
