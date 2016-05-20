


//
// This is a copy of an old clock program.  It's a really nice looking, so I dumped it here to be
// developed into an example program.  It used an old framework, but that functionality is mostly
// self-explanitory and can be easily replaced.
//
// There's also a clock_overlay.png image that overlays on top of the clock raster drawing.
//
// Have fun! :)
//


#include <allegro_flare/allegro_flare.h>
#include <time.h>


float max_clock_radius = 80;
float clock_radius = max_clock_radius*0.9;
float clock_opacity = 0.0;



inline float inv(float val) { return (1.0-val)*-1; }
inline float range(float val, float min, float max) { return val*(max-min)+min; }



void draw_clock(float x, float y, float radius=100, float opacity=1.0)
{
   if (opacity == 0.0) return;

   float scale = radius/100.0;
   float offset_x = 0;
   float offset_y = 0;
   time_t rawtime;
   struct tm *timeinfo;

   time(&rawtime);
   timeinfo = localtime(&rawtime);


   // draw clock face

   al_draw_filled_circle(x, y, radius*1.04, color::name("white", opacity));

   al_draw_circle(x, y, radius*1.04, color::name("black", opacity), scale);
   for (int i=0; i<60; i++)
   {
      offset_x = cos(i/60.0*FULL_ROTATION)*radius*((opacity*0.3)+0.7);
      offset_y = sin(i/60.0*FULL_ROTATION)*radius*((opacity*0.3)+0.7);

      if (i%5 == 0) al_draw_filled_circle(x+offset_x, y+offset_y, scale*2, color::name("black", opacity*opacity));
      else al_draw_filled_circle(x+offset_x, y+offset_y, scale, color::name("black", opacity*opacity));
   }

   // draw date

   //al_draw_text(get_font("Lacuna.ttf", -18*radius/75), al_color_name("lightgray"), x, y-radius*0.3, ALLEGRO_ALIGN_CENTRE, "Monday");
   //al_draw_text(get_font("Lacuna.ttf", -18*radius/75), al_color_name("lightgray"), x, y, ALLEGRO_ALIGN_CENTRE, "May 26");
   //al_draw_text(get_font("Lacuna.ttf", -18*radius/75), al_color_name("lightgray"), x, y+radius*0.3, ALLEGRO_ALIGN_CENTRE, "2011");

   // draw hands

   float num_sec = timeinfo->tm_sec;
   offset_x = cos(num_sec/60.0*FULL_ROTATION-FULL_ROTATION/4)*radius;
   offset_y = sin(num_sec/60.0*FULL_ROTATION-FULL_ROTATION/4)*radius;
   al_draw_line(x, y, x+offset_x, y+offset_y, color::name("black", opacity), scale*1.0);

   float num_minutes = timeinfo->tm_min + num_sec/60.0;
   offset_x = cos(num_minutes/60.0*FULL_ROTATION-FULL_ROTATION/4)*radius*0.85;
   offset_y = sin(num_minutes/60.0*FULL_ROTATION-FULL_ROTATION/4)*radius*0.85;
   al_draw_line(x, y, x+offset_x, y+offset_y, color::name("black", opacity), scale*3.0);
   al_draw_filled_circle(x+offset_x, y+offset_y, scale*1.5, color::name("black", opacity));

   float num_hrs = timeinfo->tm_hour/2 + num_minutes/60.0;
   offset_x = cos(num_hrs/12.0*FULL_ROTATION-FULL_ROTATION/4)*radius*0.6;
   offset_y = sin(num_hrs/12.0*FULL_ROTATION-FULL_ROTATION/4)*radius*0.6;
   al_draw_line(x, y, x+offset_x, y+offset_y, color::name("black", opacity), scale*3.0);
   al_draw_filled_circle(x+offset_x, y+offset_y, scale*1.5, color::name("black", opacity));

   al_draw_filled_circle(x, y, scale*1.5, color::name("black", opacity));

   if (true)
   {
      ALLEGRO_BITMAP *clock_overlay = Framework::bitmap("clock_overlay.png");
      float clock_overlay_scale = scale/2;
      al_draw_tinted_scaled_bitmap(clock_overlay, color::name("white", opacity),
         0, 0, al_get_bitmap_width(clock_overlay), al_get_bitmap_height(clock_overlay),
         x-al_get_bitmap_width(clock_overlay)*0.5*clock_overlay_scale, y-al_get_bitmap_height(clock_overlay)*0.5*clock_overlay_scale,
         al_get_bitmap_width(clock_overlay)*clock_overlay_scale, al_get_bitmap_height(clock_overlay)*clock_overlay_scale, ALLEGRO_FLAGS_EMPTY);
   }

   // border outline
   al_draw_circle(x, y, radius*1.09 + inv(opacity)*60, color::name("darkblue", opacity*0.2), radius/100.0*3);
   al_draw_circle(x, y, radius*1.235 + inv(opacity)*30, color::name("darkblue", opacity*0.1), radius/100.0*2);
}



