



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
#include <AllegroFlare/ProfilerRenderer.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData.hpp>
#include <AllegroFlare/Routers/Base.hpp>
//#include <AllegroFlare/Routers/Standard.hpp>
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>
#include <AllegroFlare/Instrumentation/PrimaryProcessEventMetric.hpp>
#include <AllegroFlare/DisplaySettingsInterfaces/Live.hpp>
#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>
#include <AllegroFlare/SystemInfo.hpp>



// TODO: Move this to Frameworks::Full instance variable, and make configurable and 
static std::string LOG_FILENAME = "flare_log.txt";


namespace AllegroFlare
{
namespace Frameworks
{


Full::Full()
   //: logger_instance()
   : screens()
   , initialized(false)
   , config(DEFAULT_CONFIG_FILENAME)
   , profiler()
   , fonts()
   , samples()
   , bitmaps()
   , icon_bin()
   , models()
   , video_bin()
   , asset_studio_database()
   , asset_studio_bitmap_bin()
   , motions(200)
   , audio_controller(&samples)
   , event_emitter()
   , achievements()
   , notifications()
   , dialog_system()
   , input_devices_list()
   , virtual_controls_processor()
   , router(nullptr)
   , textlog(nullptr)
   , initial_target_fps(60)
   , render_surface_multisamples(0) // Used to be 4
   , render_surface_depth_size(32)
   , render_surface_adapter(-1)
   , primary_display(nullptr)
   , primary_display_icon_image_identifier("allegro-flare-generic-icon-1024.png")
   //, primary_display_sub_bitmap_for_overlay(nullptr)
   //, high_frequency_timer(nullptr)
   , camera_2d()
   , showing_dialog_switched_in_debug_text(false)
   , variable_time_stepper()
   , display_backbuffer()
   , display_backbuffer_sub_bitmap()
   , primary_render_surface(nullptr)
   , post_processing_shader(nullptr)
   //, flip_sync()
   , sync_oracle()
   , using_instrumentation(false)
   , drawing_inputs_bar_overlay(false)
   , drawing_notifications(true)
   , drawing_dialogs(true)
   , input_hints_tokens({})
   , display_close_will_shutdown(true)
   , escape_key_will_shutdown(true)
   , output_auto_created_config_warning(true)
   , set_primary_render_surface_as_target_before_calling_primary_timer_funcs(true)
   , clear_render_surface_before_calling_primary_timer_funcs(true) // TODO: I think this should be false by default
                                                                   // for performance reasons
   //, using_display_backbuffer_as_primary_render_surface(true)
   , using_display_backbuffer_as_primary_render_surface(false)
   , input_hints_text_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , input_hints_text_opacity(0.4)
   , input_hints_backfill_color(ALLEGRO_COLOR{0, 0, 0, 0})
   , input_hints_backfill_opacity(0.35)
   , input_hints_bar_height(60)
   , fullscreen(true)
   , log_file_is_disabled(true)
   , mipmapping(true)
   , deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_UNDEF)
   , unset_deployment_environment_warning_on_initialization_is_disabled(false)
   , shader_source_poller()
   , shader_target_for_hotloading(nullptr)
   , display_settings_interface(nullptr)
   //, gameplay_screen(nullptr)
   , draw(false)
   , drain_sequential_timer_events(true)
   , event_callbacks()
   , next_event_callback_id(1)
   , event_queue(nullptr)
   , shutdown_program(false)
   , current_screen(nullptr)
   , current_event(nullptr)
   //, primary_time()
   , time_now(0)
   , key_alt(0)
   , key_shift(0)
   , key_ctrl(0)
   , key_command(0)
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


VideoBin &Full::get_video_bin_ref()
{
   return video_bin;
}


AllegroFlare::AssetStudio::Database &Full::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


ScreenManagers::Dictionary &Full::get_screen_manager_ref()
{
   return screens;
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


AllegroFlare::Routers::Base *Full::get_router()
{
   return router;
}


void Full::set_router(AllegroFlare::Routers::Base *router)
{
   this->router = router;
}


Display *Full::get_primary_display()
{
   return primary_display;
}


void Full::set_primary_display_icon_image_identifier(std::string image_identifier)
{
   primary_display_icon_image_identifier = image_identifier;
   refresh_display_icon();
}


void Full::refresh_display_icon()
{
   // TODO: Sort out this issue where bitmaps[] is looking in bin/data/bitmaps, needs bin/data/icons
   if (primary_display)
   {
      ALLEGRO_BITMAP *icon = icon_bin[primary_display_icon_image_identifier];
      // TODO: Consider using al_set_display_icons (plural)
      // TODO: Look into if this fulfills icon for window frame, taskbar, alt-tab popup, etc
      al_set_display_icon(primary_display->al_display, icon);
   }
}


bool Full::initialize_core_system()
{
   if (initialized) return false; // TODO: Throw here if already initialized


   // TODO: throw if alt, shift, command, or ctrl are pressed, or capture initial keyboard state and
   // set the values for these to correct values. E.g. A game system is setup to count-capture presses and unpresses
   // of keys, but has at startup when a key pressed, will only capture the unpress and thus noise
   

   //AllegroFlare::Logger::set_instance(&logger_instance);

   //if (!log_file_is_disabled)
   //{
      //logger_instance.set_log_filename(LOG_FILENAME);
      //logger_instance.initialize_log_file();
      //AllegroFlare::Logger::info_from(
            //"AllegroFlare::Frameworks::Full::",
            //"Initialized AllegroFlare::Logger to \"" + LOG_FILENAME + "\""
         //);
   //}



   //bool using_instrumentation = true;
   //if (using_instrumentation)
   //{
      //logger_instance.initialize_instrumentation_log_file();
      //AllegroFlare::Logger::initialize_instrumentation_log_file();
      //AllegroFlare::Logger::initialize_instrumentation_log_file(&logger_instance);
   //}


   if (!al_init())
   {
      // TODO: Improve this log message
      std::cerr << "al_init() failed" << std::endl;
   }


   // Setup our deployment environment and working directory

   if (deployment_environment.is_undefined())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Frameworks::Full::initialize_core_system",
         "The current deployment environment has not been defined. Before calling "
            "AllegroFlare::Frameworks::Full::initialize(), be sure to set a deployment environment with "
            "AllegroFlare::Frameworks::Full::set_deployment_environment(). In the mean time, the environemnt will "
            "automatically be set to ENVIRONMENT_DEVELOPMENT. Alternatively, ou can also disable this warning message "
            "with AllegroFlare::Frameworks::Full::disable_unset_deployment_environment_warning_on_initialization()."
      );
      deployment_environment.set_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT);
   }

   deployment_environment.setup_current_working_directory();



   // Initialize Allegro's various parts

   // TODO: Throw on these errors instead of output to std::cerr
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
   if (!al_init_video_addon()) std::cerr << "al_init_video_addon() failed" << std::endl;

   if (!al_reserve_samples(32)) std::cerr << "al_reserve_samples() failed" << std::endl;


   // Setup our preferred objects & settings

   srand(time(NULL));

   //primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   //high_frequency_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60 * 16)); // TODO: Look into if this is reasonable

   if (mipmapping) al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   bool force_video_bitmaps_only = true;
   if (force_video_bitmaps_only)
   {
      // This flag is set so that all bitmaps ever created are video bitmaps.
      al_set_new_bitmap_flags(al_get_new_bitmap_flags() | ALLEGRO_VIDEO_BITMAP);
   }


   event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_joystick_event_source());
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_default_menu_event_source());
   //al_register_event_source(event_queue, al_get_timer_event_source(high_frequency_timer));


   // Register our higher level objects

   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // Setup our experimental live-polling of shader source code tool
   if (!deployment_environment.is_production()) // TODO: figure out what environment(s) are reasonable for
                                                // this hotloading feature
   {
      //std::string live_source_code_for_fragment_shader = "tmp/live_fragment.glsl";
      //std::string live_source_code_for_vertex_shader = "tmp/live_vertex.glsl";
      //shader_source_poller.set_path("/Users/markoates/Repos/allegro_flare/");
      //shader_source_poller.set_event_queue(event_queue);
      //shader_source_poller.set_fragment_source_filename(live_source_code_for_fragment_shader);
      //shader_source_poller.set_vertex_source_filename(live_source_code_for_vertex_shader);
      //shader_source_poller.initialize();
      //shader_source_poller.start_polling();
   }

   // Setup the paths for our asset bins
   std::string data_folder_path = deployment_environment.get_data_folder_path();
   fonts.set_path(data_folder_path + "fonts");
   samples.set_path(data_folder_path + "samples");
   bitmaps.set_path(data_folder_path + "bitmaps");
   icon_bin.set_path(data_folder_path + "icons");
   models.set_path(data_folder_path + "models");
   video_bin.set_path(data_folder_path + "videos");




   // NOTE: Asset Studio was previously loaded here, and now is loaded after the display is created




   // Add our config (which is currently unused)
   config.load_or_create_empty(output_auto_created_config_warning);

   // Declare an ALLEGRO_COLOR custom attribute in Attributes
   // TODO: Look into the ramifications of this being a stat property on the class
   Attributes::create_datatype_definition(
      AllegroColorAttributeDatatype::IDENTIFIER,
      AllegroColorAttributeDatatype::to_val_func,
      AllegroColorAttributeDatatype::to_str_func
   );

   // Setup our screens, TODO: Consider an initializtion scheme
   screens.set_event_emitter(&event_emitter);

   // Initialize our AudioController
   audio_controller.initialize();

   // Initialize our InputDeviceList
   input_devices_list.initialize();

   // Initialize our VirtualControlsProcessor
   virtual_controls_processor.set_input_devices_list(&input_devices_list);
   virtual_controls_processor.set_event_emitter(&event_emitter);
   virtual_controls_processor.initialize();

   // Initialize our Achievements
   achievements.set_event_emitter(&event_emitter);

   // Initialize the DialogSystem::DialogSystem
   dialog_system.set_bitmap_bin(&bitmaps);
   dialog_system.set_font_bin(&fonts);
   dialog_system.set_event_emitter(&event_emitter);
   dialog_system.initialize();

   // Create a dialog system driver for use by default
   // TODO: Consider how this should be destroyed if a different driver is used in its place

