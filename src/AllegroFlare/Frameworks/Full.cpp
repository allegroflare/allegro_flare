



#include <AllegroFlare/Frameworks/Full.hpp>

#include <thread> // for offset_primary_timer
#include <chrono> // for offset_primary_timer
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/AllegroColorAttributeDatatype.hpp>
#include <AllegroFlare/Attributes.hpp>
#include <AllegroFlare/Motion.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/Version.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/InputHints.hpp>
#include <AllegroFlare/Elements/NotificationsRenderer.hpp>
#include <AllegroFlare/NotificationsFactory.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/ProfilerRenderer.hpp>



namespace AllegroFlare
{
namespace Frameworks
{


Full::Full()
   : working_directory_before_init(".")
   , screens()
   , initialized(false)
   , config("data/config/config.cfg")
   , profiler()
   , fonts()
   , samples()
   , bitmaps()
   , models()
   , motions(200)
   , audio_controller(&samples)
   , event_emitter()
   , achievements()
   , notifications()
   , virtual_controls_processor()
   , textlog(nullptr)
   , primary_display(nullptr)
   //, primary_display_sub_bitmap_for_overlay(nullptr)
   , primary_timer(nullptr)
   , camera_2d()
   , display_backbuffer()
   , display_backbuffer_sub_bitmap()
   , primary_render_surface(nullptr)
   , post_processing_shader(nullptr)
   , drawing_inputs_bar_overlay(false)
   , drawing_notifications(true)
   , input_hints_tokens({})
   , escape_key_will_shutdown(true)
   , output_auto_created_config_warning(true)
   , set_primary_render_surface_as_target_before_calling_primary_timer_funcs(true)
   , clear_to_color_before_calling_primary_timer_funcs(true)
   , clear_depth_buffer_before_calling_primary_timer_funcs(true)
   , using_display_backbuffer_as_primary_render_surface(true)
   , input_hints_text_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , input_hints_text_opacity(0.4)
   , input_hints_backfill_color(ALLEGRO_COLOR{0, 0, 0, 0})
   , input_hints_backfill_opacity(0.35)
   , input_hints_bar_height(60)
   , fullscreen(true)
   , deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_UNDEF)
   , unset_deployment_environment_warning_on_initialization_is_disabled(false)
   , event_callbacks()
   , next_event_callback_id(1)
   , event_queue(nullptr)
   , shutdown_program(false)
   , current_screen(nullptr)
   , current_event(nullptr)
   , time_now(0)
   , key_alt(0)
   , key_shift(0)
   , key_ctrl(0)
   , drawing_profiler_graph(false)
{}


Full::~Full()
{
   shutdown();
}


ALLEGRO_FONT *Full::font(std::string identifier)
{
   return fonts[identifier];
}


ALLEGRO_BITMAP *Full::bitmap(std::string identifier)
{
   return bitmaps[identifier];
}


ALLEGRO_SAMPLE *Full::sample(std::string identifier)
{
   return samples[identifier];
}


Model3D *Full::model(std::string identifier)
{
   return models[identifier];
}


Profiler &Full::get_profiler_ref()
{
   return profiler;
}


Motion &Full::motion()
{
   return motions;
}


Config &Full::get_config()
{
   return config;
}


FontBin &Full::get_font_bin_ref()
{
   return fonts;
}


BitmapBin &Full::get_bitmap_bin_ref()
{
   return bitmaps;
}



SampleBin &Full::get_sample_bin_ref()
{
   return samples;
}


ModelBin &Full::get_model_bin_ref()
{
   return models;
}


Camera2D &Full::get_camera_2d_ref()
{
   return camera_2d;
}



AudioController &Full::get_audio_controller_ref()
{
   return audio_controller;
}


EventEmitter &Full::get_event_emitter_ref()
{
   return event_emitter;
}


Notifications &Full::get_notifications_ref()
{
   return notifications;
}


Achievements &Full::get_achievements_ref()
{
   return achievements;
}


Display *Full::get_primary_display()
{
   return primary_display;
}



bool Full::initialize_without_display()
{
   if (initialized) return false;

   if (!al_init()) std::cerr << "al_init() failed" << std::endl;



   // Before setting the path, we will need to capture the existing path so it can be restores
   // after destruction.

   // TODO: finish this message with actual working directory, put behind warn levels
   {
      std::string info_message = AllegroFlare::Logger::build_info_message(
         "AllegroFlare::Frameworks::Full::initialize_without_display",
         "Capturing initial working directory before modifying."
      );
      std::cout << info_message << std::endl;
   }
   working_directory_before_init = std::filesystem::current_path().string();

   if (deployment_environment.is_undefined())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Frameworks::Full::initialize_without_display",
         "The current deployment environment has not been defined. Before calling "
            "AllegroFlare::Frameworks::Full::initialize(), be sure to set a deployment environment with "
            "AllegroFlare::Frameworks::Full::set_deployment_environment(). In the mean time, the environemnt will "
            "automatically be set to ENVIRONMENT_DEVELOPMENT. You can also disable this warning message with "
            "AllegroFlare::Frameworks::Full::disable_unset_deployment_environment_warning_on_initialization()."
      );
      deployment_environment.set_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT);
   }

   if (deployment_environment.is_invalid())
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::Frameworks::Full::initialize_without_display",
         "The current deployment environment is invalid. Before calling Frameworks::Full::initialize(), "
         "be sure to set a deployment environment with set_deployment_environment(...)."
      );
   }

   std::string deployment_environment_message = "Deployment environment is " + deployment_environment.get_environment();
   std::string info_message = AllegroFlare::Logger::build_info_message(
      "AllegroFlare::Frameworks::Full::initialize_without_display",
      deployment_environment_message
   );
   std::cout << info_message << std::endl;

   if (deployment_environment.environment_should_set_path_to_resources_path()) // NOTE: this happens in PRODUCTION
   {
      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);
   }
   else
   {
      // Do nothing. Presume that the executable (which is assumed to be a test executable) is being run from the
      // root folder of the project, otherwise there will be undefined behavior.
   }

   std::string data_folder_path = deployment_environment.get_data_folder_path();


   // Output current directory that framework is being run from 
   {
      std::string info_message = AllegroFlare::Logger::build_info_message(
         "AllegroFlare::Frameworks::Full::initialize_without_display",
         "Running from working path: \"" + std::filesystem::current_path().string() + "\". "
         "Data folder path: \"" + data_folder_path + "\""
      );
      std::cout << info_message << std::endl;
   }


   // Initialize Allegro's various parts

   if (!al_install_mouse()) std::cerr << "al_install_mouse() failed" << std::endl;
   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;
   if (!al_install_joystick()) std::cerr << "al_install_joystick() failed" << std::endl;
   if (!al_install_audio()) std::cerr << "al_install_audio() failed" << std::endl;

   if (!al_init_native_dialog_addon()) std::cerr << "al_init_native_dialog_addon() failed" << std::endl;
   if (!al_init_primitives_addon()) std::cerr << "al_init_primitives_addon() failed" << std::endl;
   if (!al_init_image_addon()) std::cerr << "al_init_image_addon() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;
   if (!al_init_acodec_addon()) std::cerr << "al_init_acodec_addon() failed" << std::endl;

   if (!al_reserve_samples(32)) std::cerr << "al_reserve_samples() failed" << std::endl;



   // Setup our preferred objects & settings

   srand(time(NULL));

   primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));

   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
   //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_joystick_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_default_menu_event_source());

   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   virtual_controls_processor.set_event_emitter(&event_emitter);
   virtual_controls_processor.initialize();

   achievements.set_event_emitter(&event_emitter);

   // TODO: prevent these paths from being hard-coded, or, allow it to be hard-coded in the context of
   // different deployment environments.
   fonts.set_path(data_folder_path + "fonts");
   samples.set_path(data_folder_path + "samples");
   bitmaps.set_path(data_folder_path + "bitmaps");
   models.set_path(data_folder_path + "models");

   config.load_or_create_empty(output_auto_created_config_warning);

   Attributes::create_datatype_definition(
      AllegroColorAttributeDatatype::IDENTIFIER,
      AllegroColorAttributeDatatype::to_val_func,
      AllegroColorAttributeDatatype::to_str_func
   );

   audio_controller.initialize();
 

   // Finalize initialization

   initialized = true;

   return true;
}



