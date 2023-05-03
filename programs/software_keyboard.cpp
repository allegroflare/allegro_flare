



//#include <allegro_flare/allegro_flare.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Path2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Screens/Base.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>




//using namespace allegro_flare;
//using namespace AllegroFlare;



AllegroFlare::FontBin *fonts;



enum
{
   SIGNAL_NONE = 0,
   SIGNAL_TOGGLE_KEYBOARD_VISIBILITY,
};




class SoftKeyKey
{
private:
   static bool initialized;
   static ALLEGRO_FONT *large_font;
   static ALLEGRO_FONT *small_font;
   static ALLEGRO_COLOR key_color;
   static ALLEGRO_COLOR alt_key_color;
   //static ALLEGRO_SAMPLE *keypress_sound, *keyhover_sound;
   static float key_roundness;

   void initialize()
   {
      if (!fonts) throw std::runtime_error("need fonts");
      if (initialized) return;
      large_font = fonts->auto_get("Inter-Regular.ttf -32"); //, ALLEGRO_FLAGS_EMPTY);
      small_font = fonts->auto_get("Inter-Regular.ttf -18"); //, ALLEGRO_FLAGS_EMPTY);
      //keyhover_sound = al_load_sample("data/samples/click.wav");
      //keypress_sound = al_load_sample("data/samples/keypress_light.wav");
      key_color = AllegroFlare::color::hex("646873");
      alt_key_color = AllegroFlare::color::hex("363d47");
      initialized = true;
   }

public:
   float x, y, w, h;

   AllegroFlare::Path2D *path;
   ALLEGRO_BITMAP *icon;
   bool is_standard_key;
   char c;
   std::string text;
   int allegro_key_code;
   bool bigfont;

   bool mouse_over;

   float pressed_counter;

   SoftKeyKey()
      : x(0)
      , y(0)
      , w(0)
      , h(0)
      , path(NULL)
      , icon(NULL)
      , is_standard_key(true)
      , text("")
      , allegro_key_code(ALLEGRO_KEY_MAX)
      , bigfont(true)
      , mouse_over(false)
      , pressed_counter(0)
   {
      initialize();
   }

   //bool collide(float x, float y)
   //{
      //if (x < this->x) return false;
      //if (y < this->y) return false;
      //if (x >= this->x+this->w) return false;
      //if (y >= this->y+this->h) return false;
      //return true;
   //}

   void set(float x, float y, float w, float h, AllegroFlare::Path2D *path, ALLEGRO_BITMAP *icon, bool is_standard_key, bool bigfont, std::string text, int allegro_key_code)
   {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
      this->path = path;
      this->icon = icon;
      this->is_standard_key = is_standard_key;
      this->text = text;
      this->bigfont = bigfont;
      this->allegro_key_code = allegro_key_code;
   }

   void update_press_fx()
   {
      pressed_counter = std::max<float>(0.0, (pressed_counter -= 1.0/60));
   }

   void trigger()
   {
      //al_play_sample(keypress_sound, 0.6, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      //if (allegro_key_code != ALLEGRO_KEY_MAX) std::cout << allegro_key_code << " ";
      pressed_counter = 1.0;
   }

   void draw()
   {
      ALLEGRO_COLOR key_color_now = is_standard_key ? key_color : alt_key_color;
      if (mouse_over) key_color_now = AllegroFlare::Color::GreenYellow;
      if (pressed_counter > 0) key_color_now = AllegroFlare::color::mix(key_color_now, AllegroFlare::Color::GreenYellow, AllegroFlare::interpolator::tripple_fast_out(pressed_counter));

      //: is_standard_key ? key_color : alt_key_color;
      al_draw_filled_rectangle(x, y, x+w, y+h, key_color_now);
      //al_draw_line(x, y+h-3, x+w, y+h-3, AllegroFlare::color(AllegroFlare::Color::Black, 0.2), 6.0);
      al_draw_line(x, y+2, x+w, y+2, AllegroFlare::color::color(AllegroFlare::Color::White, 0.2), 3.0);
      if (!text.empty())
      {
         if (!mouse_over)
         {
            al_draw_text(
               bigfont ? large_font : small_font
               , AllegroFlare::color::color(AllegroFlare::Color::Black, 0.4)
               , x+w/2
               , y+h/2-al_get_font_line_height(bigfont ? large_font : small_font)/2*1.1+1
               , ALLEGRO_ALIGN_CENTRE
               , text.c_str()
            );
         }
         al_draw_text(
            bigfont ? large_font : small_font
            , mouse_over ? AllegroFlare::Color::Black : AllegroFlare::Color::White
            , x+w/2
            , y+h/2-al_get_font_line_height(bigfont ? large_font : small_font)/2*1.1
            , ALLEGRO_ALIGN_CENTRE
            , text.c_str()
         );
      }
      if (path)
      {
         path->draw_shape(x+w/2, y+h/2, AllegroFlare::Color::White);
      }
      if (icon)
      {
         al_draw_bitmap(icon, x+w/2 - al_get_bitmap_width(icon), y+h/2 - al_get_bitmap_height(icon), 0);
      }
      al_draw_rounded_rectangle(x, y, x+w, y+h, key_roundness, key_roundness, AllegroFlare::Color::Black, 4.0);
   }

