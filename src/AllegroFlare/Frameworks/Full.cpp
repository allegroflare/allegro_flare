



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


namespace AllegroFlare
{
namespace Frameworks
{


Full::Full()
   : screens()
   , initialized(false)
   , config("data/config/config.cfg")
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
   , joystick(nullptr)
   , primary_display(nullptr)
   , primary_sub_bitmap(nullptr)
   , primary_timer(nullptr)
   , camera_2d()
   , drawing_inputs_bar_overlay(false)
   , drawing_notifications(true)
   , input_hints_tokens({})
   , escape_key_will_shutdown(true)
   , input_hints_text_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , input_hints_text_opacity(0.4)
   , event_queue(nullptr)
   , builtin_font(nullptr)
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


Display *Full::get_primary_display()
{
   return primary_display;
}



bool Full::initialize_without_display()
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

   achievements.set_event_emitter(&event_emitter);

   //if (al_get_num_joysticks()) joystick = al_get_joystick(0); // make this better eventually
   //else
   //{
      //std::cout << "[AllegroFlare::Full::initialize] Info: No joystick(s) detected." << std::endl;
   //}

   //instance = new Full(config_filename);

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


bool Full::initialize()
{
   if (initialized) return false;

   initialize_without_display();

   primary_display = create_display(
         1920,
         1080,
         ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE
      );

   if (!primary_display || !primary_display->al_display)
   {
      throw std::runtime_error("[Frameworks::Full::initialize]: FAILURE: unable to create primary_display.");
   }

   ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(primary_display->al_display);
   primary_sub_bitmap = al_create_sub_bitmap(
      backbuffer_bitmap,
      0,
      0,
      al_get_bitmap_width(backbuffer_bitmap),
      al_get_bitmap_height(backbuffer_bitmap)
   );

   if (!primary_sub_bitmap)
   {
      std::cout << "[AllegroFlare::Frameworks::Full::initialize]: ERROR: could not create primary_sub_bitmap" << std::endl;
   }
   camera_2d.setup_dimentional_projection(primary_sub_bitmap); // this should remain the same throughout
                                                               // the whole program

   camera_2d.setup_dimentional_projection(backbuffer_bitmap); // this could potentially change depending on the
                                                              // needs of the game

   return true;
}


bool Full::shutdown()
{
   if (!initialized) return false;

   // TODO autit this function
   samples.clear();
   bitmaps.clear();
   fonts.clear();
   models.clear();

   if (primary_sub_bitmap) al_destroy_bitmap(primary_sub_bitmap);
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


void Full::primary_render()
{
   ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(primary_display->al_display);
   al_set_target_bitmap(backbuffer_bitmap);

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
   screens.primary_timer_funcs();

   al_set_target_bitmap(primary_sub_bitmap);
   draw_overlay();

   al_flip_display();
}


void Full::primary_process_event(ALLEGRO_EVENT *ev, bool drain_sequential_timer_events)
{
      ALLEGRO_EVENT &this_event = *ev;
      ALLEGRO_EVENT next_event;

      screens.on_events(current_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_TIMER:
         if (this_event.timer.source == primary_timer)
         {
            primary_update();
            //// update
            //motions.update(time_now);
            //achievements.check_all();

            primary_render();
            //// render
            //ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(primary_display->al_display);
            //al_set_target_bitmap(backbuffer_bitmap);
            //
            //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            //screens.primary_timer_funcs();
            //
            //al_set_target_bitmap(primary_sub_bitmap);
            //draw_overlay();
            //
            //al_flip_display();
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
                  case ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR:
                     disable_drawing_inputs_bar_overlay();
                  break;

                  case ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR:
                     enable_drawing_inputs_bar_overlay();
                  break;

                  case ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_OPACITY: {
                     float *data = (float *)this_event.user.data1;
                     input_hints_text_opacity = *data;
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

                  case ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED:
                    // TODO figure out what to do here
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


void Full::run_loop()
{
   event_emitter.emit_game_event(AllegroFlare::GameEvent("initialize"));

   al_wait_for_vsync();
   al_start_timer(primary_timer);

   while(!shutdown_program || Display::displays.empty())
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      current_event = &this_event;
      time_now = this_event.any.timestamp;
      //motions.update(time_now); // this was here, and has been moved to below the ALLEGRO_EVENT_TIMER event

      primary_process_event(current_event);
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
   if (drawing_inputs_bar_overlay)
   {
      //if (!input_hints_tokens.empty() || show_input_hints_bar_when_empty) // this feature has not been requested
      {
         AllegroFlare::InputHints input_hints(&fonts);
         ALLEGRO_COLOR text_color = input_hints_text_color;
         text_color.r *= input_hints_text_opacity;
         text_color.g *= input_hints_text_opacity;
         text_color.b *= input_hints_text_opacity;
         text_color.a *= input_hints_text_opacity;
         input_hints.set_keyboard_key_combo_tokens(input_hints_tokens);
         input_hints.set_text_color(text_color);
         input_hints.render();
      }
   }

   if (drawing_notifications)
   {
      float num_seconds_to_show_notifications = 6.0f;
      float min_created_at_notification_to_show = al_get_time() - num_seconds_to_show_notifications;

      std::vector<AllegroFlare::Elements::Notifications::Base*> notifications_to_render =
         notifications.select_created_at_since_order_by_created_at(min_created_at_notification_to_show);
      AllegroFlare::Elements::NotificationsRenderer notifications_renderer(&fonts, notifications_to_render);
      notifications_renderer.render();
   }
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


} // namespace Frameworks
} // namespace AllegroFlare


