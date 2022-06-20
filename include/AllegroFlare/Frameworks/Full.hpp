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
#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/VirtualControlsProcessor.hpp>
#include <AllegroFlare/AudioRepositoryElement.hpp>


namespace AllegroFlare
{
   namespace Frameworks
   {
      class Full
      {
      private:
         ScreenManagers::Dictionary screens;
         bool initialized;
         Config config;
         FontBin fonts;
         SampleBin samples;
         BitmapBin bitmaps;
         ModelBin models;
         Motion motions;
         AudioController audio_controller;
         EventEmitter event_emitter;
         VirtualControlsProcessor virtual_controls_processor;
         ALLEGRO_TEXTLOG *textlog;
         ALLEGRO_JOYSTICK *joystick; // this needs some updating to allow for multiple joysticks
         Display *primary_display;
         ALLEGRO_TIMER *primary_timer;

         bool initialize_without_display(); // only use initialize_with_display() publically from now on
         bool destruct(); // should be privarte, is called in the destructor

         friend class AllegroFlare_Frameworks_FullTest;

      public:
         Full();
         ~Full();

         ALLEGRO_EVENT_QUEUE *event_queue;
         ALLEGRO_FONT *builtin_font;
         bool shutdown_program; // set this to true at any time to shutdown the program
         Screens::Basic *current_screen;
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
         ScreenManagers::Dictionary &get_screens_ref();
         AudioController &get_audio_controller_ref();
         EventEmitter &get_event_emitter_ref();
         Display *get_primary_display();

         bool initialize();
         bool is_initialized();

         void load_jukebox_sound_effects(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});
         void load_jukebox_music_tracks(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});

         void register_screen(std::string name, AllegroFlare::Screens::Basic *screen);
         void unregister_screen(AllegroFlare::Screens::Basic *screen);
         void activate_screen(std::string name);

         Display *create_display(int width=1280, int height=720);
         Display *create_display(int width, int height, int display_flags);
         Display *create_display(int width, int height, int display_flags, int adapter);
         Display *create_display(int width, int height, bool fullscreen);
         Display *create_display(int width, int height, bool fullscreen, int adapter);
         Display *create_display(Display::resolution_t resolution);

         void run_loop();

         bool offset_primary_timer(int microseconds); // 16670 microseconds per frame

         std::string get_allegro_version_string();
         std::string get_allegro_flare_version_string();
         void open_log_window();
         void close_log_window();
         void log(std::string message);
      };
   } // namespace Frameworks
} // namespace AllegroFlare