RenderSurfaces::Base *Full::get_primary_render_surface()
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::get_data_folder_path",
         "Could retrieve because the framework has not yet been initialized. "
            "You must call this function after initialization so the render surfaces can be set."
      );
   }

   return primary_render_surface;
}



AllegroFlare::Shaders::Base *Full::get_post_processing_shader()
{
   return post_processing_shader;
}



void Full::set_post_processing_shader(AllegroFlare::Shaders::Base *post_processing_shader)
{
   this->post_processing_shader = post_processing_shader;
}



bool Full::initialize()
{
   if (initialized) return false;

   initialize_without_display();

   int display_flags = ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE;
   if (fullscreen) display_flags |= ALLEGRO_FULLSCREEN_WINDOW;

   //al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_REQUIRE);

   // TODO: validate size of display before creating a window that is larger than the display. If so, output a
   // warning.


   primary_display = create_display(
         1920,
         1080,
         display_flags
         //ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE
      );

   if (!primary_display || !primary_display->al_display)
   {
      throw std::runtime_error("[Frameworks::Full::initialize]: FAILURE: unable to create primary_display.");
   }


   display_backbuffer.set_display(primary_display->al_display);
   display_backbuffer.initialize();
   // setup a nice projection on our backbuffer
   camera_2d.setup_dimentional_projection(display_backbuffer.get_display_backbuffer());
                                                              // ^^ NOTE: this could potentially change depending on the
                                                              // needs of the game, but is setup here as a reasonable
                                                              // default
                                                              // TODO: replace this with display_backbuffer

   if (using_display_backbuffer_as_primary_render_surface)
   {
      // use the display_backbuffer as our render surface
      primary_render_surface = &display_backbuffer;
   }
   else
   {
      // TODO: Implement this new reality please!
      AllegroFlare::RenderSurfaces::Bitmap *bitmap_render_surface = new AllegroFlare::RenderSurfaces::Bitmap;
      bitmap_render_surface->setup_surface(1920, 1080, 4, 16);
      primary_render_surface = bitmap_render_surface;
   }


   // Initialize our backbuffer sub bitmap that is used to display AllegroFlare overlay, like performance graphs,
   // in-game notificatoins, etc.
   display_backbuffer_sub_bitmap.set_display(primary_display->al_display);
   display_backbuffer_sub_bitmap.initialize();
   camera_2d.setup_dimentional_projection(display_backbuffer_sub_bitmap.get_display_backbuffer_sub_bitmap());
                                                               // this should remain the same throughout
                                                               // the whole program and never be modified

   return true;
}