//static AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *create_driver(AllegroFlare::BitmapBin *bitmap_bin)
//{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *dialog_driver =
         new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();
   dialog_driver->set_bitmap_bin(&bitmaps);
   dialog_driver->initialize();
   set_dialog_system_driver(dialog_driver);

      //if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      //{
         //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         //driver->destroy();
         ////driver->initialize();
      //}
   //return driver;
//}
   //flip_sync.initialize();


   //sync_oracle.set_display(display);
   //sync_oracle.set_target_fps(60);
   //sync_oracle.set_primary_event_queue(primary_event_queue);
   //sync_oracle.activate_hyper_timer();
   //sync_oracle.activate_auto_nudge();
   //sync_oracle.initialize();


   // Create a Router
   //router = new AllegroFlare::Routers::Standard;
   //router->set_event_emitter(&event_emitter);
   //router->set_framework(this);

   // Finalize initialization
   initialized = true;

   return true;
}



void Full::initialize_asset_studio_database()
{
   // NOTE: Asset studio will need to be setup *after* the display, otherwise the assets will be loaded as
   // ALLEGRO_MEMORY_BITMAPs, which can result in awkward rendering results, particularly in 3d transformations.

 

   // Asset Studio
   // Set the path for the asset_studio. If not in production, use the global resource. Assets should be copied out
   // of the global resource at production-time. SourceReleaser should validate there are no global resource-referenced
   // assets.

   std::string data_folder_path = get_data_folder_path();
   std::string ASSETS_DB_CSV_FILENAME = "assets_db.csv";
   int sprite_sheet_scale = 3;

   // Load the local AssetStudio assets
   {
      std::string local_assets_full_path = data_folder_path + "assets/";
      asset_studio_bitmap_bin.set_path(local_assets_full_path);
      AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
      //loader.set_assets_bitmap_bin(&asset_studio_bitmap_bin);
      //loader.set_sprite_sheet_scale(sprite_sheet_scale);
      loader.set_csv_full_path(local_assets_full_path + ASSETS_DB_CSV_FILENAME);
      if (!loader.csv_file_exists())
      {
         std::string filename = local_assets_full_path + ASSETS_DB_CSV_FILENAME;
         AllegroFlare::Logger::warn_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "The expected assets_db file \"" + filename + "\" is not present. If this is expected, please ignore this "
               "message. TODO: Allow this warning to be hidden with an optional flag."
         );
      }
      else
      {
         loader.load_records();
         asset_studio_database.set_local_records(loader.get_records());
         asset_studio_database.set_assets_bitmap_bin(&asset_studio_bitmap_bin);
         asset_studio_database.set_sprite_sheet_scale(sprite_sheet_scale);

         AllegroFlare::Logger::info_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "Creating local AssetStudio assets..."
         );

         asset_studio_database.load_all_local_assets_from_all_local_records();

         AllegroFlare::Logger::info_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "Local AssetStudio assets loading finished."
         );
      }

      // Can the bitmap_bin be cleared here?
   }

   // Load the global AssetStudio assets
   bool using_global_assets = !deployment_environment.is_production();
   if (using_global_assets)
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
         "Loading global AssetStudio records..."
      );

      AllegroFlare::SystemInfo system_info;
      // DEVELOPER HACK: Depending on the developer system, use different path for the assets_db.csv file
      std::string global_assets_full_path = "/Users/markoates/Assets/"; //data_folder_path + "assets/";
      std::string operating_system = system_info.operating_system();
      if (operating_system == AllegroFlare::SystemInfo::OPERATING_SYSTEM_WINDOWS_32_BIT
         || operating_system == AllegroFlare::SystemInfo::OPERATING_SYSTEM_WINDOWS_64_BIT
         )
      {
         global_assets_full_path = "/msys64/home/Mark/Assets/";
      }

      //assets_full_path = "/Users/markoates/Assets/"; //data_folder_path + "assets/";
      asset_studio_bitmap_bin.set_full_path(global_assets_full_path);
      AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
      //loader.set_assets_bitmap_bin(&asset_studio_bitmap_bin);
      //loader.set_sprite_sheet_scale(sprite_sheet_scale);
      loader.set_csv_full_path(global_assets_full_path + ASSETS_DB_CSV_FILENAME);

      if (!loader.csv_file_exists())
      {
         std::string filename = global_assets_full_path + ASSETS_DB_CSV_FILENAME;
         AllegroFlare::Logger::warn_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "The expected assets_db file \"" + filename + "\" is not present. If this is expected, please ignore this "
               "message. TODO: Allow this warning to be hidden with an optional flag."
         );
      }
      else
      {
         loader.load_records();
         asset_studio_database.set_global_records(loader.get_records());
         asset_studio_database.set_assets_bitmap_bin(&asset_studio_bitmap_bin);
         asset_studio_database.set_sprite_sheet_scale(sprite_sheet_scale);

         AllegroFlare::Logger::info_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "Loading global AssetStudio assets..."
         );

         asset_studio_database.load_all_global_assets_from_all_global_records();

         asset_studio_bitmap_bin.set_full_path(global_assets_full_path);
         asset_studio_database.set_global_identifier_prefix(
               AllegroFlare::AssetStudio::Database::DEFAULT_GLOBAL_IDENTIFIER_PREFIX
            );

         AllegroFlare::Logger::info_from(
            "AllegroFlare::Frameworks::Full::initialize_asset_studio_database",
            "global AssetStudio assets loading finished."
         );
      }


      //loader.load();

      //asset_studio_database.set_global_assets(loader.get_assets());
      ////assets_full_path = "/Users/markoates/Assets/";
      //asset_studio_bitmap_bin.set_full_path(global_assets_full_path);
      //asset_studio_database.set_global_identifier_prefix(
            //AllegroFlare::AssetStudio::Database::DEFAULT_GLOBAL_IDENTIFIER_PREFIX
         //);

      //AllegroFlare::Logger::info_from(
         //"AllegroFlare::Frameworks::Full::initialize_core_system",
         //"Global AssetStudio assets loading finished."
      //);

      // Can the bitmap_bin be cleared here?
   }
}



