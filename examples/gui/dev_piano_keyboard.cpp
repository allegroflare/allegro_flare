#ifndef __UI_PIANO_KEYBOAD_HEADER
#define __AF_PIANO_KEYBOAD_HEADER



#include <allegro_flare/allegro_flare.h>
//#include <allegro_flare/midi_win.h> // this was stripped out, but will need to be implemented in a comprehensive way




class PianoKeyboardKey
{
public:
   float x, y, w, h;
   bool mouse_over;
   int midi_key_num;
   bool triggered;
   bool black_key;

   PianoKeyboardKey();

   bool collide(float mouse_x, float mouse_y);

   void set(float x, float y, float w, float h, int midi_key_num, bool black_key);

   void on_mouse_leave();
   void on_mouse_enter();
   void on_mouse_move(float mouse_x, float mouse_y);
   void on_mouse_down();
   void on_mouse_up();

   void switch_out();

   void draw();

   void trigger();
   void release();
};








class UIPianoKeyboard : public UIWidget
{
public:
   vec2d mouse_screen, mouse_world;
   #define NUM_KEYS 48

   PianoKeyboardKey keys[NUM_KEYS];
   float w, h;

   UIPianoKeyboard(UIWidget *parent, float x, float y);

   bool is_black_key(int num, std::vector<int> &set);

   void set_keys_to_diatonic();
   void set_keys_to_octatonic1();
   void set_keys_to_pentatonic();
   void set_keys_to_whole_tone();
   void set_keys_to_scale(int *set_array, int size);
   void set_keys_to_scale(std::vector<int> &set);

   void on_draw() override;
   void on_mouse_move(float x, float y, float dx, float dy) override;
   void on_mouse_down() override;
   void on_mouse_up() override;
};







#endif















//#include <allegro_flare_screens/piano_keyboard.h>




PianoKeyboardKey::PianoKeyboardKey()
   : mouse_over(false)
   , x(0)
   , y(0)
   , w(0)
   , h(0)
   , midi_key_num(0)
   , triggered(false)
   , black_key(false)
{}

void PianoKeyboardKey::set(float x, float y, float w, float h, int midi_key_num, bool black_key)
{
   this->x = x;
   this->y = y;
   this->w = w;
   this->h = h;
   this->midi_key_num = midi_key_num;
   this->black_key = black_key;
}

bool PianoKeyboardKey::collide(float mouse_x, float mouse_y)
{
   if (mouse_x < x) return false;
   if (mouse_y < y) return false;
   if (mouse_x >= x+w) return false;
   if (mouse_y >= y+h) return false;
   return true;
}

void PianoKeyboardKey::draw()
{
   al_draw_filled_rectangle(x, y, x+w, y+h, mouse_over ? color::deeppink : black_key ? color::hex("171720") : color::hex("f2f2f0"));
   al_draw_rounded_rectangle(x, y, x+w, y+h, black_key ? 0.5 : 2, black_key ? 0.5 : 2, color::black, 1.5);
   if (black_key)
   {
      al_draw_filled_rounded_rectangle(x+2, y, x+w-2, y+h-7, 2, 2, color::color(color::white, 0.1));
      al_draw_line(x+2, y+h-7, x+w-2, y+h-7, color::color(color::white, 0.25), 1.0);
   }
   if (midi_key_num==0) al_draw_filled_circle(x+w/2, y+h, w/5, color::dodgerblue);
   else if (midi_key_num%12 == 0) al_draw_circle(x+w/2, y+h, w/5, color::dodgerblue, 1.0);
}

void PianoKeyboardKey::on_mouse_leave()
{
   if (triggered) release();
}

void PianoKeyboardKey::on_mouse_enter()
{
}

void PianoKeyboardKey::switch_out()
{
   if (mouse_over) on_mouse_leave();
   mouse_over = false;
}

void PianoKeyboardKey::on_mouse_move(float mouse_x, float mouse_y)
{
   bool collide_now = collide(mouse_x, mouse_y);
   if (collide_now && !mouse_over) on_mouse_enter();
   if (!collide_now && mouse_over) on_mouse_leave();
   mouse_over = collide_now;
}

void PianoKeyboardKey::trigger()
{
   //midi_note_on(0, midi_key_num+60, 64);
   std::cout << "note triggered!" << std::endl;
   triggered = true;
}