   //void on_mouse_enter()
   //{
      ////al_play_sample(keyhover_sound, 0.2, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
   //}

   //void on_mouse_move(float mouse_x, float mouse_y)
   //{
      //bool mouse_now_over = false;
      //if (collide(mouse_x, mouse_y)) mouse_now_over = true;
      //if (mouse_now_over && !mouse_over) on_mouse_enter();
      ////else if (!mouse_now_over && mouse_over) on_mouse_leave();
      //mouse_over = mouse_now_over;
   //}

   //bool on_mouse_down() // << TODO: shouldn't this be void?
   //{
      //if (mouse_over)
      //{
         //trigger();
         //return true;
      //}
      //return false; // ??
   //}
};




bool SoftKeyKey::initialized = false;
ALLEGRO_FONT *SoftKeyKey::large_font = NULL;
ALLEGRO_FONT *SoftKeyKey::small_font = NULL;
ALLEGRO_COLOR SoftKeyKey::key_color = AllegroFlare::Color::Black;
ALLEGRO_COLOR SoftKeyKey::alt_key_color = AllegroFlare::Color::Black;
//ALLEGRO_SAMPLE *SoftKeyKey::keypress_sound = NULL;
//ALLEGRO_SAMPLE *SoftKeyKey::keyhover_sound = NULL;
float SoftKeyKey::key_roundness = 0.0;




class SoftwareKeyboard// : public UIWidget
{
public:
   AllegroFlare::Motion motion_manager;
   //Display *display;
   // 43 keys
   static constexpr size_t KEY_COUNT_MAX = 43;
   SoftKeyKey key[43];
   float x, y;
   float w, h;
   int num_cols;
   int num_rows;
   AllegroFlare::Placement2D place;
   AllegroFlare::vec2d mouse_world, mouse_screen;
   bool visible;
   bool shift_pressed;
   bool initialized;

   SoftwareKeyboard(float x, float y)
      //: UIWidget(parent, "SoftwareKeyboard", new UISurfaceAreaBox(x, y, 850, 250))
      : motion_manager(3)
      , key()
      , x(x)
      , y(y)
      , w(850)
      , h(250)
      , num_cols(12)
      , num_rows(4)
      //  , display(display)
      , mouse_world()
      , mouse_screen()
      , visible(true)
      , shift_pressed(false)
      , initialized(false)
   {
   }


