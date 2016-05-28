
#include <allegro_flare/framework.h>

#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>

#include <allegro_flare/useful.h>

#include <allegro_flare/bins/sample_bin.h>
#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/bins/model_bin.h>
#include <allegro_flare/motion.h>



Framework *Framework::get_instance()
{
   if (!instance) instance = new Framework(1);
   return instance;
}



Framework::Framework(int val)
   : fonts("data/fonts")
   , samples("data/samples")
   , bitmaps("data/bitmaps")
   , models("data/models")
   , motions(200)
{}



ALLEGRO_FONT *Framework::font(std::string identifier)
{
   return get_instance()->fonts[identifier];
}



ALLEGRO_BITMAP *Framework::bitmap(std::string identifier)
{
   return get_instance()->bitmaps[identifier];
}



ALLEGRO_SAMPLE *Framework::sample(std::string identifier)
{
   return get_instance()->samples[identifier];
}



Model3D *Framework::model(std::string identifier)
{
   return get_instance()->models[identifier];
}



Motion &Framework::motion()
{
   return get_instance()->motions;
}



bool Framework::initialize(std::string config_filename)
{
	if (initialized) return initialized;

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

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
//	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

	builtin_font = al_create_builtin_font();

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_default_menu_event_source());

	if (al_get_num_joysticks()) joystick = al_get_joystick(0); // make this better eventually
	else std::cerr << "no joystick(s) detected" << std::endl;

	initialized = true;

	return initialized;
}


// TODO: get rid of all these silly Framework::create_display() overloads


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



void Framework::use_screen(Screen *screen)
{
	//current_screen = screen;
}



void Framework::run_loop()
{
	al_start_timer(primary_timer);

	while(!shutdown_program || Display::displays.empty())
	{
		ALLEGRO_EVENT this_event, next_event;

		al_wait_for_event(event_queue, &this_event);
		
		current_event = &this_event;
		time_now = this_event.any.timestamp;
		get_instance()->motions.update(time_now);

		Screen::on_events(current_event);

		switch(this_event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			if (this_event.timer.source == primary_timer)
				Screen::primary_timer_funcs();
			else
				Screen::timer_funcs();
			while (al_peek_next_event(event_queue, &next_event)
				&& next_event.type == ALLEGRO_EVENT_TIMER
				&& next_event.timer.source == this_event.timer.source)
					al_drop_next_event(event_queue);
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
			Screen::key_down_funcs();
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LSHIFT
				|| Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) Framework::key_shift--;
			if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALT
				|| Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ALTGR) Framework::key_alt--;
			if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_RCTRL
				|| Framework::current_event->keyboard.keycode == ALLEGRO_KEY_LCTRL) Framework::key_ctrl--;
			Screen::key_up_funcs();
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			Screen::key_char_funcs();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			Screen::mouse_up_funcs();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			Screen::mouse_down_funcs();
			break;
		case ALLEGRO_EVENT_MOUSE_WARPED:
			Screen::mouse_warp_funcs();
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			Screen::mouse_axes_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
			Screen::joy_button_down_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
			Screen::joy_button_up_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
			Screen::joy_axis_funcs();
			break;
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			// currently ignored
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
			Screen::display_switch_out_funcs();
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
			Screen::display_switch_in_funcs();
			break;
		case ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE:
			//Screen::display_switch_in_funcs();
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
			Screen::joy_config_funcs();
			break;
		case ALLEGRO_EVENT_MENU_CLICK:
			Screen::native_menu_click_funcs();
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				Display *this_display = Display::find_display(this_event.display.source);
				if (this_display) this_display->display_close_func();
			}
			break;
		default:
			if (ALLEGRO_EVENT_TYPE_IS_USER(this_event.type)) Screen::user_event_funcs();
			else std::cout << "uncaught event [" << this_event.type << "]" << std::endl;
			break;
		}
	}
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



ALLEGRO_TEXTLOG *Framework::textlog = NULL;
ALLEGRO_JOYSTICK *Framework::joystick = NULL;
ALLEGRO_EVENT_QUEUE *Framework::event_queue = NULL;
ALLEGRO_TIMER *Framework::primary_timer = NULL;
ALLEGRO_FONT *Framework::builtin_font = NULL;
bool Framework::shutdown_program = false;
Screen *Framework::current_screen = NULL;
double Framework::time_now = 0;
ALLEGRO_EVENT *Framework::current_event = NULL;
bool Framework::initialized = false;
int Framework::key_alt = 0;
int Framework::key_shift = 0;
int Framework::key_ctrl = 0;
bool Framework::drawing_profiler_graph = false;

Framework *Framework::instance = NULL;