bool Full::initialize_display_and_render_pipeline()
{
   // TODO: validate size of display before creating a window that is potentially larger than the display. If so,
   // output a warning.  This issue occurred on Linux on a display that could not support 1920x1080


   // Create our primary display

   if (primary_display)
   {
      // TODO: Add better "double initialization" error here
      throw std::runtime_error("AllegroFlare/Frameworks/Full:: odd error expecting uninit value");
   }


   int display_width = config.get_or_default_int("display", "width", DEFAULT_DISPLAY_WIDTH);
   int display_height = config.get_or_default_int("display", "height", DEFAULT_DISPLAY_HEIGHT);
   fullscreen = config.get_or_default_bool("display", "fullscreen", fullscreen);
   bool resizable_with_mouse = config.get_or_default_bool(
         "display",
         "resizable_with_mouse", 
         DEFAULT_DISPLAY_RESIZABLE_WITH_MOUSE 
      );
   //bool resizable = true;


   // Setup the display
   primary_display = new Display(
      display_width,
      display_height,
      0, // legacy argument is depreciated
      render_surface_multisamples,
      render_surface_depth_size,
      render_surface_adapter,
      fullscreen,
      resizable_with_mouse
   );

   if (!primary_display)
   {
      throw std::runtime_error("[Frameworks::Full::initialize_display_and_render_pipeline]: FAILURE: unable to create "
                               "primary_display.");
   }

   primary_display->initialize();

   if (!primary_display->al_display)
   {
      throw std::runtime_error("[Frameworks::Full::initialize_display_and_render_pipeline]: FAILURE: When initializing "
                               "the primary_display, was unable to create an al_display.");
   }


   // Refresh the display icon
   refresh_display_icon();


   // Setup the display settings interface
   display_settings_interface = new AllegroFlare::DisplaySettingsInterfaces::Live(primary_display->al_display);

   // NOTE: Fullscreen may have failed. At this point in the initialization, the "fulscreen" member variable only
   // represents the preferred option at startup, not the actual fullscreen state.

   // Initialized the preferred settings with the display and display_settings_interface
   // Hide the mouse cursor by default (when in fullscreen)
   if (fullscreen)
   {
      // Hide the mouse cursor
      display_settings_interface->hide_mouse_cursor();
   }

   // Inhibit the screensaver by default
   // TODO: Consider disabling this option as a config
   display_settings_interface->enable_inhibit_screensaver();

  

   // Register our display with the event_queue

   al_register_event_source(event_queue, al_get_display_event_source(primary_display->al_display));


   // Setup our graphics pipeline

   display_backbuffer.set_display(primary_display->al_display);
   display_backbuffer.initialize();

   camera_2d.setup_dimensional_projection(display_backbuffer.get_display_backbuffer());
                                                              // ^^ NOTE: this could potentially change depending on the
                                                              // needs of the game, but is setup here as a reasonable
                                                              // default

   //using_display_backbuffer_as_primary_render_surface = false;
   if (using_display_backbuffer_as_primary_render_surface)
   {
      // use the display_backbuffer as our render surface
      primary_render_surface = &display_backbuffer;
   }
   else
   {
      std::cout << "Setting up a bitmap buffer as a primary render surface" << std::endl;
      // TODO: Implement this new reality please!
      AllegroFlare::RenderSurfaces::Bitmap *bitmap_render_surface = new AllegroFlare::RenderSurfaces::Bitmap();

      bitmap_render_surface->setup_surface_with_settings_that_match_display(primary_display->al_display, 1920, 1080);
      bitmap_render_surface->initialize();

      primary_render_surface = bitmap_render_surface;
      std::cout << "Now using RenderSurfaces::Bitmap as a primary render surface" << std::endl;
   }


   // Initialize our backbuffer sub bitmap that is used to display AllegroFlare overlay, like performance graphs,
   // in-game notificatoins, etc.
   display_backbuffer_sub_bitmap.set_display(primary_display->al_display);
   display_backbuffer_sub_bitmap.initialize();
   camera_2d.setup_dimensional_projection(display_backbuffer_sub_bitmap.get_display_backbuffer_sub_bitmap());
                                                               // this should remain the same throughout
                                                               // the whole program and never be modified



   return true;
}



void Full::set_initial_target_fps(int initial_target_fps)
{
   if (initial_target_fps <= 0 || initial_target_fps > 240)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::set_initial_target_fps",
         "initial_target_fps cannot be <= 0 or > 240" // 240 is only for sanity, it could work in theory.
      );
   }

   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::set_initial_target_fps",
         "Could not set because the framework has already been initialized. You must call this function before init."
      );
   }

   this->initial_target_fps = initial_target_fps;
}



int Full::get_initial_target_fps()
{
   return initial_target_fps;
}



void Full::set_render_surface_multisamples(int render_surface_multisamples)
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::set_render_surface_multisamples",
         "Could not set because the framework has already been initialized. You must call this function before init."
      );
   }

   this->render_surface_multisamples = render_surface_multisamples;
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



void Full::set_shader_target_for_hotloading(AllegroFlare::Shaders::Base *shader_target_for_hotloading)
{
   this->shader_target_for_hotloading = shader_target_for_hotloading;
}



AllegroFlare::Shaders::Base *Full::get_shader_target_for_hotloading()
{
   return shader_target_for_hotloading;
}



void Full::initialize_sync_oracle()
{
   sync_oracle.set_display(primary_display->al_display);
   sync_oracle.set_target_fps(initial_target_fps);
   sync_oracle.set_primary_event_queue(event_queue);
   sync_oracle.initialize();

}



bool Full::initialize()
{
   if (initialized) return false;

   initialize_core_system();
   initialize_display_and_render_pipeline();
   initialize_asset_studio_database();
   initialize_sync_oracle();

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
   if (!initialized)
   {
      fullscreen = false;
   }
}


void Full::enable_log_file()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::enable_log_file",
         "Could not enable because the framework has already been initialized. "
            "You must call this function before initializing the framework for it to take effect."
      );
   }
   log_file_is_disabled = false;
}


void Full::disable_log_file()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Frameworks::Full::disable_log_file",
         "Could not disable because the framework has already been initialized. "
            "You must call this function before initializing the framework for it to take effect."
      );
   }
   log_file_is_disabled = true;
}


void Full::disable_mipmapping()
{
   if (initialized)
   {
      std::cout << "[AllegroFlare::Frameworks::Full::disable_mipmapping]: WARNING: "
                << "could not disable because the framework has already been initialized.  "
                << "For now, you must disable the mipmapping before initializing the framework for it to take effect."
                << std::endl;
   }
   if (!initialized) mipmapping = false;
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
   // NOTE: This condition below was removed, but 
   //if (!initialized)
   //{
      //AllegroFlare::Logger::throw_error(
         //"AllegroFlare::Frameworks::Full::get_data_folder_path",
         //"Could retrieve because the framework has not yet been initialized. "
            //"You must call this function after initialization so the path has been has been properly set."
      //);
   //}

   return deployment_environment.get_data_folder_path();
}



void Full::set_window_size(int width, int height)
{
   display_settings_interface->set_window_size(width, height);
   return;

   if (fullscreen)
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Frameworks::Full::set_window_size",
         "Cannot set the display size while in FULLSCREEN_WINDOW"
      );
   }
   else
   {
      bool resize_was_successful = al_resize_display(primary_display->al_display, width, height);
      if (!resize_was_successful)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Frameworks::Full::set_window_size",
            "Allegro returned false while trying to resize the display."
         );
      }
   }
}



void Full::set_display_to_fullscreen()
{
   display_settings_interface->activate_fullscreen();
   return;
   // TODO: Double check the guards on this
   if (!initialized) throw std::runtime_error("set_display_to_fullscreen: must_be_initialized");
   if (fullscreen) return;

   bool successful = al_set_display_flag(primary_display->al_display, ALLEGRO_FULLSCREEN_WINDOW, true);
   if (!successful)
   {
      throw std::runtime_error("(error 62e1c2): setting ALLEGRO_FULLSCREEN_WINDOW unsuccessful (not supported).");
   }

   bool is_actually_fullscreen = al_get_display_flags(primary_display->al_display) & ALLEGRO_FULLSCREEN_WINDOW;
   if (!is_actually_fullscreen)
   {
      throw std::runtime_error("(error 782fa8): ALLEGRO_FULLSCREEN_WINDOW was not actually set.");
   }

   bool mouse_hidden = al_hide_mouse_cursor(primary_display->al_display);
   if (!mouse_hidden)
   {
      throw std::runtime_error("(error xcb6bx): al_hide_mouse_cursor returned false.");
   }

   fullscreen = true;
}



void Full::set_display_to_windowed()
{
   display_settings_interface->deactivate_fullscreen();
   return;
   // TODO: Double check the guards on this
   if (!initialized) throw std::runtime_error("set_display_to_windowed: must_be_initialized");
   if (!fullscreen) return;

   bool successful = al_set_display_flag(primary_display->al_display, ALLEGRO_FULLSCREEN_WINDOW, false);
   if (!successful)
   {
      throw std::runtime_error("(error 62x1x2): setting ALLEGRO_FULLSCREEN_WINDOW unsuccessful (not supported).");
   }

   bool is_actually_fullscreen = al_get_display_flags(primary_display->al_display) & ALLEGRO_FULLSCREEN_WINDOW;
   if (is_actually_fullscreen)
   {
      throw std::runtime_error("(error 7x2fax): ALLEGRO_FULLSCREEN_WINDOW was not actually set to fullscreen.");
   }

   bool mouse_shown = al_show_mouse_cursor(primary_display->al_display);
   if (!mouse_shown)
   {
      throw std::runtime_error("(error ecb6b8): al_show_mouse_cursor returned false.");
   }
   fullscreen = false;
}