void PianoKeyboardKey::release()
{
   //midi_note_off(0, midi_key_num+60);
   std::cout << "note released!" << std::endl;
   triggered = false;
}

void PianoKeyboardKey::on_mouse_down()
{
   if (mouse_over) trigger();
}

void PianoKeyboardKey::on_mouse_up()
{
   if (mouse_over) release();
}














UIPianoKeyboard::UIPianoKeyboard(UIWidget *parent, float x, float y)
   : UIWidget(parent, new UISurfaceAreaBox(x, y, 500, 100))
{
   set_keys_to_pentatonic();
   //init_midi();
   //if (!midi_out_device.empty()) { open_midi_device(midi_out_device[0]); }

   //camera.x = w/2 + 0.5;
   //camera.scale_x = 1.25;
   //camera.scale_y = 1.25;
   //camera.rotation = 0.1;
}

bool UIPianoKeyboard::is_black_key(int num, std::vector<int> &set)
{
   for (std::vector<int>::iterator it=set.begin(); it!=set.end(); it++)
      if ((*it) == num) return false;
   return true;
}

void UIPianoKeyboard::set_keys_to_diatonic()
{
   int myints[] = {0, 2, 4, 5, 7, 9, 11};
   std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
   set_keys_to_scale(set);
}

void UIPianoKeyboard::set_keys_to_whole_tone()
{
   int myints[] = {0, 2, 4, 6, 8, 10};
   std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
   set_keys_to_scale(set);
}

void UIPianoKeyboard::set_keys_to_octatonic1()
{
   int myints[] = {0, 1, 3, 4, 6, 7, 9, 10};
   std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
   set_keys_to_scale(set);
}

void UIPianoKeyboard::set_keys_to_pentatonic()
{
   int myints[] = {0, 2, 4, 7, 9 };
   std::vector<int> set(myints, myints + sizeof(myints) / sizeof(int));
   set_keys_to_scale(set);
}

void UIPianoKeyboard::set_keys_to_scale(int *set_array, int size)
{
   std::vector<int> set(set_array, set_array + size / sizeof(int));
   set_keys_to_scale(set);
}

void UIPianoKeyboard::set_keys_to_scale(std::vector<int> &set)
{
   float key_width = 20;
   float key_height = 100;
   float keyboard_padding[4] = { 4, 4, 4, 4 };

   // create keys here:
   for (int i=0; i<NUM_KEYS; i++)
      keys[i].set(i, 0, 1, 1, i-24, false);

   float x_cursor = 0;

   for (int i=0; i<NUM_KEYS; i++)
   {
      int val = i%12;
      if (is_black_key(val, set)) //val==1 || val==3 || val==6 || val==7 || val==8 || val==10)
         keys[i].black_key = true;
      else keys[i].black_key = false;

      if (keys[i].black_key)
      {
         keys[i].w = 0.5;
         keys[i].h = 0.6;
      }
      else
      {
         keys[i].w = 1.0;
         keys[i].h = 1.0;
      }

      if (i==0)
      {
         // don't move the cursor forward
      }
      else
      {
         bool previous_key_white = !keys[i-1].black_key;
         bool this_key_white = !keys[i].black_key;

         if (previous_key_white && this_key_white) x_cursor += 1.0;
         else if (previous_key_white && !this_key_white) x_cursor += 0.75;
         else if (!previous_key_white && !this_key_white) x_cursor += 0.5;
         else if (!previous_key_white && this_key_white) x_cursor += 0.25;
      }
      keys[i].x = x_cursor;

      if (i==(NUM_KEYS-1))
         x_cursor += keys[i].black_key ? 0.5 : 1.0;



      keys[i].x *= key_width;
      keys[i].y *= key_height;
      keys[i].w *= key_width;
      keys[i].h *= key_height;

      keys[i].x += keyboard_padding[3];
      keys[i].y += keyboard_padding[1];
   }

   w = x_cursor * key_width + keyboard_padding[3] + keyboard_padding[1];
   h = key_height + keyboard_padding[0] + keyboard_padding[2];

   place.size.x = w;
   place.size.y = h;
}

void UIPianoKeyboard::on_draw()
{
   al_draw_filled_rectangle(0, 0, w, h, color::hex("876833")); // dark tan
   //al_draw_filled_rectangle(0, 0, w, h, color::hex("172b43")); // dark blue

   for (int i=0; i<NUM_KEYS; i++)
      if (!keys[i].black_key) keys[i].draw();

   al_draw_filled_rectangle(0, 0, w, 2, color::hex("800818")); // red felt

   for (int i=0; i<NUM_KEYS; i++)
      if (keys[i].black_key) keys[i].draw();
}