void Full::disable_fullscreen()
{
   if (initialized)
   {
      std::cout << "[AllegroFlare::Frameworks::Full::disable_fullscreen]: WARNING: "
                << "could not disable because the framework has already been initialized.  "
                << "For now, you must disable the fullscreen before initializing the framework for it to take effect."
                << std::endl;
   }
   if (!initialized) fullscreen = false;
}



void Full::disable_unset_deployment_environment_warning_on_initialization()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::disable_unset_deployment_environment_warning_on_initialization",
         "Could not disable because the framework has already been initialized. "
            "You must call this function before initializing the framework for it to take effect."
      );
   }
   if (!initialized) unset_deployment_environment_warning_on_initialization_is_disabled = true;
}



void Full::set_deployment_environment(std::string environment)
{
   // TODO: add tests for this function
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::set_deployment_environment",
         "Could not set because the framework has already been initialized. "
            "You must call this function before initializing the framework for it to take effect."
      );
   }

   deployment_environment.set_environment(environment);
}



bool Full::is_deployment_environment_production()
{
   // TODO: add tests for this function
   return deployment_environment.is_production();
}



bool Full::is_deployment_environment_development()
{
   // TODO: add tests for this function
   return deployment_environment.is_development();
}



bool Full::is_deployment_environment_test()
{
   // TODO: add tests for this function
   return deployment_environment.is_test();
}



std::string Full::get_data_folder_path()
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::get_data_folder_path",
         "Could retrieve because the framework has not yet been initialized. "
            "You must call this function after initialization so the path has been has been properly set."
      );
   }

   return deployment_environment.get_data_folder_path();
}



bool Full::shutdown()
{
   if (!initialized) return false;

   // TODO: this line is commented out now that we are assuming the "system_text_font" is not allegro's "builtin" font.
   // Note that if the font *is* created as the builtin font, then it should be deleted. For now, that case is
   // being ignored. You could possibly consider a case where the builtin font is included in the font bin.
   //al_destroy_font(system_text_font);

   // TODO autit this function
   samples.clear();
   bitmaps.clear();
   fonts.clear();
   models.clear();

   event_callbacks.clear();

   // TODO: destroy sub-bitmap here on new render surface:
   //if (primary_display_sub_bitmap_for_overlay) al_destroy_bitmap(primary_display_sub_bitmap_for_overlay);
   if (primary_display) al_destroy_display(primary_display->al_display);

   audio_controller.destruct();

   al_shutdown_image_addon(); //) std::cerr << "shutdown of al_init_image_addon() failed" << std::endl;
   al_shutdown_ttf_addon(); //) std::cerr << "shutdown al_init_ttf_addon() failed" << std::endl;
   al_shutdown_font_addon(); //) std::cerr << "shutdown of al_init_font_addon() failed" << std::endl;
   al_shutdown_primitives_addon(); //) std::cerr << "shutdown of al_init_primitives_addon() failed" << std::endl;
   al_shutdown_native_dialog_addon(); // std::cerr << "shutdown of al_init_native_dialog_addon() failed" << std::endl;
   //al_shutdown_acodec_addon(); // not a thing, possibly a bug. Causes some issues with testing

   al_uninstall_audio();
   al_uninstall_joystick();
   al_uninstall_keyboard();
   al_uninstall_mouse();

   // restore path
   // TODO: finish this message with actual working directory, put behind warn levels
   //if (AllegroFlare::Logger::log_level_low())
   {
      std::string info_message = AllegroFlare::Logger::build_info_message(
         "AllegroFlare::Frameworks::Full::shutdown",
         "Restoring working directory to initial directory at runtime."
      );
      std::cout << info_message << std::endl;
   }
   al_change_directory(working_directory_before_init.c_str());


   al_uninstall_system(); // Note that there is risk of a crash at shutdown if assets have been created outside the
                          // lifecycle of the Framework

   initialized = false;

   return true;
}


void Full::enable_escape_key_will_shutdown()
{
   this->escape_key_will_shutdown = true;
}


void Full::disable_escape_key_will_shutdown()
{
   this->escape_key_will_shutdown = false;
}


void Full::enable_auto_created_config_warning()
{
   this->output_auto_created_config_warning = true;
}


void Full::disable_auto_created_config_warning()
{
   this->output_auto_created_config_warning = false;
}


void Full::enable_set_primary_render_surface_as_target_before_calling_primary_timer_funcs()
{
   set_primary_render_surface_as_target_before_calling_primary_timer_funcs = true;
}


