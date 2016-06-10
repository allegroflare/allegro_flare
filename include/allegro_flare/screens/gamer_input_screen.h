#ifndef __AF_GAMER_INPUT_SCREEN_HEADER
#define __AF_GAMER_INPUT_SCREEN_HEADER




#include <allegro_flare/allegro_flare.h>




#define ALLEGRO_EVENT_GAMER_BUTTON_UP ALLEGRO_GET_EVENT_TYPE('N','P','T','U')
#define ALLEGRO_EVENT_GAMER_BUTTON_DOWN ALLEGRO_GET_EVENT_TYPE('N','P','T','D')




enum button_t
{
   GAMER_BUTTON_UNDEF = 0,
   GAMER_BUTTON_UP,
   GAMER_BUTTON_DOWN,
   GAMER_BUTTON_LEFT,
   GAMER_BUTTON_RIGHT,
   GAMER_BUTTON_START,
   GAMER_BUTTON_BACK,
   GAMER_BUTTON_A,
   GAMER_BUTTON_B,
   GAMER_BUTTON_C,
   GAMER_BUTTON_SIZE_MAX,
};




class GamerInputScreen : public Screen
{
private:
   ALLEGRO_EVENT_SOURCE input_event_source;
   bool pressed[GAMER_BUTTON_SIZE_MAX] = {0};

public:

   bool show_graphic = true;

   int button_up_joystick_buttonmap = 0;
   int button_down_joystick_buttonmap = 0;
   int button_left_joystick_buttonmap = 0;
   int button_right_joystick_buttonmap = 0;
   int button_start_joystick_buttonmap = 0;
   int button_back_joystick_buttonmap = 0;
   int button_a_joystick_buttonmap = 0;
   int button_b_joystick_buttonmap = 0;
   int button_c_joystick_buttonmap = 0;

   int button_up_keyboard_keymap = 0;
   int button_down_keyboard_keymap = 0;
   int button_left_keyboard_keymap = 0;
   int button_right_keyboard_keymap = 0;
   int button_start_keyboard_keymap = 0;
   int button_back_keyboard_keymap = 0;
   int button_a_keyboard_keymap = 0;
   int button_b_keyboard_keymap = 0;
   int button_c_keyboard_keymap = 0;

   /// /// /// /// ///

   GamerInputScreen(Display *display);
   ~GamerInputScreen();

   /// /// /// /// ///

   void primary_timer_func() override;
   void key_down_func() override;
   void key_up_func() override;
   void joy_axis_func() override;
   void joy_button_down_func() override;
   void joy_button_up_func() override;
   void joy_config_func() override;

   /// /// /// /// ///

   std::string get_button_name(button_t button);
   bool is_pressed(button_t button);
   void emit_gamer_button_up(button_t button);
   void emit_gamer_button_down(button_t button);

   void setup_default_keyboard_mapping_for_ARROW_KEYS();
   void setup_default_joystick_mapping_for_LOGITECH_RUMBLEPAD_2();
   void setup_default_joystick_mapping_for_XBOX_360_CONTROLLER();
   static void draw_gamer_input_state(bool button[GAMER_BUTTON_SIZE_MAX], float opacity=0.5, float x=0, float y=0, float align_x=0.0, float align_y=0.0, float scale_x=0.5, float scale_y=0.5);
};




#endif