void UIPianoKeyboard::on_mouse_move(float x, float y, float dx, float dy)
{
   place.transform_coordinates(&x, &y);

   bool collided = false;
   for (int i=0; i<NUM_KEYS; i++)
   {
      if (keys[i].black_key)
      {
         if (collided) keys[i].switch_out();
         else
         {
            keys[i].on_mouse_move(x, y);
            if (keys[i].mouse_over) collided = true;
         }
      }
   }
   for (int i=0; i<NUM_KEYS; i++)
   {
      if (!keys[i].black_key)
      {
         if (collided) keys[i].switch_out();
         else
         {
            keys[i].on_mouse_move(x, y);
            if (keys[i].mouse_over) collided = true;
         }
      }
   }
}

void UIPianoKeyboard::on_mouse_down()
{
   for (int i=0; i<NUM_KEYS; i++)
      keys[i].on_mouse_down();
}

void UIPianoKeyboard::on_mouse_up()
{
   for (int i=0; i<NUM_KEYS; i++)
      keys[i].on_mouse_up();
}


























class PianoKeyboardExampleProject : public UIScreen
{
public:
   Display *display;
   ALLEGRO_FONT *font;
   PianoKeyboardExampleProject(Display *display)
      : UIScreen(display)
      , font(al_load_font("data/fonts/DroidSans.ttf", -20, ALLEGRO_FLAGS_EMPTY))
   {


      std::vector<int> major7;  major7.push_back(0); major7.push_back(4); major7.push_back(7); major7.push_back(11);


      UIPianoKeyboard *piano_keyboard1 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard1->place.position.x = -200 + display->width()/2;
      piano_keyboard1->place.position.y = display->height()/2;
      piano_keyboard1->place.scale.x = 0.7;
      piano_keyboard1->place.scale.y = 0.7;

      UIPianoKeyboard *piano_keyboard5 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard5->set_keys_to_scale(major7);
      piano_keyboard5->place.position.y = 300 + display->height()/2;
      piano_keyboard5->place.position.x = -200 + display->width()/2;
      piano_keyboard5->place.scale.x = 0.7;
      piano_keyboard5->place.scale.y = 0.7;

      UIPianoKeyboard *piano_keyboard4 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard4->set_keys_to_whole_tone();
      piano_keyboard4->place.position.y = 150 + display->height()/2;
      piano_keyboard4->place.position.x = -200 + display->width()/2;
      piano_keyboard4->place.scale.x = 0.7;
      piano_keyboard4->place.scale.y = 0.7;

      UIPianoKeyboard *piano_keyboard2 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard2->set_keys_to_diatonic();
      piano_keyboard2->place.position.y = -150 + display->height()/2;
      piano_keyboard2->place.position.x = -200 + display->width()/2;
      piano_keyboard2->place.scale.x = 0.7;
      piano_keyboard2->place.scale.y = 0.7;

      UIPianoKeyboard *piano_keyboard3 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard3->set_keys_to_octatonic1();
      piano_keyboard3->place.position.y = -300 + display->height()/2;
      piano_keyboard3->place.position.x = -200 + display->width()/2;
      piano_keyboard3->place.scale.x = 0.7;
      piano_keyboard3->place.scale.y = 0.7;

      std::vector<int> this_set; this_set.push_back(0); this_set.push_back(4); this_set.push_back(6);
         this_set.push_back(10); this_set.push_back(11);
      UIPianoKeyboard *piano_keyboard6 = new UIPianoKeyboard(this, 0, 0);
      piano_keyboard6->set_keys_to_scale(this_set);
      piano_keyboard6->place.position.x = 250 + display->width()/2;
      piano_keyboard6->place.position.y = 200 + display->height()/2;
      piano_keyboard6->place.rotation = 0.2;
      piano_keyboard6->place.scale.x = 0.7;
      piano_keyboard6->place.scale.y = 0.7;
      //piano_keyboard5->camera.x -= 200;


   }
};






int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(1280, 800, false);

   PianoKeyboardExampleProject *project = new PianoKeyboardExampleProject(display);

   Framework::run_loop();

   return 0;
}