void hide_clock(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
   Framework::motion().cmove_to(&clock_opacity, 0.0, 0.6);
   Framework::motion().cmove_to(&clock_radius, max_clock_radius*0.9, 0.6);
   if (clock_opacity == 1.0) al_play_sample(Framework::sample("clock_hide.wav"), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}



void show_clock(void *obj, ALLEGRO_MOUSE_EVENT *ev, void *user)
{
   Framework::motion().cmove_to(&clock_opacity, 1.0, 0.3, interpolator::slowInOut);
   Framework::motion().cmove_to(&clock_radius, max_clock_radius, 0.3, interpolator::slowInOut);
   if (clock_opacity == 0.0) al_play_sample(Framework::sample("clock_show.wav"), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}



/*
void draw_button(void *obj, void *user)
{
   UIButton *b = static_cast<UIButton *>(obj);
   float off = b->pix_r;

   ALLEGRO_COLOR bg_color = color_hex("606060");
   ALLEGRO_COLOR text_color = color_hex("efefef");
   ALLEGRO_COLOR border_color = color_hex("404040");
   ALLEGRO_COLOR hilight_color = color_hex("707070");

   al_draw_filled_rounded_rectangle(b->x+off, b->y+off, b->x+b->w-off, b->y+b->h-off, b->roundness, b->roundness, bg_color);
   al_draw_rounded_rectangle(b->x+off, b->y+off, b->x+b->w-off, b->y+b->h-off, b->roundness, b->roundness, border_color, 1.0);
   //al_draw_rounded_rectangle(b->x+off+1, b->y+off+1, b->x+b->w-off-1, b->y+b->h-off-1, b->roundness, b->roundness, b->inner_border_color, 1.0);
   al_draw_filled_rectangle(b->x+3+off, b->y+3+off, b->x+b->w-3-off, b->y+b->h/2-off, hilight_color);

   if (b->font) al_draw_text(b->font, text_color,
      b->x+b->w/2+b->label_displacement_x, b->y+b->h/2-al_get_font_ascent(b->font)/2+b->label_displacement_y-1,
      ALLEGRO_ALIGN_CENTRE, b->label.c_str());

   //if (b->click_in)
   //   al_draw_rounded_rectangle(b->x+off+1, b->y+off+1, b->x+b->w-off-1, b->y+b->h-off-1, b->roundness, b->roundness, al_color_name("yellow"), 1.0);
}
*/


/*
void timer_func(Framework *f, ALLEGRO_TIMER_EVENT *ev)
{
   draw_clock(af_get_screen_width()/2, af_get_screen_height()/2, clock_radius, clock_opacity);
}
*/



class ClockExampleProgram : public FGUIScreen
{
private:
   bool clock_showing;
   FGUIButton *show_button;
   FGUIButton *hide_button;
public:
   ClockExampleProgram(Display *display)
      : FGUIScreen(display)
      , clock_showing(false)
      , show_button(NULL)
      , hide_button(NULL)
   {
      show_button = new FGUIButton(this, 200, 200, 80, 50, "Show");
      hide_button = new FGUIButton(this, 200, 300, 80, 50, "Hide");
   }
   void on_timer() override
   {
      draw_clock(display->width()/2, display->height()/2, clock_radius, clock_opacity);
   }
   void on_message(FGUIWidget *sender, std::string message) override
   {
      if (sender == show_button) show_clock(NULL, NULL, NULL);
      else if (sender == hide_button) hide_clock(NULL, NULL, NULL);
   }
};


int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   ClockExampleProgram *program = new ClockExampleProgram(display);
   Framework::run_loop();
   return 0;
}