void Full::toggle_display_fullscreen()
{
   display_settings_interface->toggle_fullscreen();
   return;
   // TODO: Double check the guards on this
   if (!initialized) throw std::runtime_error("toggle_display_fullscreen: must_be_initialized");

   if (fullscreen)
   {
      set_display_to_windowed();
   }
   else
   {
      set_display_to_fullscreen();
   }
}


AllegroFlare::DisplaySettingsInterfaces::Base *Full::get_display_settings_interface()
{
   return display_settings_interface;
}



bool Full::shutdown()
{
   if (!initialized) return false;

   // TODO: Consider how to destroy the dialog system driver
   //void destroy_driver(AllegroFlare::DialogSystemDrivers::Base* _driver)
   //{
      //if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      //{
         //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         //driver->destroy();
      //}
      //else
      //{
         //throw std::runtime_error("in test: Could not destroy _driver");
      //}
   //}
   //al_stop_timer(high_frequency_timer);
   //al_unregister_event_source(event_queue, al_get_timer_event_source(high_frequency_timer));
   //al_destroy_timer(high_frequency_timer);
   sync_oracle.shutdown();
   delete display_settings_interface;



   // TODO audit this function
   samples.clear();
   bitmaps.clear();
   icon_bin.clear();
   fonts.clear();
   models.clear();
   video_bin.clear();
   asset_studio_bitmap_bin.clear();

   event_callbacks.clear();

   // TODO: destroy sub-bitmap here on new render surface:
   //if (primary_display_sub_bitmap_for_overlay) al_destroy_bitmap(primary_display_sub_bitmap_for_overlay);
   if (!using_display_backbuffer_as_primary_render_surface)
   {
      al_destroy_bitmap(primary_render_surface->obtain_surface()); // NOTE: this step is required to not crash on Windows.
                                                                   // TODO: please review a better way/place to destroy this
                                                                   // object, possibly in a destruct function on the base
                                                                   // class that is overridden in child classes
   }

   // shutdown the router
   //if (router) delete router; // Consider if this is the correct place to free this resource

   if (primary_display) primary_display->destroy();

   audio_controller.destruct();

   // Shutdown the allegro addons
   al_shutdown_image_addon();
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_shutdown_native_dialog_addon();
   //al_shutdown_acodec_addon(); // not a thing, possibly a bug. Causes some issues with testing
   al_shutdown_video_addon();

   // Uninstall the allegro controlled devices
   al_uninstall_audio();
   al_uninstall_joystick();
   al_uninstall_keyboard();
   al_uninstall_mouse();

   // Restore the directory before start
   deployment_environment.restore_initial_working_directory();


   // TODO:
   // Destroy our list of input devices
   //input_devices_list.destroy();

   // TODO:
   // Destroy any custom types that were created in Attributes
   //Attributes::destroy_all_custom_types()


   //AllegroFlare::Logger::set_instance(nullptr);
   //delete logger_instance;


   al_uninstall_system(); // Note that there is risk of a crash at shutdown if assets have been created outside the
                          // lifecycle of the Framework

   initialized = false;


   //if (using_instrumentation)
   //{
      //logger_instance.close_instrumentation_log_file();
      //AllegroFlare::Logger::initialize_instrumentation_log_file(&logger_instance);
   //}


   //AllegroFlare::Logger::clear_instance();

   //if (!log_file_is_disabled)
   //{
      //logger_instance.close_log_file();
   //}

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


void Full::enable_display_close_will_shutdown()
{
   this->display_close_will_shutdown = true;
}


void Full::disable_display_close_will_shutdown()
{
   this->display_close_will_shutdown = false;
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


void Full::enable_clear_render_surface_before_calling_primary_timer_funcs()
{
   clear_render_surface_before_calling_primary_timer_funcs = true;
}


void Full::disable_clear_render_surface_before_calling_primary_timer_funcs()
{
   clear_render_surface_before_calling_primary_timer_funcs = false;
}


bool Full::is_clear_render_surface_before_calling_primary_timer_funcs_enabled()
{
   return clear_render_surface_before_calling_primary_timer_funcs;
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


void Full::set_dialog_system_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank)
{
   dialog_system.set_dialog_node_bank(dialog_node_bank);
}


void Full::set_dialog_system_driver(AllegroFlare::DialogSystemDrivers::Base *dialog_system_driver)
{
   // TODO: Consider "resetting" consequences when changing the driver mid-flight
   dialog_system.set_driver(dialog_system_driver);
}


DialogSystem::DialogSystem &Full::get_dialog_system_ref()
{
   // TODO: Consider modifying this so that functions are used to access/assign the expected parts of the system
   return dialog_system;
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


//void Full::register_gameplay_screen(std::string name, AllegroFlare::Screens::Gameplay *gameplay_screen)
//{
   //screens.add(name, gameplay_screen);
//}


//void Full::unregister_gameplay_screen(AllegroFlare::Screens::Gameplay *gameplay_screen)
//{
   //screens.remove(gameplay_screen);
//}


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


bool Full::offset_primary_timer(int microseconds)
{
   sync_oracle.nudge_primary_timer_forward();
   //throw std::runtime
   /*
   if (!primary_timer)
   {
      throw std::runtime_error("Frameworks::Full: offset_primary_timer: primary_timer cannot be nullptr");
   }
   if (!al_get_timer_started(primary_timer)) return false;

   // TODO, profile this delay offset and output the actual offset to cout
   // TODO: Improve this cout
   std::cout << "Offsetting timer by " << microseconds << " microseconds." << std::endl;

   double offset_start_time = al_get_time();
   al_stop_timer(primary_timer);
   al_rest(microseconds * 0.000001);
   al_start_timer(primary_timer);
   double offset_stop_time = al_get_time();


   float actual_offset = offset_stop_time - offset_start_time;
   int actual_offset_int = (int)((actual_offset) * 1000000);
   int expected_offset = microseconds;
   int offset_difference = actual_offset_int - expected_offset;

   std::cout << "  Offset processed over " << actual_offset_int << " microseconds ("
             << offset_difference
             << ")." << std::endl;
   */

   return true;
}


void Full::primary_update(double _time_now, double delta_time)
//void Full::primary_update()
{
   // WARNING: "time_now" is a member, so _time_now is used in this scope
   // update
   // TODO: Consider the ordering of this, if events may be emitted or state modified
   //double delta_time = 1.0f; // Not sure what this value should be, should it be the FPS or 1/60 
   screens.primary_update_funcs(time_now, delta_time);
                                     // Game will typically use *either* _timer_funcs on its own OR use the
                                     // _update and _render funcs.
   motions.update(_time_now); // TODO: Update this to use delta time
   achievements.check_all();
   dialog_system.update(_time_now); // TODO: Considr how to update this to use delta_time

   //double delta_time = 1.0f; // Not sure what this value should be, should it be the FPS or 1/60 
   //screens.primary_update_funcs(delta_time); // Game will typically use *either* _timer_funcs on its own OR use the
                                     // _update and _render funcs.
   // TODO: Add screens.primary_update(time_now, deltatime);
}


void Full::primary_time_step(double time_step_increment, double world_time_after_step)
{
   // WARNING: "time_now" is a member, so _time_now is used in this scope
   // update
   // TODO: Consider the ordering of this, if events may be emitted or state modified
   //double delta_time = 1.0f; // Not sure what this value should be, should it be the FPS or 1/60 
   screens.primary_time_step_funcs(time_step_increment, world_time_after_step);
                                     // Game will typically use *either* _timer_funcs on its own OR use the
                                     // _update and _render funcs.
   //motions.update(_time_now); // TODO: Update this to use delta time
   //achievements.check_all();
   //dialog_system.update(_time_now); // TODO: Considr how to update this to use delta_time

   //double delta_time = 1.0f; // Not sure what this value should be, should it be the FPS or 1/60 
   //screens.primary_update_funcs(delta_time); // Game will typically use *either* _timer_funcs on its own OR use the
                                     // _update and _render funcs.
   // TODO: Add screens.primary_update(time_now, deltatime);
}


void Full::render_screens_to_primary_render_surface()
{
   //ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(primary_display->al_display);
   //al_set_target_bitmap(backbuffer_bitmap);
   if (set_primary_render_surface_as_target_before_calling_primary_timer_funcs)
   {
      primary_render_surface->set_as_target();
      if (clear_render_surface_before_calling_primary_timer_funcs) primary_render_surface->clear_surface();

      al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL); // less or equal allows 
                                                                              // subsequent renders at the same
                                                                              // z-level to overwrite. This 
                                                                              // mimics the rendering of typical
                                                                              // traditional 2D drawing behavior
                                                                              // like Illustrator, HTML, etc.
   }

   if (screens.no_active_screens())
   {
      draw_no_active_screens_text();
   }
   else
   {
      screens.primary_timer_funcs(); // Game will typically use *either* _timer_funcs on its own OR use the
                                     // _update and _render funcs.
      screens.primary_render_funcs();
   }




   //camera_2d.setup_dimensional_projection();//display_backbuffer_sub_bitmap.get_display_backbuffer_sub_bitmap());
   primary_render_surface->set_as_target();
   camera_2d.setup_dimensional_projection(al_get_target_bitmap()); // TODO: Look inot if this cleares the
                                                                   // z-buffer or not

         //display_backbuffer_sub_bitmap.get_display_backbuffer_sub_bitmap());
   // Consider resetting/restoring the projection on this surface

   al_use_shader(NULL); // TODO: consider side-effects of this
   draw_overlay(); // NOTE: Default shader and other state restoration flags are handled within the function.


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
      al_use_shader(NULL); // TODO: consider side-effects of this, consider NULL is already set twice prior
                           // before draw_overlay() and within draw_overlay()


      //draw_overlay(); // NOTE: Default shader and other state restoration flags are handled within the function.


      ALLEGRO_BITMAP *bitmap = primary_render_surface->obtain_surface();

      ///* // NOTE: This is a possible technique to always ensure the render surface will be stretched to 
         // fit the display, regardless of its dimensions
         ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());
         int display_natural_width = al_get_bitmap_width(backbuffer);
         int display_natural_height = al_get_bitmap_height(backbuffer);

         ALLEGRO_TRANSFORM transform;
         al_identity_transform(&transform);
         al_orthographic_transform(
            &transform,
            0,
            0,
            -1.0,
            // OPTION A:
               display_natural_width, //al_get_bitmap_width(backbuffer),
               display_natural_height, //al_get_bitmap_height(backbuffer),
            // OPTION B:
               //al_get_bitmap_width(primary_render_surface->obtain_surface()),
               //al_get_bitmap_height(primary_render_surface->obtain_surface()),
            1.0
         );
         al_use_projection_transform(&transform);
      //*/



      // TODO: setup the post-process shader
      // TODO: consider if disabling a depth buffer (or other flags) are needed here
      //if (post_processing_shader) post_processing_shader->activate();

      //al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL); // may want this?
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 0); // may want this?
      //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_RGB); // may want this?
      // previously: al_draw_bitmap(bitmap, 0, 0, 0);
      //int hheight = 
      
      int surface_width = al_get_bitmap_width(bitmap);
      int surface_height = al_get_bitmap_height(bitmap);

      float surface_ar = surface_width / surface_height;
      float x = 140;
      float y = 80;
      //int display_natural_width = al_get_bitmap_width(backbuffer);
      //int display_natural_height = al_get_bitmap_height(backbuffer);


      // Activate the post_processing_shader (if present)
      if (post_processing_shader) post_processing_shader->activate();


      // Build a placement for the render surface. E.g. Setup a placement to stretch the bitmap to fit the entire
      // display. TODO: Consider making the placement customizable.
      AllegroFlare::Placement2D render_surface_placement_on_display;
      render_surface_placement_on_display.position =
            // TODO: Consider if a pixel-friendly coord is preferred here:
            AllegroFlare::Vec2D{ (float)display_natural_width / 2, (float)display_natural_height / 2 }
         ;
      render_surface_placement_on_display.size = AllegroFlare::Vec2D{ (float)surface_width, (float)surface_height };
      render_surface_placement_on_display.scale_to_fit_width_or_height(display_natural_width, display_natural_height);
      
      render_surface_placement_on_display.start_transform();

      /*
      al_draw_scaled_bitmap(
         bitmap, //ALLEGRO_BITMAP *bitmap,
         0, // sx
         0, // sy
         al_get_bitmap_width(bitmap),
         al_get_bitmap_height(bitmap),
         x,
         y,
         display_natural_width,
         display_natural_height,
         //al_get_bitmap_width(backbuffer), //1920, // The final display height, taking into account the projection
         //al_get_bitmap_height(backbuffer), //1080, // The final display width, taking into account the projection
         0
         //float dx, float dy, float dw, float dh, int flags
      );
      */


      // Since we are just plastering this texture to the display backbuffer, we can disable the depth test
      al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
      al_set_render_state(ALLEGRO_ALPHA_TEST, 0);
      al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_RGB); // TODO: may want this?


      // Draw the bitmap
      al_draw_bitmap(bitmap, 0, 0, 0);
      if (post_processing_shader) post_processing_shader->deactivate();


      // TODO: Restore the transform
      render_surface_placement_on_display.restore_transform();


      // Restore the preferred typical render state
      // TODO: Consider if this is needed, also, see if this should be configurable
      al_set_render_state(ALLEGRO_DEPTH_TEST, 1); // may want this?
      al_set_render_state(ALLEGRO_ALPHA_TEST, 1);
      al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA); // may want this?
   }
}