void Full::disable_set_primary_render_surface_as_target_before_calling_primary_timer_funcs()
{
   set_primary_render_surface_as_target_before_calling_primary_timer_funcs = false;
}


bool Full::is_set_primary_render_surface_as_target_before_calling_primary_timer_funcs_enabled()
{
   return set_primary_render_surface_as_target_before_calling_primary_timer_funcs;
}


void Full::enable_clear_to_color_before_calling_primary_timer_funcs()
{
   clear_to_color_before_calling_primary_timer_funcs = true;
}


void Full::disable_clear_to_color_before_calling_primary_timer_funcs()
{
   clear_to_color_before_calling_primary_timer_funcs = false;
}


bool Full::is_clear_to_color_before_calling_primary_timer_funcs_enabled()
{
   return clear_to_color_before_calling_primary_timer_funcs;
}


void Full::enable_clear_depth_buffer_before_calling_primary_timer_funcs()
{
   clear_depth_buffer_before_calling_primary_timer_funcs = true;
}


void Full::disable_clear_depth_buffer_before_calling_primary_timer_funcs()
{
   clear_depth_buffer_before_calling_primary_timer_funcs = false;
}


bool Full::is_clear_depth_buffer_before_calling_primary_timer_funcs_enabled()
{
   return clear_depth_buffer_before_calling_primary_timer_funcs;
}



void Full::enable_using_display_backbuffer_as_primary_render_surface()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::enable_using_display_backbuffer_as_primary_render_surface",
         "Could not set because the framework has already been initialized. "
            "For now, you must call this function before initializing the framework for it to take effect."
      );
   }
   using_display_backbuffer_as_primary_render_surface = true;
}



void Full::disable_using_display_backbuffer_as_primary_render_surface()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::disable_using_display_backbuffer_as_primary_render_surface",
         "Could not set because the framework has already been initialized. "
            "For now, you must call this function before initializing the framework for it to take effect."
      );
   }
   using_display_backbuffer_as_primary_render_surface = false;
}



bool Full::is_using_display_backbuffer_as_primary_render_surface()
{
   return using_display_backbuffer_as_primary_render_surface;
}



bool Full::is_initialized()
{
   return initialized;
}


void Full::load_jukebox_sound_effects(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements)
{
   audio_controller.set_and_load_sound_effect_elements(elements);
}


void Full::load_jukebox_music_tracks(std::map<std::string, AllegroFlare::AudioRepositoryElement> elements)
{
   audio_controller.set_and_load_music_track_elements(elements);
}


void Full::register_screen(std::string name, AllegroFlare::Screens::Base *screen)
{
   screens.add(name, screen);
}


void Full::unregister_screen(AllegroFlare::Screens::Base *screen)
{
   screens.remove(screen);
}


void Full::activate_screen(std::string name)
{
   screens.activate(name);
}


void Full::register_and_activate_screen(std::string name, AllegroFlare::Screens::Base *screen)
{
   register_screen(name, screen);
   activate_screen(name);
}


std::string Full::get_currently_active_screen_name()
{
   return screens.get_currently_active_screen_name();
}


void Full::register_achievement(std::string name, Achievement *achievement)
{
   achievements.add(name, achievement);
}


void Full::unregister_achievement(Achievement *achievement)
{
   throw std::runtime_error("Frameworks::Full::unregister: error: not implemented");
   // TODO: not implemented
}


void Full::enable_drawing_inputs_bar_overlay()
{
   drawing_inputs_bar_overlay = true;
}


void Full::disable_drawing_inputs_bar_overlay()
{
   drawing_inputs_bar_overlay = false;
}


void Full::set_drawing_inputs_bar_overlay(bool drawing_inputs_bar_overlay)
{
   this->drawing_inputs_bar_overlay = drawing_inputs_bar_overlay;
}


bool Full::get_drawing_inputs_bar_overlay()
{
   return drawing_inputs_bar_overlay;
}


Display *Full::create_display(int width, int height)
{
   return create_display(width, height, false, -1);
}


Display *Full::create_display(int width, int height, int display_flags)
{
   Display *display = new Display(width, height, display_flags);
   al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
   return display;
}


Display *Full::create_display(int width, int height, int display_flags, int adapter)
{
   if (adapter!=-1) al_set_new_display_adapter(adapter);
   Display *display = new Display(width, height, display_flags);
   al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
   return display;
}


Display *Full::create_display(int width, int height, bool fullscreen)
{
   Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);
   al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
   return display;
}


Display *Full::create_display(int width, int height, bool fullscreen, int adapter)
{
   if (adapter!=-1) al_set_new_display_adapter(adapter);
   Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);

   al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
   return display;
}


