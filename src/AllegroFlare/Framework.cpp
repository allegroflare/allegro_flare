



#include <AllegroFlare/Framework.hpp>

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/Screen.hpp>
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

#include <thread> // for offset_primary_timer
#include <chrono> // for offset_primary_timer


namespace AllegroFlare
{
   //ALLEGRO_TEXTLOG *Framework::textlog = NULL;
   //ALLEGRO_JOYSTICK *Framework::joystick = NULL;
   //ALLEGRO_EVENT_QUEUE *Framework::event_queue = NULL;
   //ALLEGRO_TIMER *Framework::primary_timer = NULL;
   //ALLEGRO_FONT *Framework::builtin_font = NULL;
   //bool Framework::shutdown_program = false;
   //Screen *Framework::current_screen = NULL;
   //double Framework::time_now = 0;
   //ALLEGRO_EVENT *Framework::current_event = NULL;
   //bool Framework::initialized = false;
   //int Framework::key_alt = 0;
   //int Framework::key_shift = 0;
   //int Framework::key_ctrl = 0;
   //bool Framework::drawing_profiler_graph = false;




   Framework::Framework(Screens *screens_ptr)
      : screens_ptr(screens_ptr)
      , initialized(false)
      , config("data/config/config.cfg")
      , fonts()
      , samples()
      , bitmaps()
      , models()
      , motions(200)
      , audio_controller(&samples)
      , event_emitter()
      , virtual_controls_processor()
      , textlog(nullptr)
      , joystick(nullptr)
      , event_queue(nullptr)
      , builtin_font(nullptr)
      , primary_display(nullptr)
      , primary_timer(nullptr)
      , shutdown_program(false)
      , current_screen(nullptr)
      , current_event(nullptr)
      , time_now(0)
      , key_alt(0)
      , key_shift(0)
      , key_ctrl(0)
      , drawing_profiler_graph(false)
   {}




   Framework::~Framework()
   {
      destruct();
   }




   ALLEGRO_FONT *Framework::font(std::string identifier)
   {
      return fonts[identifier];
   }




   ALLEGRO_BITMAP *Framework::bitmap(std::string identifier)
   {
      return bitmaps[identifier];
   }




   ALLEGRO_SAMPLE *Framework::sample(std::string identifier)
   {
      return samples[identifier];
   }




   Model3D *Framework::model(std::string identifier)
   {
      return models[identifier];
   }




   Motion &Framework::motion()
   {
      return motions;
   }




   Config &Framework::get_config()
   {
      return config;
   }



   FontBin &Framework::get_font_bin_ref()
   {
      return fonts;
   }



   BitmapBin &Framework::get_bitmap_bin_ref()
   {
      return bitmaps;
   }



   SampleBin &Framework::get_sample_bin_ref()
   {
      return samples;
   }



   AudioController &Framework::get_audio_controller_ref()
   {
      return audio_controller;
   }


   EventEmitter &Framework::get_event_emitter_ref()
   {
      return event_emitter;
   }


   Display *Framework::get_primary_display()
   {
      return primary_display;
   }



   bool Framework::initialize()
   {
      if (initialized) return false;

      if (!al_init()) std::cerr << "al_init() failed" << std::endl;

      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);

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

      srand(time(NULL));

      primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));


      al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
      //	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

      builtin_font = al_create_builtin_font();

      event_queue = al_create_event_queue();
      al_register_event_source(event_queue, al_get_keyboard_event_source());
      al_register_event_source(event_queue, al_get_mouse_event_source());
      al_register_event_source(event_queue, al_get_joystick_event_source());
      al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
      al_register_event_source(event_queue, al_get_joystick_event_source());
      al_register_event_source(event_queue, al_get_default_menu_event_source());

      event_emitter.initialize();
      al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

      virtual_controls_processor.set_event_emitter(&event_emitter);
      virtual_controls_processor.initialize();

      //if (al_get_num_joysticks()) joystick = al_get_joystick(0); // make this better eventually
      //else
      //{
         //std::cout << "[AllegroFlare::Framework::initialize] Info: No joystick(s) detected." << std::endl;
      //}

      //instance = new Framework(config_filename);

      fonts.set_path("data/fonts");
      samples.set_path("data/samples");
      bitmaps.set_path("data/bitmaps");
      models.set_path("data/models");
      config.load_or_create_empty();

      Attributes::create_datatype_definition(
         AllegroColorAttributeDatatype::IDENTIFIER,
         AllegroColorAttributeDatatype::to_val_func,
         AllegroColorAttributeDatatype::to_str_func
      );

      audio_controller.initialize();

      initialized = true;

      return true;
   }


   bool Framework::initialize_with_display()
   {
      if (initialized) return false;

      initialize();

      primary_display = create_display(
            1920,
            1080,
            ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE
         );
   }


   bool Framework::destruct()
   {
      // TODO autit this function
      samples.clear();
      bitmaps.clear();
      fonts.clear();

      initialized = false;

      al_uninstall_system();
      return true;
   }




   bool Framework::is_initialized()
   {
      return initialized;
   }




   Display *Framework::create_display(int width, int height)
   {
      return create_display(width, height, false, -1);
   }




   Display *Framework::create_display(int width, int height, int display_flags)
   {
      Display *display = new Display(width, height, display_flags);
      al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
      return display;
   }




   Display *Framework::create_display(int width, int height, int display_flags, int adapter)
   {
      if (adapter!=-1) al_set_new_display_adapter(adapter);
      Display *display = new Display(width, height, display_flags);
      al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
      return display;
   }




   Display *Framework::create_display(int width, int height, bool fullscreen)
   {
      Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);
      al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
      return display;
   }




   Display *Framework::create_display(int width, int height, bool fullscreen, int adapter)
   {
      if (adapter!=-1) al_set_new_display_adapter(adapter);
      Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);

      al_register_event_source(event_queue, al_get_display_event_source(display->al_display));
      return display;
   }




   Display *Framework::create_display(Display::resolution_t resolution)
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



   bool Framework::offset_primary_timer(int microseconds)
   {
      if (!primary_timer) throw std::runtime_error("Framework: offset_primary_timer: primary_timer cannot be nullptr");
      if (!al_get_timer_started(primary_timer)) return false;

      // TODO, profile this delay offset and output the actual offset to cout
      al_stop_timer(primary_timer);
      std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
      al_start_timer(primary_timer);

      return true;
   }



   void Framework::run_loop()
   {
      if (!screens_ptr)
      {
         std::stringstream error_message;
         error_message << "Framework::run_loop: error: screens cannot be nullptr";
         throw std::runtime_error(error_message.str());
      }

      al_wait_for_vsync();
      al_start_timer(primary_timer);

      AllegroFlare::Screens &screens = (*screens_ptr);

      while(!shutdown_program || Display::displays.empty())
      {
         ALLEGRO_EVENT this_event, next_event;

         al_wait_for_event(event_queue, &this_event);

         current_event = &this_event;
         time_now = this_event.any.timestamp;
         motions.update(time_now);

         screens.on_events(current_event);

         switch(this_event.type)
         {
         case ALLEGRO_EVENT_TIMER:
            if (this_event.timer.source == primary_timer)
            {
               al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
               screens.primary_timer_funcs();
               al_flip_display();
            }
            else
            {
               screens.timer_funcs();
            }
            while (al_peek_next_event(event_queue, &next_event)
                  && next_event.type == ALLEGRO_EVENT_TIMER
                  && next_event.timer.source == this_event.timer.source)
            {
               al_drop_next_event(event_queue);
            }
            break;
         case ALLEGRO_EVENT_KEY_DOWN:
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Framework::key_shift++;
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Framework::key_alt++;
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Framework::key_ctrl++;
            if (current_event->keyboard.keycode == ALLEGRO_KEY_F1)
               drawing_profiler_graph = !drawing_profiler_graph; // toggle the profiler graph with F1
            screens.key_down_funcs(&this_event);
            virtual_controls_processor.handle_raw_keyboard_key_down_event(&this_event);
            break;
         case ALLEGRO_EVENT_KEY_UP:
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Framework::key_shift--;
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Framework::key_alt--;
            if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
                  || Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Framework::key_ctrl--;
            screens.key_up_funcs(&this_event);
            virtual_controls_processor.handle_raw_keyboard_key_up_event(&this_event);
            break;
         case ALLEGRO_EVENT_KEY_CHAR:
            screens.key_char_funcs(&this_event);
            break;
         case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            screens.mouse_up_funcs();
            break;
         case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            screens.mouse_down_funcs();
            break;
         case ALLEGRO_EVENT_MOUSE_WARPED:
            screens.mouse_warp_funcs();
            break;
         case ALLEGRO_EVENT_MOUSE_AXES:
            screens.mouse_axes_funcs();
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
         case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            std::cout << "a joystick was added/removed" << std::endl;
            al_reconfigure_joysticks();
            // note: a bug in allegro causes a crash when al_get_joystick(0) if there
            // are 0 joysticks.  So this extra check has been added to prevent
            // the crash from occuring, though it should be corrected in future
            // versions when this bug in allegro is fixed.
            joystick = (al_get_num_joysticks() == 0) ? NULL : al_get_joystick(0);
            screens.joy_config_funcs(&this_event);
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
                     case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
                       screens.virtual_control_button_up_funcs(&this_event);
                     break;

                     case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
                       screens.virtual_control_button_down_funcs(&this_event);
                     break;

                     case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE:
                       screens.virtual_control_axis_change_funcs(&this_event);
                     break;

                     case ALLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK:
                       {
                          std::string *data = (std::string *)this_event.user.data1;
                          if (!data)
                          {
                             // TODO: add an error message
                          }
                          else
                          {
                             audio_controller.play_music_track_by_identifier(*data);
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
                             audio_controller.play_sound_effect_by_identifier(*data);
                             delete data;
                          }
                       }
                     break;
                  }
               }
               else
               {
                  screens.user_event_funcs(&this_event);
               }
            }
            else
            {
               std::cout << "uncaught event [" << this_event.type << "]" << std::endl;
            }
            break;
         }
      }
   }




   std::string Framework::get_allegro_version_string()
   {
      AllegroFlare::Version version;
      return version.get_allegro_version_string();
   }




   std::string Framework::get_allegro_flare_version_string()
   {
      AllegroFlare::Version version;
      return version.get_allegro_flare_version_string();
   }




   void Framework::open_log_window()
   {
      if (textlog) return;

      textlog = al_open_native_text_log("Log", ALLEGRO_TEXTLOG_MONOSPACE);
      al_register_event_source(event_queue, al_get_native_text_log_event_source(textlog));
   }




   void Framework::close_log_window()
   {
      if (!textlog) return;

      al_unregister_event_source(event_queue, al_get_native_text_log_event_source(textlog));
      textlog = NULL;
   }




   void Framework::log(std::string message)
   {
      if (!textlog) return;
      al_append_native_text_log(textlog, message.c_str());
   }
}