void Full::primary_render()
{
   //profiler.start(".render_screens_to_primary_render_surface()");
   render_screens_to_primary_render_surface();
   //profiler.stop(".render_screens_to_primary_render_surface()");

   //profiler.start(".draw_overlay()");
   //draw_overlay(); // NOTE: Default shader and other state restoration flags are handled within the function.
   //profiler.stop(".draw_overlay()");
   //sync_oracle.end_draw_measure()
}


void Full::primary_flip()
{
   //profiler.start("al_flip_display()");
   //sync_oracle.start_flip_measure(); // ---
   al_flip_display();
   //sync_oracle.end_flip_measure(); // ---
   //profiler.stop("al_flip_display()");
}


void Full::nudge_primary_timer_forward()
{
   //int MICROSECONDS_PER_FRAME = 16670; // TODO: Make this relative to the actual FPS
   //int microseconds_to_offset = MICROSECONDS_PER_FRAME / 10;
   //event_emitter.emit_offset_primary_timer_event(microseconds_to_offset);
}


void Full::nudge_primary_timer_backward()
{
   //int MICROSECONDS_PER_FRAME = 16670; // TODO: Make this relative to the actual FPS
   //int microseconds_to_offset = MICROSECONDS_PER_FRAME - ((MICROSECONDS_PER_FRAME / 10) * 3);
   //event_emitter.emit_offset_primary_timer_event(microseconds_to_offset);
}


void Full::handle_timer_event(ALLEGRO_EVENT *this_event)
{
   bool is_primary_timer_event = sync_oracle.is_primary_timer_event(this_event);

   if (!is_primary_timer_event)
   {
      // TODO: screens.on_timer()?
   }
   else
   {
      double this_event_time = this_event->any.timestamp;
      variable_time_stepper.set_atomic_on_step_func([this](double step, double total, void* ud){
         this->primary_time_step(step, total);
      });
      variable_time_stepper.step_ahead_to(this_event_time);

      sync_oracle.capture_primary_timer_event_time(this_event->any.timestamp);
      draw = true;

   //if (this_event.timer.source == primary_timer)
   //{
      //sync_oracle.start_update_measure();
      //primary_update();
      //sync_oracle.end_update_measure();

      if (drain_sequential_timer_events)
      {
         ALLEGRO_EVENT next_event;
         while (
            al_peek_next_event(event_queue, &next_event)
            && sync_oracle.is_primary_timer_event(&next_event)
            //&& next_event.type == ALLEGRO_EVENT_TIMER
            //&& next_event.timer.source == this_event.timer.source)
            )
         {
            // TODO: Consider that this will offset the timer, possibly leading to intermittent stuttering
            // problems as experienced on some machines.
            al_drop_next_event(event_queue);
            //metric.primary_timer_events_dropped++;
            // HERE: Track when and how often events are dropped and see if there is a correlation 
         }
      }
   }
}


void Full::handle_display_resize_event(ALLEGRO_EVENT *this_event)
{
   std::cout << "Acknowledging resize on display " << this_event->display.source << ": ("
             << "x: " << this_event->display.x
             << ", y: " << this_event->display.y
             << ", w: " << this_event->display.width
             << ", h: " << this_event->display.height
             << ")";
   al_acknowledge_resize(this_event->display.source);
   std::cout << "... done." << std::endl;
}