Display *Full::create_display(Display::resolution_t resolution)
{
   int w, h;
   int screen_flags = ALLEGRO_FLAGS_EMPTY;
   int display_adapter_to_use = 0;

   switch(resolution)
   {
   case Display::RESOLUTION_XGA:
      w = 1024;
      h = 768;
      break;
   case Display::RESOLUTION_WXGA:
      w = 1280;
      h = 800;
      break;
   case Display::RESOLUTION_WXGA_PLUS:
      w = 1440;
      h = 900;
      break;
   case Display::RESOLUTION_HD_1080:
      w = 1920;
      h = 1080;
      break;
   case Display::RESOLUTION_HD_720:
      w = 1280;
      h = 720;
      break;
   case Display::RESOLUTION_RETINA:
      w = 2880;
      h = 1800;
      break;
   case Display::FULLSCREEN_AUTO:
      {
         ALLEGRO_MONITOR_INFO monitor_info;
         al_get_monitor_info(display_adapter_to_use, &monitor_info);
         w = monitor_info.x2 - monitor_info.x1;
         h = monitor_info.y2 - monitor_info.y1;
         screen_flags = ALLEGRO_FULLSCREEN;
      }
      break;
   default:
      w = 1024;
      h = 768;
      break;
   }

   return create_display(w, h, screen_flags, display_adapter_to_use);
}


bool Full::offset_primary_timer(int microseconds)
{
   if (!primary_timer)
   {
      throw std::runtime_error("Frameworks::Full: offset_primary_timer: primary_timer cannot be nullptr");
   }
   if (!al_get_timer_started(primary_timer)) return false;

   // TODO, profile this delay offset and output the actual offset to cout
   al_stop_timer(primary_timer);
   std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
   al_start_timer(primary_timer);

   return true;
}


void Full::primary_update()
{
   // update
   motions.update(time_now);
   achievements.check_all();
}


void Full::render_screens_to_primary_render_surface()
{
   //ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(primary_display->al_display);
   //al_set_target_bitmap(backbuffer_bitmap);
   if (set_primary_render_surface_as_target_before_calling_primary_timer_funcs)
   {
      primary_render_surface->set_as_target();
      
      if (clear_to_color_before_calling_primary_timer_funcs) al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      if (clear_depth_buffer_before_calling_primary_timer_funcs) al_clear_depth_buffer(1);
      // Maybe will use this:
      //al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL); // less or equal allows 
                                                                                // subsequent renders at the same
                                                                                // z-level to overwrite. This 
                                                                                // mimics the rendering of typical
                                                                                // "traditional" drawing functions
   }

   if (screens.no_active_screens())
   {
      draw_no_active_screens_text();
   }
   else
   {
      screens.primary_timer_funcs();
   }


   // If the primary_render_surface is *not* a display, fully draw it to the backbuffer.
   // TODO: Consider if the backbuffer surface projection is valid for this rendering, e.g. the "display backbuffer"
   // render surface should be unmodified through the course of the user's code (any code in screens).
   // This includes, but is not limited to:
   //   - ALLEGRO_DEPTH_TEST
   //   - ALLEGRO_WRITE_MASK
   //   - the projection that is currently used on the display backbuffer
   //   - a cleared depth buffer
   //   - current shader (which in this next block is expected to be set to a post-processing shader)
   //   - blending modes
   if (primary_render_surface && !primary_render_surface->is_a_display_surface())
   {
      // render the primary_render_surface to the backbuffer
      display_backbuffer.set_as_target();
      ALLEGRO_BITMAP *bitmap = primary_render_surface->obtain_surface();

      // TODO: setup the post-process shader
      // TODO: consider if disabling a depth buffer (or other flags) are needed here
      //if (post_processing_shader) post_processing_shader->activate();
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 0); // may want this?
      //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_RGB); // may want this?
      al_draw_bitmap(bitmap, 0, 0, 0);
      //if (post_processing_shader) post_processing_shader->deactivate();
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 1); // may want this?
      //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA); // may want this?
   }
}


void Full::primary_render()
{
   profiler.start(".render_screens_to_primary_render_surface()");
   render_screens_to_primary_render_surface();
   profiler.stop(".render_screens_to_primary_render_surface()");

   draw_overlay(); // NOTE: Default shader and other state restoration flags are handled within the function.

   profiler.start("al_flip_display()");
   al_flip_display();
   profiler.stop("al_flip_display()");
}


