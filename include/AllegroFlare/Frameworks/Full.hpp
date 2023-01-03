#pragma once


#include <string>
#include <functional>
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
#include <AllegroFlare/Achievements.hpp>
#include <AllegroFlare/Notifications.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/VirtualControlsProcessor.hpp>
#include <AllegroFlare/AudioRepositoryElement.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


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
         AllegroFlare::Profiler profiler;
         FontBin fonts; // TODO: fix this to "font_bin"
         SampleBin samples;
         BitmapBin bitmaps;
         ModelBin models;
         Motion motions;
         AudioController audio_controller;
         EventEmitter event_emitter;
         Achievements achievements;
         Notifications notifications;
         VirtualControlsProcessor virtual_controls_processor;
         ALLEGRO_TEXTLOG *textlog;
         ALLEGRO_JOYSTICK *joystick; // this needs some updating to allow for multiple joysticks
         Display *primary_display;
         ALLEGRO_BITMAP *primary_sub_bitmap;
         ALLEGRO_TIMER *primary_timer;
         Camera2D camera_2d;
         //Camera3D camera_3d; // next
         bool drawing_inputs_bar_overlay;
         bool drawing_notifications;
         std::vector<std::string> input_hints_tokens;
         bool initialize_without_display(); // only use initialize() publically from now on
         bool escape_key_will_shutdown;
         bool output_auto_created_config_warning;
         ALLEGRO_COLOR input_hints_text_color;
         float input_hints_text_opacity;
         ALLEGRO_COLOR input_hints_backfill_color;
         float input_hints_backfill_opacity;
         float input_hints_bar_height;
         bool fullscreen;
         AllegroFlare::DeploymentEnvironment deployment_environment;
         bool unset_deployment_environment_warning_on_initialization_is_disabled;

         void draw_overlay();
        
         std::map<uint32_t, std::pair<std::function<void(ALLEGRO_EVENT*, void*)>, void*>> event_callbacks;
         uint32_t next_event_callback_id;

         friend class AllegroFlare_Frameworks_FullTest;
         ALLEGRO_FONT *obtain_profiler_graph_font();

      public:
         Full();
         ~Full();

         ALLEGRO_EVENT_QUEUE *event_queue;
         ALLEGRO_FONT *builtin_font; // TODO: Femove this. There is now an expected Inter font for use
         bool shutdown_program; // set this to true at any time to shutdown the program
         Screens::Base *current_screen;
         ALLEGRO_EVENT *current_event;
         double time_now; // used to be current_event_time

         int key_alt, key_shift, key_ctrl;
         bool drawing_profiler_graph;

         ALLEGRO_FONT *font(std::string identifier);
         ALLEGRO_BITMAP *bitmap(std::string identifier);
         ALLEGRO_SAMPLE *sample(std::string identifier);
         Model3D *model(std::string identifier);
         Profiler &get_profiler_ref();
         Motion &motion(); // we'll do this for now
         Config &get_config();
         FontBin &get_font_bin_ref();
         BitmapBin &get_bitmap_bin_ref();
         SampleBin &get_sample_bin_ref();
         ModelBin &get_model_bin_ref();
         Camera2D &get_camera_2d_ref();
         ScreenManagers::Dictionary &get_screens_ref();
         AudioController &get_audio_controller_ref();
         EventEmitter &get_event_emitter_ref();
         Notifications &get_notifications_ref();
         Achievements &get_achievements_ref();
         Display *get_primary_display();


         bool initialize();
         bool is_initialized();
         bool shutdown();
         void disable_fullscreen();
         void disable_unset_deployment_environment_warning_on_initialization();
         void set_deployment_environment(std::string);

         void enable_escape_key_will_shutdown();
         void disable_escape_key_will_shutdown();
         void disable_auto_created_config_warning();
         void enable_auto_created_config_warning();

         void load_jukebox_sound_effects(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});
         void load_jukebox_music_tracks(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});

         void register_screen(std::string name, AllegroFlare::Screens::Base *screen);
         void unregister_screen(AllegroFlare::Screens::Base *screen);
         void activate_screen(std::string name);
         std::string get_currently_active_screen_name();

         void register_achievement(std::string name, Achievement *achievement);
         void unregister_achievement(Achievement *achievement); // NOT IMPLEMENTED

         void enable_drawing_inputs_bar_overlay();
         void disable_drawing_inputs_bar_overlay();
         void set_drawing_inputs_bar_overlay(bool drawing_inputs_bar_overlay);
         bool get_drawing_inputs_bar_overlay();

         void set_input_hints_tokens(std::vector<std::string> input_hints_tokens={});
         void clear_input_hints_tokens();
         std::vector<std::string> get_input_hints_tokens();
         float get_input_hints_text_opacity();
         float get_input_hints_backfill_opacity();
         float get_input_hints_bar_height();

         Display *create_display(int width=1280, int height=720);
         Display *create_display(int width, int height, int display_flags);
         Display *create_display(int width, int height, int display_flags, int adapter);
         Display *create_display(int width, int height, bool fullscreen);
         Display *create_display(int width, int height, bool fullscreen, int adapter);
         Display *create_display(Display::resolution_t resolution);

         void primary_update();
         void primary_render();
         void primary_process_event(ALLEGRO_EVENT *ev, bool drain_sequential_timer_events=true);
         int process_events_in_queue();
         void run_loop();

         bool offset_primary_timer(int microseconds); // 16670 microseconds per frame

         std::string get_allegro_version_string();
         std::string get_allegro_flare_version_string();
         void open_log_window();
         void close_log_window();
         void log(std::string message);

         uint32_t register_event_callback(std::function<void(ALLEGRO_EVENT*, void*)> callback, void* user_data);
         bool unregister_event_callback(uint32_t id);

         void draw_no_active_screens_text();
      };
   } // namespace Frameworks
} // namespace AllegroFlare