void Full::handle_user_event(ALLEGRO_EVENT *_this_event)
{
   ALLEGRO_EVENT &this_event = *_this_event;

   if (this_event.any.source == &event_emitter.get_event_source_ref())
   {
      screens.event_emitter_event_funcs(&this_event);

      switch(this_event.type)
      {
         case ALLEGRO_FLARE_EVENT_SET_DISPLAY_SIZE: {
            int width = this_event.user.data1;
            int height = this_event.user.data1;
            set_window_size(width, height);
         } break;

         case ALLEGRO_FLARE_EVENT_TOGGLE_FULLSCREEN: {
            toggle_display_fullscreen();
         } break;

         case ALLEGRO_FLARE_EVENT_ENABLE_FULLSCREEN: {
            // TODO: Test this
            set_display_to_fullscreen();
         } break;

         case ALLEGRO_FLARE_EVENT_DISABLE_FULLSCREEN: {
            // TODO: Test this
            set_display_to_windowed();
         } break;

         case ALLEGRO_FLARE_EVENT_OFFSET_PRIMARY_TIMER: {
            int microseconds = this_event.user.data1;
            offset_primary_timer(microseconds);
         } break;

         case ALLEGRO_FLARE_EVENT_ROUTER: {
            if (!router)
            {
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Frameworks::Full::primary_process_event",
                  "Handling an event of type ALLEGRO_FLARE_EVENT_ROUTER, but no router is present."
               );
            }
            else
            {
               uint32_t route_event = this_event.user.data1;
               AllegroFlare::RouteEventDatas::Base *route_event_data =
                  (AllegroFlare::RouteEventDatas::Base *)this_event.user.data2;
               float *time_now_ptr = (float*)this_event.user.data3;
               router->on_route_event(route_event, route_event_data, *time_now_ptr);
               if (route_event_data) delete route_event_data; // NOTE: RouteEventData is erased here. Consider a different location.
               delete time_now_ptr;
            }
         } break;

         case ALLEGRO_FLARE_EVENT_PAUSE_GAMEPLAY: {
         } break;

         case ALLEGRO_FLARE_EVENT_UNPAUSE_GAMEPLAY: {
         } break;

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
            AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData *event_data =
               static_cast<AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData*>(
                  (void*)this_event.user.data1
               );

            AllegroFlare::Player *player = event_data->get_player();
            AllegroFlare::VirtualControllers::Base *virtual_controller =
               event_data->get_virtual_controller();
            int virtual_controller_button_num = event_data->get_virtual_controller_button_num();
            bool is_repeat = false;

            // TODO: Update this method. Currently the signature is:
            // screens.virtual_control_button_up_funcs(player_num, button_num, is_repeat);
            screens.virtual_control_button_up_funcs(
               player,
               virtual_controller,
               virtual_controller_button_num,
               is_repeat
            );

            delete event_data;
         } break;

         case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN: {
            AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData *event_data =
               static_cast<AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData*>(
                  (void*)this_event.user.data1
               );

            AllegroFlare::Player *player = event_data->get_player();
            AllegroFlare::VirtualControllers::Base *virtual_controller =
               event_data->get_virtual_controller();
            int virtual_controller_button_num = event_data->get_virtual_controller_button_num();
            bool is_repeat = false;

            // TODO: Update this method. Currently the signature is:
            // screens.virtual_control_button_down_funcs(player_num, button_num, is_repeat);
            screens.virtual_control_button_down_funcs(
               player,
               virtual_controller,
               virtual_controller_button_num,
               is_repeat
             );

            delete event_data;
         } break;

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
                 //std::stringstream info_message;
                 //info_message << "Playing music track identifer" << " \"" << (*data) << "\"";
                 AllegroFlare::Logger::throw_error(
                    "AllegroFlare::Frameworks::Full::run_loop",
                    //info_message.str()
                    "When handling an AlLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK event, data1 nullptr."
                       //"be present but one or ther other is a nullptr."
                 );
                 //std::cout << "[AllegroFlare::Frameworks::Full::run_loop]: ERROR: music track data is nullptr."
                           //<< std::endl;
              }
              else
              {
                 std::stringstream info_message;
                 info_message << "Playing music track identifer" << " \"" << (*data) << "\"";
                 AllegroFlare::Logger::info_from(
                    "AllegroFlare::Frameworks::Full::run_loop",
                    info_message.str()
                    //"When handling a ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, expecting data1 and data2 to "
                       //"be present but one or ther other is a nullptr."
                 );
                 //std::cout << "[AllegroFlare::Frameworks::Full::run_loop]: INFO: playing music track identifer"
                           //<< " \"" << (*data) << "\""
                           //<< std::endl;
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

         // TODO: Test these cases. This is the only location where deactivation is handled
         //case ALLEGRO_FLARE_EVENT_SCREEN_ACTIVATED:
         //case ALLEGRO_FLARE_EVENT_SCREEN_DEACTIVATED:
           //{
              //std::string *data = (std::string *)this_event.user.data1;
              //if (!data)
              //{
                 //// TODO: add an error message
              //}
              //else
              //{
                 ////audio_controller.play_sound_effect(*data);
                 //delete data;
              //}
           //}
         //break;

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

         case ALLEGRO_FLARE_EVENT_POST_JOYSTICK_CONNECTED_NOTIFICATION:
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
                    notifications_factory.create_joystick_connected_notification(*data)
                 );
                 delete data;
              }
           }
         break;

         case ALLEGRO_FLARE_EVENT_POST_JOYSTICK_DISCONNECTED_NOTIFICATION:
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
                    notifications_factory.create_joystick_disconnected_notification(*data)
                 );
                 delete data;
              }
           }
         break;

         case ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED:
            {
               AllegroFlare::Achievement *data1 = (AllegroFlare::Achievement *)this_event.user.data1;
               std::string *data2 = (std::string *)this_event.user.data2;
               if (!data1 || !data2)
               {
                  AllegroFlare::Logger::throw_error(
                     "AllegroFlare::Frameworks::Full::primary_process_event",
                     "When handling a ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED, expecting data1 and data2 to "
                        "be present but one or ther other is a nullptr."
                  );
               }
               else
               {
                  // TODO: Test this
                  std::string achievement_title = data1->get_title();
                  std::string achievement_identifier = *data2;
                  event_emitter.emit_post_unlocked_achievement_notification_event(achievement_title);
                  event_emitter.emit_achievement_unlocked_game_event(*data2);
                  // NOTE: data1 and data2 do NOT get deleted here. Normally this is where it happens, but
                  // in the case of this particular event, the pointers used point directly to data
                  // owned by Achievements.
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

         case ALLEGRO_FLARE_EVENT_SET_SHADER_TARGET_FOR_HOTLOADING: {
            // TODO: add test for this event
            AllegroFlare::Shaders::Base* shader =
               static_cast<AllegroFlare::Shaders::Base*>((void *)this_event.user.data1);
            set_shader_target_for_hotloading(shader);
         } break;

         case ALLEGRO_FLARE_EVENT_POLL_HOTLOAD_SHADER_SOURCE_FOR_CHANGE: {
            // NOTE: this will require initialization
            bool files_have_changed = shader_source_poller.poll();
            std::cout << "poll (" << (files_have_changed ? "files changed" : "no change") << ")" << std::endl;

            if (files_have_changed)
            {
               // TODO: emit event to hotload shader source
               event_emitter.emit_hotload_shader_source_event(
                  shader_source_poller.read_vertex_source_code_from_file(),
                  shader_source_poller.read_fragment_source_code_from_file()
               );
            }
         } break;

         case ALLEGRO_FLARE_EVENT_HOTLOAD_SHADER_SOURCE: {
            // TODO: add test for this event
            std::string *vertex_shader_source_ptr = static_cast<std::string*>((void *)this_event.user.data1);
            std::string *fragment_shader_source_ptr = static_cast<std::string*>((void *)this_event.user.data2);
            AllegroFlare::Shaders::Base* shader =
                  static_cast<AllegroFlare::Shaders::Base*>((void *)this_event.user.data3);

            // NOTE: The shader for hotloading is currently *hard-coded* here to be the post_processing_shader
            shader_target_for_hotloading = post_processing_shader; // TODO: make a better place for this

            if (shader)
            {
               shader->hotload(*vertex_shader_source_ptr, *fragment_shader_source_ptr);
            }
            else if (shader_target_for_hotloading)
            {
               shader_target_for_hotloading->hotload(*vertex_shader_source_ptr, *fragment_shader_source_ptr);
            }
            else
            {
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Frameworks::Full::primary_process_event",
                  "Could not hotload the shader because there is no shader target provided. Either a shader "
                  "is included in the ALLEGRO_FLARE_EVENT_HOTLOAD_SHADER_SOURCE event data or the "
                  "\"shader_target_for_hotloading\" property is set in Frameworks/Full."
               );
            }

            delete vertex_shader_source_ptr;
            delete fragment_shader_source_ptr;
            // NOTE: do not delete shader, it remains active
         } break;


         // TODO: Consider if these event should be grouped together like this
         //case ALLEGRO_FLARE_EVENT_DIALOG_OPEN:
         //case ALLEGRO_FLARE_EVENT_DIALOG_ADVANCE:
         //case ALLEGRO_FLARE_EVENT_DIALOG_CLOSE:
         case ALLEGRO_FLARE_EVENT_DIALOG_SWITCHED_IN: {
            // Nothing do do here. But consider adding "dialog_switched_in" to screens
            // NOTE: This event is fired by the dialog_system, and is a notification to the rest of the system
            // that the dialog_system is now intercepting the inputs
            screens.dialog_system_switch_in_funcs();
         } break;

         case ALLEGRO_FLARE_EVENT_DIALOG_SWITCHED_OUT: {
            // Nothing do do here. But consider adding "dialog_switched_in" to screens
            // NOTE: This event is fired by the dialog_system, and is a notification to the rest of the system
            // that the dialog_system is not intercepting the inputs anymore
            screens.dialog_system_switch_out_funcs();
         } break;

         case ALLEGRO_FLARE_EVENT_DIALOG: {
            {
               AllegroFlare::GameEventDatas::Base *data =
                  static_cast<AllegroFlare::GameEventDatas::Base *>((void *)this_event.user.data1);
               if (!data)
               {
                  // TODO: Improve error message
                  throw std::runtime_error("Frameworks::Full::error: ALLEGRO_FLARE_EVENT_DIALOG data is null");
               }
               else
               {
                  dialog_system.handle_raw_ALLEGRO_EVENT_that_is_dialog_event(&this_event, data);
                  //screens.game_event_funcs(data);
                  //achievements.unlock_manually(*data);
                  //audio_controller.play_music_track_by_identifier(*data);
                  delete data;
               }
            }
            //dialog_system.handle_raw_ALLEGRO_EVENT_that_is_dialog_event(ev);
            // TODO: Consider destroying event data here
            // Consider implementation here for dialog_system
            // TODO: Consider that "switch_in" and "switch_out" events might need to be passed down and
               // handled at the screens level, too
            //AllegroFlare::GameEvent *data =
               //static_cast<AllegroFlare::GameEvent *>((void *)this_event.user.data1);
            //dialog_system.process_ALLEGRO_FLARE_EVENT_DIALOG_event(data);
         } break;

         default:
         break;
      }
   }
   else
   {
      //screens.user_event_funcs(&this_event);
   }
}