void Full::primary_process_event(ALLEGRO_EVENT *ev, bool drain_sequential_timer_events)
{
      ALLEGRO_EVENT &this_event = *ev;
      ALLEGRO_EVENT next_event;

      // process callbacks first
      for (auto &event_callback : event_callbacks)
      {
         // call the callback function, and pass in the user_data provided when the
         // callback was registered
         event_callback.second.first(&this_event, event_callback.second.second);
      }

      screens.on_events(current_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_TIMER:
         if (this_event.timer.source == primary_timer)
         {
            primary_update();
            primary_render();
         }
         else
         {
            screens.timer_funcs();
         }

         if (drain_sequential_timer_events)
         {
            ALLEGRO_EVENT next_event;
            while (al_peek_next_event(event_queue, &next_event)
               && next_event.type == ALLEGRO_EVENT_TIMER
               && next_event.timer.source == this_event.timer.source)
            {
               al_drop_next_event(event_queue);
            }
         }
      break;

      case ALLEGRO_EVENT_KEY_DOWN:
         if (this_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
         {
            if (escape_key_will_shutdown) shutdown_program = true;
         }

         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Full::key_shift++;
         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Full::key_alt++;
         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Full::key_ctrl++;
         if (current_event->keyboard.keycode == ALLEGRO_KEY_F1)
            drawing_profiler_graph = !drawing_profiler_graph; // toggle the profiler graph with F1
         screens.key_down_funcs(&this_event);
         virtual_controls_processor.handle_raw_keyboard_key_down_event(&this_event);
      break;

      case ALLEGRO_EVENT_KEY_UP:
         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Full::key_shift--;
         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Full::key_alt--;
         if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
               || Full::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Full::key_ctrl--;
         screens.key_up_funcs(&this_event);
         virtual_controls_processor.handle_raw_keyboard_key_up_event(&this_event);
      break;

      case ALLEGRO_EVENT_KEY_CHAR:
         screens.key_char_funcs(&this_event);
         //virtual_controls_processor.handle_raw_keyboard_key_char_event(&this_event); // LOOK INTO THIS
      break;

      case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
         screens.mouse_up_funcs(&this_event);
      break;

      case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
         screens.mouse_down_funcs(&this_event);
      break;

      case ALLEGRO_EVENT_MOUSE_WARPED:
         screens.mouse_warp_funcs(&this_event);
      break;

      case ALLEGRO_EVENT_MOUSE_AXES:
         screens.mouse_axes_funcs(&this_event);
      break;

      case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
         screens.joy_button_down_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_button_down_event(&this_event);
      break;

      case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
         screens.joy_button_up_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_button_up_event(&this_event);
      break;

      case ALLEGRO_EVENT_JOYSTICK_AXIS:
         screens.joy_axis_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_axis_change_event(&this_event);
      break;

      case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
         screens.joy_config_funcs(&this_event);
         virtual_controls_processor.handle_joystick_device_configuration_change_event(&this_event);
      break;

      case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
      case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
         // currently ignored
      break;

      case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
         screens.display_switch_out_funcs();
      break;

      case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
         screens.display_switch_in_funcs();
      break;

      case ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE:
         //screens.display_switch_in_funcs();
         if (textlog) close_log_window();
      break;

      case ALLEGRO_EVENT_MENU_CLICK:
         screens.native_menu_click_funcs();
      break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         {
            Display *this_display = Display::find_display(this_event.display.source);
            if (this_display) this_display->display_close_func();
         }
      break;

      default:
         if (ALLEGRO_EVENT_TYPE_IS_USER(this_event.type))
         {
            if (this_event.any.source == &event_emitter.get_event_source_ref())
            {
               screens.event_emitter_event_funcs(&this_event);

               switch(this_event.type)
               {
                  case ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR:
                     disable_drawing_inputs_bar_overlay();
                  break;

                  case ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR:
                     enable_drawing_inputs_bar_overlay();
                  break;

                  case ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_TEXT_OPACITY: {
                     float *data = (float *)this_event.user.data1;
                     input_hints_text_opacity = *data;
                     delete data;
                  } break;

                  case ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_BACKFILL_OPACITY: {
                     float *data = (float *)this_event.user.data1;
                     input_hints_backfill_opacity = *data;
                     delete data;
                  } break;

                  case ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_HEIGHT: {
                     float *data = (float *)this_event.user.data1;
                     input_hints_bar_height = *data;
                     delete data;
                  } break;

                  case ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR: {
                     std::vector<std::string> *data = (std::vector<std::string> *)this_event.user.data1;
                     set_input_hints_tokens(*data);
                     delete data;
                  } break;

                  case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP: {
                     int player_num = this_event.user.data1;
                     int button_num = this_event.user.data2;
                     bool is_repeat = this_event.user.data3;
                      //screens.virtual_control_button_up_funcs(&this_event);
                     screens.virtual_control_button_up_funcs(player_num, button_num, is_repeat);
                  } break;

                  case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
                     {
                        int player_num = this_event.user.data1;
                        int button_num = this_event.user.data2;
                        bool is_repeat = this_event.user.data3;
                        //screens.virtual_control_button_down_funcs(&this_event);
                        screens.virtual_control_button_down_funcs(player_num, button_num, is_repeat);
                     }
                  break;

                  case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE:
                    // TODO: extract more relevant data and inject into this function
                    // HERE:
                    //int player_num = this_event.user.data1;
                    //int button_num = this_event.user.data2;
                    //bool is_repeat = this_event.user.data3;
                    //screens.virtual_control_button_down_funcs(&this_event);
                    //screens.virtual_control_button_down_funcs(player_num, button_num, is_repeat);

                    screens.virtual_control_axis_change_funcs(&this_event);
                  break;

                  case ALLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK:
                    {
                       std::string *data = (std::string *)this_event.user.data1;
                       if (!data)
                       {
                          // TODO: add an error message
                          std::cout << "[AllegroFlare::Frameworks::Full::run_loop]: ERROR: music track data is nullptr."
                                    << std::endl;
                       }
                       else
                       {
                          std::cout << "[AllegroFlare::Frameworks::Full::run_loop]: INFO: playing music track identifer"
                                    << " \"" << (*data) << "\""
                                    << std::endl;
                          audio_controller.play_music_track(*data);
                          delete data;
                       }
                    }
                  break;

                  case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
                    {
                       std::string *data = (std::string *)this_event.user.data1;
                       if (!data)
                       {
                          // TODO: add an error message
                       }
                       else
                       {
                          audio_controller.play_sound_effect(*data);
                          delete data;
                       }
                    }
                  break;

                  case ALLEGRO_FLARE_EVENT_STOP_ALL_MUSIC_TRACKS:
                    {
                       audio_controller.stop_all_music_tracks();
                    }
                  break;

                  case ALLEGRO_FLARE_EVENT_POST_ACHIEVEMENT_UNLOCKED_NOTIFICATION:
                    {
                       // TODO: handle other types of notifications and pass data on event
                       std::string *data = (std::string *)this_event.user.data1;
                       if (!data)
                       {
                          // TODO: add an error message
                       }
                       else
                       {
                          AllegroFlare::NotificationsFactory notifications_factory;
                          notifications.add(
                             notifications_factory.create_achievement_unlocked_notification(*data)
                          );
                          delete data;
                       }
                    }
                  break;

                  case ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED:
                     {
                        AllegroFlare::Achievement *data = (AllegroFlare::Achievement *)this_event.user.data1;
                        if (!data)
                        {
                           // TODO: add an error message
                        }
                        else
                        {
                           std::string achievement_title = data->get_title();
                           event_emitter.emit_post_unlocked_achievement_notification_event(achievement_title);
                           // delete data; // NOTE: do NOT delete the data here
                        }
                     }
                  break;

                  case ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT:
                     {
                        std::string *data = (std::string *)this_event.user.data1;
                        if (!data)
                        {
                           // TODO: add an error message
                        }
                        else
                        {
                           achievements.unlock_manually(*data);
                           //audio_controller.play_music_track_by_identifier(*data);
                           delete data;
                        }
                     }
                  break;

                  case ALLEGRO_FLARE_EVENT_SWITCH_SCREEN:
                     {
                        std::string *data = (std::string *)this_event.user.data1;
                        if (!data)
                        {
                           // TODO: add an error message
                        }
                        else
                        {
                           screens.activate(*data);
                           //achievements.unlock_manually(*data);
                           //audio_controller.play_music_track_by_identifier(*data);
                           delete data;
                        }
                     }
                    //screens.activate();
                  break;

                  case ALLEGRO_FLARE_EVENT_START_NEW_GAME:
                     {
                        AllegroFlare::GameEvent start_new_game_event("start_new_game");
                        event_emitter.emit_game_event(start_new_game_event);
                     }
                  break;

                  case ALLEGRO_FLARE_EVENT_EXIT_GAME:
                     shutdown_program = true;
                  break;

                  case ALLEGRO_FLARE_EVENT_GAME_EVENT:
                     {
                        AllegroFlare::GameEvent *data =
                           static_cast<AllegroFlare::GameEvent *>((void *)this_event.user.data1);
                        if (!data)
                        {
                           // TODO: add an error message
                        }
                        else
                        {
                           screens.game_event_funcs(data);
                           //achievements.unlock_manually(*data);
                           //audio_controller.play_music_track_by_identifier(*data);
                           delete data;
                        }
                     }
                  break;

                  default:
                     screens.user_event_funcs(&this_event);
                  break;
               }
            }
            else
            {
               //screens.user_event_funcs(&this_event);
            }
         }
         else
         {
            std::cout << "uncaught event [" << this_event.type << "]" << std::endl;
         }
         break;
      }
}


int Full::process_events_in_queue()
{
   int count = 0;
   ALLEGRO_EVENT this_event;
   while (al_get_next_event(event_queue, &this_event))
   {
      count++;
      primary_process_event(&this_event);
   }
   return count;
}


void Full::run_loop(float auto_shutdown_after_seconds)
{
   al_wait_for_vsync();
   al_start_timer(primary_timer);
   event_emitter.emit_game_event(AllegroFlare::GameEvent("initialize"));
   float loop_started_at = al_get_time();

   while(!shutdown_program || Display::displays.empty())
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      current_event = &this_event;
      time_now = this_event.any.timestamp;
      //motions.update(time_now); // this was here, and has been moved to below the ALLEGRO_EVENT_TIMER event

      primary_process_event(current_event);

      // shutdown the program if an autoshutdown time has been defined.
      if (auto_shutdown_after_seconds > 0 && (time_now - loop_started_at) > auto_shutdown_after_seconds)
      {
         shutdown_program = true;
      }
   }

   al_stop_timer(primary_timer);
}