   void initialize()
   {
      place.position.x = x;
      place.position.y = y;
      place.size.x = w;
      place.size.y = h;

      key[0].set(0, 0, 1, 1, NULL, NULL, true, true, "q", ALLEGRO_KEY_Q);
      key[1].set(1, 0, 1, 1, NULL, NULL, true, true, "w", ALLEGRO_KEY_W);
      key[2].set(2, 0, 1, 1, NULL, NULL, true, true, "e", ALLEGRO_KEY_E);
      key[3].set(3, 0, 1, 1, NULL, NULL, true, true, "r", ALLEGRO_KEY_R);
      key[4].set(4, 0, 1, 1, NULL, NULL, true, true, "t", ALLEGRO_KEY_T);
      key[5].set(5, 0, 1, 1, NULL, NULL, true, true, "y", ALLEGRO_KEY_Y);
      key[6].set(6, 0, 1, 1, NULL, NULL, true, true, "u", ALLEGRO_KEY_U);
      key[7].set(7, 0, 1, 1, NULL, NULL, true, true, "i", ALLEGRO_KEY_I);
      key[8].set(8, 0, 1, 1, NULL, NULL, true, true, "o", ALLEGRO_KEY_O);
      key[9].set(9, 0, 1, 1, NULL, NULL, true, true, "p", ALLEGRO_KEY_P);
      key[10].set(10, 0, 2, 1, NULL, NULL, true, false, "Backspace", ALLEGRO_KEY_BACKSPACE);

      key[11].set(0, 1, 1, 1, NULL, NULL, true, true, "a", ALLEGRO_KEY_A);
      key[12].set(1, 1, 1, 1, NULL, NULL, true, true, "s", ALLEGRO_KEY_S);
      key[13].set(2, 1, 1, 1, NULL, NULL, true, true, "d", ALLEGRO_KEY_D);
      key[14].set(3, 1, 1, 1, NULL, NULL, true, true, "f", ALLEGRO_KEY_F);
      key[15].set(4, 1, 1, 1, NULL, NULL, true, true, "g", ALLEGRO_KEY_G);
      key[16].set(5, 1, 1, 1, NULL, NULL, true, true, "h", ALLEGRO_KEY_H);
      key[17].set(6, 1, 1, 1, NULL, NULL, true, true, "j", ALLEGRO_KEY_J);
      key[18].set(7, 1, 1, 1, NULL, NULL, true, true, "k", ALLEGRO_KEY_K);
      key[19].set(8, 1, 1, 1, NULL, NULL, true, true, "l", ALLEGRO_KEY_L);
      key[20].set(9, 1, 1, 1, NULL, NULL, true, true, "\"", ALLEGRO_KEY_A);
      key[21].set(10, 1, 2, 1, NULL, NULL, true, false, "Enter", ALLEGRO_KEY_ENTER);

      for (int i=11; i<=21; i++)
         key[i].x += 0.25;
      key[21].w -= 0.25;

      key[22].set(0, 2, 1, 1, NULL, NULL, false, true, "^", ALLEGRO_KEY_LSHIFT);
      key[23].set(1, 2, 1, 1, NULL, NULL, true, true, "z", ALLEGRO_KEY_Z);
      key[24].set(2, 2, 1, 1, NULL, NULL, true, true, "x", ALLEGRO_KEY_X);
      key[25].set(3, 2, 1, 1, NULL, NULL, true, true, "c", ALLEGRO_KEY_C);
      key[26].set(4, 2, 1, 1, NULL, NULL, true, true, "v", ALLEGRO_KEY_V);
      key[27].set(5, 2, 1, 1, NULL, NULL, true, true, "b", ALLEGRO_KEY_B);
      key[28].set(6, 2, 1, 1, NULL, NULL, true, true, "n", ALLEGRO_KEY_N);
      key[29].set(7, 2, 1, 1, NULL, NULL, true, true, "m", ALLEGRO_KEY_M);
      key[30].set(8, 2, 1, 1, NULL, NULL, true, true, ",", ALLEGRO_KEY_COMMA);
      key[31].set(9, 2, 1, 1, NULL, NULL, true, true, ".", ALLEGRO_KEY_FULLSTOP);
      key[32].set(10, 2, 1, 1, NULL, NULL, true, true, "?", ALLEGRO_KEY_SLASH);
      key[33].set(11, 2, 1, 1, NULL, NULL, false, true, "^", ALLEGRO_KEY_RSHIFT);

      key[34].set(0, 3, 1, 1, NULL, NULL, false, false, "Ctrl", ALLEGRO_KEY_Z);
      key[35].set(1, 3, 1, 1, NULL, NULL, false, false, "&123", ALLEGRO_KEY_X);
      key[36].set(2, 3, 1, 1, NULL, NULL, false, false, "wtf", ALLEGRO_KEY_C);
      key[37].set(3, 3, 1, 1, NULL, NULL, true, true, "/", ALLEGRO_KEY_SLASH);
      key[38].set(4, 3, 4, 1, NULL, NULL, true, true, "", ALLEGRO_KEY_SPACE);
      key[39].set(8, 3, 1, 1, NULL, NULL, true, false, ".com", ALLEGRO_KEY_A);
      key[40].set(9, 3, 1, 1, NULL, NULL, false, true, "<<", ALLEGRO_KEY_LEFT);
      key[41].set(10, 3, 1, 1, NULL, NULL, false, true, ">>", ALLEGRO_KEY_RIGHT);
      key[42].set(11, 3, 1, 1, NULL, NULL, false, true, "[]", ALLEGRO_KEY_RIGHT);

      float std_button_width = w/num_cols;
      float std_button_height = h/num_rows;
      for (unsigned i=0; i<43; i++)
      {
         key[i].x *= std_button_width;
         key[i].y *= std_button_height;
         key[i].w *= std_button_width;
         key[i].h *= std_button_height;
         //key[i].x -= w/2;
         //key[i].y -= h;
      }

      initialized = true;
   }