void Full::handle_key_down_event(ALLEGRO_EVENT *this_event)
{
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Full::key_shift++;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Full::key_alt++;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Full::key_ctrl++;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_COMMAND) Full::key_command++;
   if (current_event->keyboard.keycode == ALLEGRO_KEY_F1)
      drawing_profiler_graph = !drawing_profiler_graph; // toggle the profiler graph with F1


   if ((this_event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) && (Full::key_shift > 0))
   {
      if (escape_key_will_shutdown) shutdown_program = true;
   }

   // Handle offsetting the primary timer
   if (Full::key_shift > 0)
   {
      switch (Full::current_event->keyboard.keycode)
      {
         //case ALLEGRO_KEY_F: {
            //toggle_display_fullscreen();
         //} break;
         //case ALLEGRO_KEY_1: {
            //set_window_size(1920, 1080);
         //} break;
         //case ALLEGRO_KEY_2: {
            //set_window_size(1080, 1920);
         //} break;
         //case ALLEGRO_KEY_3: {
            //set_window_size(2520, 1080);
         //} break;
         case ALLEGRO_KEY_FULLSTOP: {
            nudge_primary_timer_forward();
         } break;
         case ALLEGRO_KEY_COMMA: {
            nudge_primary_timer_backward();
         } break;
      }
      
      //int MICROSECONDS_PER_FRAME = 16670;
      //int microseconds_to_offset = MICROSECONDS_PER_FRAME / 10;
      //event_emitter.emit_offset_primary_timer_event(microseconds_to_offset);
   }

   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
      switch(this_event->keyboard.keycode)
      {
         //case ALLEGRO_KEY_UP:
            //dialog_system.move_selection_cursor_up();
         //break;

         //case ALLEGRO_KEY_DOWN:
            //dialog_system.move_selection_cursor_down();
         //break;

         case ALLEGRO_KEY_SPACE:
         case ALLEGRO_KEY_ENTER:
            dialog_system.dialog_advance();
         break;
      }
   }
   else
   {
      screens.key_down_funcs(this_event);
      virtual_controls_processor.handle_raw_keyboard_key_down_event(this_event);
   }
}


void Full::handle_key_up_event(ALLEGRO_EVENT *this_event)
{
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Full::key_shift--;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Full::key_alt--;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
         || Full::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Full::key_ctrl--;
   if (Full::current_event->keyboard.keycode == ALLEGRO_KEY_COMMAND) Full::key_command--;
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
   }
   else
   {
      screens.key_up_funcs(this_event);
      virtual_controls_processor.handle_raw_keyboard_key_up_event(this_event);
   }
   //virtual_controls_processor.handle_raw_keyboard_key_up_event(&this_event);
}


void Full::handle_key_char_event(ALLEGRO_EVENT *this_event)
{
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
      switch(this_event->keyboard.keycode)
      {
         case ALLEGRO_KEY_UP:
            dialog_system.move_dialog_cursor_position_up();
         break;

         case ALLEGRO_KEY_DOWN:
            dialog_system.move_dialog_cursor_position_down();
         break;

         case ALLEGRO_KEY_SPACE:
         case ALLEGRO_KEY_ENTER:
            //dialog_system.advance(); // Not for this case, this is handled in ALLEGRO_KEY_DOWN (until 
                                       // upgraded to virtual controls)
         break;
      }
   }
   else
   {
      screens.key_char_funcs(this_event);
   }
   //virtual_controls_processor.handle_raw_keyboard_key_char_event(&this_event); // LOOK INTO THIS
}


void Full::handle_mouse_button_up_event(ALLEGRO_EVENT *this_event)
{
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
   }
   else
   {
      screens.mouse_up_funcs(this_event);
   }
}


void Full::handle_mouse_button_down_event(ALLEGRO_EVENT *this_event)
{
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
      dialog_system.dialog_advance();
   }
   else
   {
      screens.mouse_down_funcs(this_event);
   }
}


void Full::handle_mouse_warped_event(ALLEGRO_EVENT *this_event)
{
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
   }
   else
   {
      screens.mouse_warp_funcs(this_event);
   }
}



void Full::handle_mouse_axes_event(ALLEGRO_EVENT *this_event)
{
   if (dialog_system.get_switched_in())
   {
      // HERE:
      // TODO: Handle input case with dialog when it is "switched in"
      // TODO: Add this branching for each input event case
      // TODO: Add tests for these cases, with and without dialog swtiched in
   }
   else
   {
      screens.mouse_axes_funcs(this_event);
   }
}