std::string Full::get_allegro_version_string()
{
   AllegroFlare::Version version;
   return version.get_allegro_version_string();
}


std::string Full::get_allegro_flare_version_string()
{
   AllegroFlare::Version version;
   return version.get_allegro_flare_version_string();
}



void Full::draw_overlay()
{
   profiler.start(".draw_overlay()");

   // TODO: do a full audit of render flags that should be restored in addition to setting the 
   // display_backbuffer_sub_bitmap
   display_backbuffer_sub_bitmap.set_as_target();
   al_use_shader(NULL); // TODO: consider side-effects of this

   if (drawing_inputs_bar_overlay)
   {
      //if (!input_hints_tokens.empty() || show_input_hints_bar_when_empty) // this feature has not been requested
      {
         AllegroFlare::InputHints input_hints(&fonts);
         ALLEGRO_COLOR text_color = input_hints_text_color;
         ALLEGRO_COLOR backfill_color = input_hints_backfill_color;
         text_color.r *= input_hints_text_opacity;
         text_color.g *= input_hints_text_opacity;
         text_color.b *= input_hints_text_opacity;
         text_color.a *= input_hints_text_opacity;
         backfill_color.r *= input_hints_backfill_opacity;
         backfill_color.g *= input_hints_backfill_opacity;
         backfill_color.b *= input_hints_backfill_opacity;
         backfill_color.a *= input_hints_backfill_opacity;
         input_hints.set_keyboard_key_combo_tokens(input_hints_tokens);
         input_hints.set_text_color(text_color);
         input_hints.set_backfill_color(backfill_color);
         input_hints.set_bar_height(input_hints_bar_height);
         input_hints.render();
      }
   }

   if (drawing_notifications)
   {
      float num_seconds_to_show_notifications = 6.0f;
      float min_created_at_notification_to_show = al_get_time() - num_seconds_to_show_notifications;

      std::vector<AllegroFlare::Elements::Notifications::Base*> notifications_to_render =
         notifications.select_created_at_since_order_by_created_at(min_created_at_notification_to_show);
      AllegroFlare::Elements::NotificationsRenderer notifications_renderer(&bitmaps, &fonts, notifications_to_render);
      notifications_renderer.render();
   }

   profiler.stop(".draw_overlay()");

   if (drawing_profiler_graph)
   {
      //int previous_profiler_rendering_duration_msec = profiler_rendering_timer.get_elapsed_time_milliseconds();

      //profiler_rendering_timer.start();


      // TODO: include Profiler "draw" as a metric in the graph, add a bool allowing "hiding" it.
      // TODO: include this "previous_profiler_rendering_duration_msec" in the render
      //int previous_profiler_rendering_duration_msec = profiler_rendering_timer.get_elapsed_time_milliseconds();

      //profiler_rendering_timer.start();

      //AllegroFlare::ProfilerRenderer profiler_renderer;
      //profiler_renderer.set_timers(&timers);
      //profiler_renderer.render();

      //profiler_rendering_timer.stop();



      AllegroFlare::ProfilerRenderer profiler_renderer(&fonts);
      profiler_renderer.set_timers(&profiler.get_timers_ref());
      profiler_renderer.render();

      //profiler_rendering_timer.stop();
   }


      //profiler.draw(0, 0, obtain_profiler_graph_font());
   //}
}



