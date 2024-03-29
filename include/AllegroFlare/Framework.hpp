#pragma once


#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Config.hpp>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/Motion.hpp>
#include <AllegroFlare/ScreenManager.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/VirtualControlsProcessor.hpp>


namespace AllegroFlare
{
   class Screen;


   class Framework
   {
   private:
      ScreenManager *screens_ptr;
      bool initialized;
      Config config;
      FontBin fonts;
      SampleBin samples;
      BitmapBin bitmaps;
      ModelBin models;
      Motion motions;
      EventEmitter event_emitter;
      VirtualControlsProcessor virtual_controls_processor;

   public:
      Framework(ScreenManager *screens_ptr=nullptr);
      ~Framework();

      ALLEGRO_TEXTLOG *textlog;
      ALLEGRO_JOYSTICK *joystick; // this needs some updating to allow for multiple joysticks
      ALLEGRO_EVENT_QUEUE *event_queue;
      ALLEGRO_FONT *builtin_font;
      ALLEGRO_TIMER *primary_timer;
      bool shutdown_program; // set this to true at any time to shutdown the program
      Screen *current_screen;
      ALLEGRO_EVENT *current_event;
      double time_now; // used to be current_event_time

      int key_alt, key_shift, key_ctrl;
      bool drawing_profiler_graph;

      ALLEGRO_FONT *font(std::string identifier);
      ALLEGRO_BITMAP *bitmap(std::string identifier);
      ALLEGRO_SAMPLE *sample(std::string identifier);
      Model3D *model(std::string identifier);
      Motion &motion(); // we'll do this for now
      Config &get_config();
      FontBin &get_font_bin_ref();
      BitmapBin &get_bitmap_bin_ref();
      SampleBin &get_sample_bin_ref();

      bool initialize();
      bool destruct(); // should be privarte, is called in the destructor
      bool is_initialized();
      Display *create_display(int width=1280, int height=720);
      Display *create_display(int width, int height, int display_flags);
      Display *create_display(int width, int height, int display_flags, int adapter);
      Display *create_display(int width, int height, bool fullscreen);
      Display *create_display(int width, int height, bool fullscreen, int adapter);
      //Display *create_display(Display::resolution_t resolution);

      void run_loop();

      bool offset_primary_timer(int microseconds); // 16670 microseconds per frame

      std::string get_allegro_version_string();
      std::string get_allegro_flare_version_string();
      void open_log_window();
      void close_log_window();
      void log(std::string message);
   };
}