void Full::primary_process_event(ALLEGRO_EVENT *ev)
{
   draw = false;


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
   case ALLEGRO_EVENT_TIMER:               handle_timer_event(&this_event); break;
   case ALLEGRO_EVENT_DISPLAY_RESIZE:      handle_display_resize_event(&this_event); break;
   case ALLEGRO_EVENT_KEY_DOWN:            handle_key_down_event(&this_event); break;
   case ALLEGRO_EVENT_KEY_UP:              handle_key_up_event(&this_event); break;
   case ALLEGRO_EVENT_KEY_CHAR:            handle_key_char_event(&this_event); break;
   case ALLEGRO_EVENT_MOUSE_BUTTON_UP:     handle_mouse_button_up_event(&this_event); break;
   case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:   handle_mouse_button_down_event(&this_event); break;
   case ALLEGRO_EVENT_MOUSE_WARPED:        handle_mouse_warped_event(&this_event); break;
   case ALLEGRO_EVENT_MOUSE_AXES:          handle_mouse_axes_event(&this_event); break;

   case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
      if (dialog_system.get_switched_in())
      {
         // HERE:
         // TODO: Handle input case with dialog when it is "switched in"
         // TODO: Add this branching for each input event case
         // TODO: Add tests for these cases, with and without dialog swtiched in

         // TODO: Consider case where may only want to advance using a certain button (and possibly cancel otherwise)
         dialog_system.dialog_advance();
      }
      else
      {
         bool use_joystick_button_right_bumper_to_offset_timer = true;
         if (use_joystick_button_right_bumper_to_offset_timer)
         {
            bool button_pressed = (this_event.joystick.button == 7); // 7 is the right bumper on XBox 360 Controller
            if (button_pressed)
            {
               nudge_primary_timer_forward();
               //int MICROSECONDS_PER_FRAME = 16670;
               //int microseconds_to_offset = MICROSECONDS_PER_FRAME / 10;
               //event_emitter.emit_offset_primary_timer_event(microseconds_to_offset);
            }
         }
            //case ALLEGRO_KEY_FULLSTOP: {
               //nudge_primary_timer_forward();
            //} break;
            //case ALLEGRO_KEY_COMMA: {
               //nudge_primary_timer_backward();
            //} break;

         screens.joy_button_down_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_button_down_event(&this_event);
      }
      //virtual_controls_processor.handle_raw_joystick_button_down_event(&this_event);
   break;

   case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
      if (dialog_system.get_switched_in())
      {
         // HERE:
         // TODO: Handle input case with dialog when it is "switched in"
         // TODO: Add this branching for each input event case
         // TODO: Add tests for these cases, with and without dialog swtiched in
      }
      else
      {
         screens.joy_button_up_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_button_up_event(&this_event);
      }
      //virtual_controls_processor.handle_raw_joystick_button_up_event(&this_event);
   break;

   case ALLEGRO_EVENT_JOYSTICK_AXIS:
      if (dialog_system.get_switched_in())
      {
         // HERE:
         // TODO: Handle input case with dialog when it is "switched in"
         // TODO: Add this branching for each input event case
         // TODO: Add tests for these cases, with and without dialog swtiched in
      }
      else
      {
         screens.joy_axis_funcs(&this_event);
         virtual_controls_processor.handle_raw_joystick_axis_change_event(&this_event);
      }
      //virtual_controls_processor.handle_raw_joystick_axis_change_event(&this_event);
   break;

   case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
      screens.joy_config_funcs(&this_event);
      // NOTE: input_devices_list.handle_reconfiguration does not occur here, it's currently managed in the
      // virtual_controls_processor which may not be the best place. This domain requires a bit of review,
      // as there is an input_devices_list that is involved and needs to be accounted for. Posting notifications
      // events may need review (should have callbacks that can be used to produce events?). See the body of
      // virtual_controls_processor.handle_joystick_device_configuration_change_event() for a little more direction.

      virtual_controls_processor.handle_joystick_device_configuration_change_event(&this_event);
   break;

   case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
   case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
      // currently ignored
   break;

   case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
      screens.display_switch_in_funcs();
   break;

   case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
      screens.display_switch_out_funcs();
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

         if (display_close_will_shutdown) shutdown_program = true;
      }
   break;

   case ALLEGRO_EVENT_VIDEO_FRAME_SHOW:
      // TODO:
      // This will require a video manager, because each video will need to be registered to the event queue
   break;

   case ALLEGRO_EVENT_VIDEO_FINISHED:
      // TODO:
      // This will require a video manager, because each video will need to be registered to the event queue
   break;

   default:
      if (ALLEGRO_EVENT_TYPE_IS_USER(this_event.type))
      {
         handle_user_event(&this_event);
      }
      else
      {
         std::cout << "uncaught event [" << this_event.type << "]" << std::endl;
      }
   break;
   }


   if (draw)
   {
      handle_update(); // TODO: Consider moving update out of this draw block
      handle_draw();

      draw = false;
   }
}


void Full::handle_update()
{
   sync_oracle.start_update_measure();
   // TODO: Figure out what this delta_time variable should be
   double delta_time = sync_oracle.calculate_duration_of_previous_frame_for_delta_time();
   primary_update(time_now, delta_time);
   sync_oracle.end_update_measure();

   //sync_oracle.start_draw_measure();
   //primary_render();
   //sync_oracle.end_draw_measure();
   ////flip_sync.start_flip_capture();
   ////metric.al_flip_display_start_time = al_get_time();
   //sync_oracle.start_flip_measure(); // ---
   //primary_flip();
   //sync_oracle.end_flip_measure(); // ---
}


void Full::handle_draw()
{
   //sync_oracle.start_update_measure();
   //// TODO: Figure out what this delta_time variable should be
   //double delta_time = sync_oracle.calculate_duration_of_previous_frame_for_delta_time();
   //primary_update(time_now, delta_time);
   //sync_oracle.end_update_measure();

   sync_oracle.start_draw_measure();
   primary_render();
   sync_oracle.end_draw_measure();
   //flip_sync.start_flip_capture();
   //metric.al_flip_display_start_time = al_get_time();
   sync_oracle.start_flip_measure(); // ---
   primary_flip();
   sync_oracle.end_flip_measure(); // ---
}


int Full::process_events_in_queue()
{
   int count = 0;
   ALLEGRO_EVENT this_event;
   int dropped_primary_timer_events = 0;
   while (al_get_next_event(event_queue, &this_event))
   {
      count++;
      //float time_of_event;
      //float time_of_event_processing_start;
      //float time_of_event_processing_end;
      //int dropped_primary_timer_events;

      primary_process_event(&this_event);
      //if (dropped_primary_timer_events != 0)
      //{
         //std::cout << "
      //}
   }
   return count;
}


void Full::run_loop(float auto_shutdown_after_seconds)
{
   // Emit our iniitial events
   event_emitter.emit_game_event(AllegroFlare::GameEvent("initialize"));
   if (router) event_emitter.emit_router_event(1); //AllegroFlare::GameEvent("initialize"));

   // Start our timers
   sync_oracle.activate_primary_timer();
   sync_oracle.activate_hyper_timer();
   sync_oracle.activate_auto_nudge();


   //al_start_timer(high_frequency_timer);

   float loop_started_at = al_get_time();

   //offset_primary_timer(4000); // Maybe this is the magic number
                               // TODO: See if this offset has any reasonable effect
                               // Doing so will attempt to set the primary timer to *start* at the beginning
                               // of the "vblank" (when the frame has finished flipping)

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

   //al_stop_timer(primary_timer);
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
   //profiler.start(".draw_overlay()");

   // TODO: Move this option to a data member
   // TODO: Consider moving this restoration process to happen before/outside this method
   bool restore_allegro_default_projection_and_use_identity_transform_before_drawing_overlay = true;
   if (restore_allegro_default_projection_and_use_identity_transform_before_drawing_overlay)
   {
      // TODO: Restore target bitmap to primary_render_surface

      // Restore allegro's default projection and use identity transform
      // TODO: Consider that a camera2d.setup_dimensional_projection() may be preferred here.
      ALLEGRO_BITMAP *surface = al_get_target_bitmap();
      ALLEGRO_TRANSFORM t;
      al_identity_transform(&t);
      al_use_transform(&t); // Use a default identity transform
      al_orthographic_transform(&t, 0, 0, -1.0, al_get_bitmap_width(surface),
                                al_get_bitmap_height(surface), 1.0);
      al_use_projection_transform(&t);

      // Clear the depth buffer
      al_clear_depth_buffer(1);

      // Set a typical render state
      // TODO: Consider if other render states should be set here as well
      // TODO: do a full audit of render flags that should be restored in addition to setting this
      al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL);

      al_use_shader(NULL); // TODO: consider side-effects of this
   }


   if (drawing_dialogs)
   {
      dialog_system.render(); // TODO: Consider moving this to a dedcated DialogSystem::Renderer
      if (showing_dialog_switched_in_debug_text && dialog_system.get_switched_in())
      {
         // Draw a debugging notice for when the dialog system is "switched in"
         // TODO: Add a flag to enable/disable this text notice
         al_draw_text(
            obtain_system_text_font_medium(),
            ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
            20,
            30,
            ALLEGRO_ALIGN_LEFT,
            "Dialog system is switched in"
         );
      }
   }


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

   //profiler.stop(".draw_overlay()");

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


      sync_oracle.draw_graph();

      //AllegroFlare::ProfilerRenderer profiler_renderer(&fonts);
      //profiler_renderer.set_timers(&profiler.get_timers_ref());
      //profiler_renderer.render();

      /*
      {
         std::vector<double> samples = flip_sync.get_last_n_capture_durations();
         ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
         std::vector<ALLEGRO_VERTEX> v;
         v.resize(samples.size());

         int x = 100;
         int y = 1080/2;

         int w = samples.size() * 3;
         //int h = 200;

         int i=0;
         for (auto &sample : samples)
         {
            v[i] = {.x = x+i*3.0f, .y = y - (float)sample*1000.0f, .z = 0, .color = white, .u = 0, .v = 0};
            i++;
         }
         
            //{.x = 128, .y = 0, .z = 0, .color = white, .u = 128, .v = 0},
            //{.x = 0, .y = 256, .z = 0, .color = white, .u = 0, .v = 256},
            //{.x = 256, .y = 256, .z = 0, .color = white, .u = 256, .v = 256}};
         al_draw_prim(&v[0], NULL, NULL, 0, samples.size(), ALLEGRO_PRIM_LINE_STRIP);
      }
      */
      //ALLEGRO_
      //al_draw_prim

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
   return fonts.auto_get("Inter-Regular.ttf -22");
}


ALLEGRO_FONT *Full::obtain_system_text_font_medium()
{
   //return fonts.auto_get("system");
   return fonts.auto_get("Inter-Regular.ttf -32");
}


} // namespace Frameworks
} // namespace AllegroFlare