void Full::set_input_hints_tokens(std::vector<std::string> input_hints_tokens)
{
   this->input_hints_tokens = input_hints_tokens;
}



void Full::clear_input_hints_tokens()
{
   set_input_hints_tokens({});
}



std::vector<std::string> Full::get_input_hints_tokens()
{
   return input_hints_tokens;
}



float Full::get_input_hints_text_opacity()
{
   return input_hints_text_opacity;
}


float Full::get_input_hints_backfill_opacity()
{
   return input_hints_backfill_opacity;
}



void Full::open_log_window()
{
   if (textlog) return;

   textlog = al_open_native_text_log("Log", ALLEGRO_TEXTLOG_MONOSPACE);
   al_register_event_source(event_queue, al_get_native_text_log_event_source(textlog));
}


void Full::close_log_window()
{
   if (!textlog) return;

   al_unregister_event_source(event_queue, al_get_native_text_log_event_source(textlog));
   textlog = NULL;
}


void Full::log(std::string message)
{
   if (!textlog) return;
   al_append_native_text_log(textlog, message.c_str());
}


uint32_t Full::register_event_callback(std::function<void(ALLEGRO_EVENT*, void*)> callback, void* user_data)
{
   uint32_t this_next_event_callback_id = next_event_callback_id;

   event_callbacks.insert({
      this_next_event_callback_id,
      { callback, user_data }
   });

   next_event_callback_id++;
   return this_next_event_callback_id;
}


bool Full::unregister_event_callback(uint32_t id)
{
   if (event_callbacks.count(id) == 0) return false;
   event_callbacks.erase(id);
   return true;
}


void Full::draw_no_active_screens_text()
{
   if (!primary_display) return;
   int surface_width = 1920; //al_get_display_height();
   int surface_height = 1080; // al_get_display_height(primary_height);
   ALLEGRO_FONT *font = obtain_system_text_font_medium();
   int font_height = al_get_font_line_height(font);

   al_draw_text(
      font,
      ALLEGRO_COLOR{0.4, 0.4, 0.4, 0.4},
      surface_width/2,
      surface_height/2 - font_height/2,
      ALLEGRO_ALIGN_CENTER,
      "There are currently no active screens"
   );
}


ALLEGRO_FONT *Full::obtain_profiler_graph_font()
{
   return fonts.auto_get("Inter-Medium.ttf -22");
}


ALLEGRO_FONT *Full::obtain_system_text_font_medium()
{
   //return fonts.auto_get("system");
   return fonts.auto_get("Inter-Medium.ttf -32");
}


} // namespace Frameworks
} // namespace AllegroFlare