   void on_draw() //override
   {
      motion_manager.update(al_get_time());

      al_draw_filled_rectangle(0, 0, w, h, AllegroFlare::Color::Black);
      al_draw_rounded_rectangle(0, 0, w, h, 4, 4, AllegroFlare::Color::Black, 4.0);

      for (unsigned i=0; i<43; i++)
      {
         key[i].update_press_fx();
         key[i].draw();
      }
   }


   void toggle_visibility()
   {
      /*
      motion_manager.clear_animations_on(&placement.position.y);
      motion_manager.clear_animations_on(&placement.scale.x);
      motion_manager.clear_animations_on(&placement.scale.y); //TODO should this be .y?
      //motion_manager.clear_animations_on(&camera.rotation);
      float time_now = al_get_time();
      if (visible)
      {
         // hide
         motion_manager.animate(&placement.position.y, placement.position.y, -display->height()/3*2.2, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         motion_manager.animate(&placement.scale.x, placement.scale.x, 0.7, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         motion_manager.animate(&placement.scale.y, placement.scale.y, 0.7, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         for (int i=0; i<43; i++) key[i].mouse_over = false;
      }
      else
      {
         // show
         motion_manager.animate(&placement.position.y, placement.position.y, -display->height()/2+h, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         motion_manager.animate(&placement.scale.x, placement.scale.x, 0.9, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         motion_manager.animate(&placement.scale.y, placement.scale.y, 0.9, time_now, time_now+0.4, interpolator::quadruple_fast_in, NULL, NULL);
         for (int i=0; i<43; i++) key[i].mouse_over = false;
      }
      */
      visible = !visible;
   }


   void toggle_shift()
   {
      if (!visible) return;

      if (shift_pressed)
         for (int i=0; i<43; i++)
            if (key[i].text.size()==1 && key[i].text[0]>='A' && key[i].text[0]<='Z') key[i].text[0] = key[i].text[0]+32;
      if (!shift_pressed)
         for (int i=0; i<43; i++)
            if (key[i].text.size()==1 && key[i].text[0]>='a' && key[i].text[0]<='z') key[i].text[0] = key[i].text[0]-32;
      shift_pressed = !shift_pressed;
   }


   void on_key_char(int allegro_keycode) //override
   {
      //TODO: int allegro_key = Framework::current_event->keyboard.keycode;
      for (unsigned i=0; i<43; i++)
         if (key[i].allegro_key_code == allegro_keycode) key[i].trigger();
   }


   void on_key_down(int keycode) //override
   {
      if (!visible) return;

      //TODO: int keycode = Framework::current_event->keyboard.keycode;
      if (keycode == ALLEGRO_KEY_RSHIFT || keycode == ALLEGRO_KEY_LSHIFT)
         toggle_shift();
   }


   //void on_mouse_move(float x, float y, float dx, float dy) //override
   //{
      //if (!visible) return;

      //mouse_screen = AllegroFlare::vec2d(x, y);
      //mouse_world = mouse_screen;
      //place.transform_coordinates(&mouse_world.x, &mouse_world.y);

      //for (unsigned i=0; i<43; i++)
         //key[i].on_mouse_move(mouse_world.x, mouse_world.y);
   //}


   //void on_mouse_down() //override
   //{
      //if (!visible) return;

      //for (unsigned i=0; i<43; i++)
      //{
         //if (key[i].on_mouse_down())
         //{
            //// fire a keypress
         //}
      //}
   //}
};




class SoftKeyboardExample : public AllegroFlare::Screens::Base
{
private:
   SoftwareKeyboard *keyboard;
   bool initialized;

public:
   SoftKeyboardExample()
      : AllegroFlare::Screens::Base("SoftKeyboardExample")
      , keyboard(NULL)
      , initialized(false)
   {
   }

   void initialize()
   {
      keyboard = new SoftwareKeyboard(1920/2, 1080/2);
      keyboard->initialize();
      initialized = true;
   }

   void primary_timer_func() override
   {
      keyboard->on_draw();
   }
};




int main(int argc, char *argv[])
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_font_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");
   fonts = &framework.get_font_bin_ref();

   //Display *display = Framework::create_display(1100, 600);
   SoftKeyboardExample *example = new SoftKeyboardExample;
   example->initialize();

   framework.register_screen("example", example);
   framework.activate_screen("example");


   framework.run_loop();

   return 0;
}




