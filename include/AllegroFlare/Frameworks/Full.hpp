#pragma once
#define ALLEGRO_UNSTABLE


#include <string>
#include <functional>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/VideoBin.hpp>
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
#include <AllegroFlare/RenderSurfaces/DisplayBackbuffer.hpp>
#include <AllegroFlare/RenderSurfaces/DisplayBackbufferSubBitmap.hpp>
#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>
#include <AllegroFlare/ShaderSourcePoller.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/InputDevicesList.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/Routers/Base.hpp>


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
         VideoBin video_bin;
         Motion motions;
         AudioController audio_controller;
         EventEmitter event_emitter;
         Achievements achievements;
         Notifications notifications;
         DialogSystem::DialogSystem dialog_system;
         AllegroFlare::InputDevicesList input_devices_list;
         VirtualControlsProcessor virtual_controls_processor;
         AllegroFlare::Routers::Base* router;
         ALLEGRO_TEXTLOG *textlog;
         int render_surface_multisamples;
         int render_surface_depth_size;
         int render_surface_adapter;
         Display *primary_display;
         //ALLEGRO_BITMAP *primary_display_sub_bitmap_for_overlay;
         ALLEGRO_TIMER *primary_timer;
         Camera2D camera_2d;

         AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer;
         AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap;
         AllegroFlare::RenderSurfaces::Base *primary_render_surface;
         AllegroFlare::Shaders::Base *post_processing_shader;

         //Camera3D camera_3d; // next
         bool drawing_inputs_bar_overlay;
         bool drawing_notifications;
         bool drawing_dialogs;
         std::vector<std::string> input_hints_tokens;
         bool initialize_core_system(); // only use initialize() publically from now on
         bool initialize_display_and_render_pipeline();
         bool display_close_will_shutdown;
         bool escape_key_will_shutdown;
         bool output_auto_created_config_warning;
         bool set_primary_render_surface_as_target_before_calling_primary_timer_funcs;
         bool clear_render_surface_before_calling_primary_timer_funcs;
         bool using_display_backbuffer_as_primary_render_surface;
         ALLEGRO_COLOR input_hints_text_color;
         float input_hints_text_opacity;
         ALLEGRO_COLOR input_hints_backfill_color;
         float input_hints_backfill_opacity;
         float input_hints_bar_height;
         bool fullscreen;
         bool mipmapping;
         AllegroFlare::DeploymentEnvironment deployment_environment;
         bool unset_deployment_environment_warning_on_initialization_is_disabled;
         AllegroFlare::ShaderSourcePoller shader_source_poller;
         AllegroFlare::Shaders::Base *shader_target_for_hotloading;

         void draw_overlay();
        
         std::map<uint32_t, std::pair<std::function<void(ALLEGRO_EVENT*, void*)>, void*>> event_callbacks;
         uint32_t next_event_callback_id;

         friend class AllegroFlare_Frameworks_FullTest;
         ALLEGRO_FONT *obtain_profiler_graph_font();
         ALLEGRO_FONT *obtain_system_text_font_medium();

      public:
         Full();
         ~Full();

         ALLEGRO_EVENT_QUEUE *event_queue;
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
         VideoBin &get_video_bin_ref();
         ScreenManagers::Dictionary &get_screen_manager_ref();
         AudioController &get_audio_controller_ref();
         EventEmitter &get_event_emitter_ref();
         Notifications &get_notifications_ref();
         Achievements &get_achievements_ref();
         AllegroFlare::Routers::Base *get_router();
         void set_router(AllegroFlare::Routers::Base* router);
         Display *get_primary_display();

         void set_render_surface_multisamples(int render_surface_multisamples=4);
         RenderSurfaces::Base *get_primary_render_surface();
         AllegroFlare::Shaders::Base *get_post_processing_shader();
         void set_post_processing_shader(AllegroFlare::Shaders::Base *post_processing_shader);

         void set_shader_target_for_hotloading(AllegroFlare::Shaders::Base *shader_target_for_hotloading=nullptr);
         AllegroFlare::Shaders::Base *get_shader_target_for_hotloading();

         bool initialize();
         bool is_initialized();
         bool shutdown(); // TODO: make this private
         void disable_mipmapping();
         void disable_fullscreen();
         void disable_unset_deployment_environment_warning_on_initialization();
         void set_deployment_environment(std::string);
         bool is_deployment_environment_production();
         bool is_deployment_environment_development();
         bool is_deployment_environment_test();
         std::string get_data_folder_path();

         void enable_display_close_will_shutdown();
         void disable_display_close_will_shutdown();
         void enable_escape_key_will_shutdown();
         void disable_escape_key_will_shutdown();
         void enable_auto_created_config_warning();
         void disable_auto_created_config_warning();
         void enable_set_primary_render_surface_as_target_before_calling_primary_timer_funcs();
         void disable_set_primary_render_surface_as_target_before_calling_primary_timer_funcs();
         bool is_set_primary_render_surface_as_target_before_calling_primary_timer_funcs_enabled();
         void enable_clear_render_surface_before_calling_primary_timer_funcs();
         void disable_clear_render_surface_before_calling_primary_timer_funcs();
         bool is_clear_render_surface_before_calling_primary_timer_funcs_enabled();
         void enable_using_display_backbuffer_as_primary_render_surface();
         void disable_using_display_backbuffer_as_primary_render_surface();
         bool is_using_display_backbuffer_as_primary_render_surface();

         // Dialog System
         void set_dialog_system_load_node_bank_func(
               std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> load_node_bank_func
            );
         void set_dialog_system_load_node_bank_func_user_data(void* load_node_bank_func_user_data);
         void set_dialog_system_activate_dialog_node_by_name_func(
               std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)>
                     activate_dialog_node_by_name_func
            );
         void set_dialog_system_activate_dialog_node_by_name_func_user_data(void* 
               activate_dialog_node_by_name_func_user_data
            );
         DialogSystem::DialogSystem &get_dialog_system_ref();

         // Audio Controller System
         void load_jukebox_sound_effects(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});
         void load_jukebox_music_tracks(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements={});

         void register_screen(std::string name, AllegroFlare::Screens::Base *screen);
         void unregister_screen(AllegroFlare::Screens::Base *screen);
         void activate_screen(std::string name);
         void register_and_activate_screen(std::string name, AllegroFlare::Screens::Base *screen);
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

         void render_screens_to_primary_render_surface();

         void primary_update();
         void primary_render();
         void primary_process_event(ALLEGRO_EVENT *ev, bool drain_sequential_timer_events=true);
         int process_events_in_queue();
         void run_loop(float auto_shutdown_after_seconds=-1);

         bool offset_primary_timer(int microseconds); // 16670 microseconds per frame

         std::string get_allegro_version_string();
         std::string get_allegro_flare_version_string();
         void open_log_window();
         void close_log_window();
         void log(std::string message);

         uint32_t register_event_callback(std::function<void(ALLEGRO_EVENT*, void*)> callback, void* user_data);
         bool unregister_event_callback(uint32_t id);

         void draw_no_active_screens_text();

      public:
         static constexpr char* DEFAULT_CONFIG_FILENAME = (char*)"data/config/config.cfg";
         static constexpr int DEFAULT_DISPLAY_WIDTH = 1920;
         static constexpr int DEFAULT_DISPLAY_HEIGHT = 1080;
      };
   } // namespace Frameworks
} // namespace AllegroFlare


