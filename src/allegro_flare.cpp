
#include <allegro_flare/allegro_flare.h>





void af::initialize(std::string config_filename)
{
	if (initialized) return;

	al_init();

	ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
	al_destroy_path(resource_path);

	al_install_mouse();
	al_install_keyboard();
	al_install_joystick();
	al_install_audio();

	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	al_reserve_samples(32); // eventually, something like af::config->get_value_int("NUM_RESERVE_SAMPLES");

	srand(time(NULL));

	primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 256, ALLEGRO_SUGGEST); // hmm... not sure about this one either
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_flags(ALLEGRO_OPENGL);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_default_menu_event_source());

	joystick = al_get_joystick(0); // make this better eventually

	initialized = true;
}


// TODO: get rid of all these silly af::create_display() overloads


Display *af::create_display(int width, int height)
{
	return create_display(width, height, false, -1);
}


Display *af::create_display(int width, int height, int display_flags)
{
	Display *display = new Display(width, height, display_flags);
	al_register_event_source(event_queue, al_get_display_event_source(display->display));
	return display;
}


Display *af::create_display(int width, int height, int display_flags, int adapter)
{
	if (adapter!=-1) al_set_new_display_adapter(adapter);
	Display *display = new Display(width, height, display_flags);
	al_register_event_source(event_queue, al_get_display_event_source(display->display));
	return display;
}


Display *af::create_display(int width, int height, bool fullscreen)
{
	Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);
	al_register_event_source(event_queue, al_get_display_event_source(display->display));
	return display;
}


Display *af::create_display(int width, int height, bool fullscreen, int adapter)
{
	if (adapter!=-1) al_set_new_display_adapter(adapter);
	Display *display = new Display(width, height, fullscreen ? ALLEGRO_FULLSCREEN : ALLEGRO_WINDOWED);

	al_register_event_source(event_queue, al_get_display_event_source(display->display));
	return display;
}



Display *af::create_display(Display::resolution_t resolution)
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



void af::use_screen(Screen *screen)
{
	//current_screen = screen;
}



void af::run_loop()
{
	al_start_timer(primary_timer);

	while(!shutdown_program || Display::displays.empty())
	{
		ALLEGRO_EVENT this_event, next_event;

		al_wait_for_event(event_queue, &this_event);
		
		current_event = &this_event;
		time_now = this_event.any.timestamp;

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
			if (current_event->keyboard.keycode == ALLEGRO_KEY_F1)
				drawing_profiler_graph = !drawing_profiler_graph; // toggle the profiler graph with F1
			Screen::key_down_funcs();
			break;
		case ALLEGRO_EVENT_KEY_UP:
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
		case ALLEGRO_EVENT_MOUSE_AXES:
			Screen::mouse_axes_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
			Screen::joy_down_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
			Screen::joy_up_funcs();
			break;
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
			Screen::joy_axis_funcs();
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
			joystick = al_get_joystick(0);
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
			break;
		}
	}
}



void af::open_log_window()
{
	if (textlog) return;

	textlog = al_open_native_text_log("Log", ALLEGRO_TEXTLOG_MONOSPACE);
	al_register_event_source(event_queue, al_get_native_text_log_event_source(textlog));
}



void af::close_log_window()
{
	if (!textlog) return;

	al_unregister_event_source(event_queue, al_get_native_text_log_event_source(textlog));
	textlog = NULL;
}



void af::log(std::string message)
{
	if (!textlog) return;
	al_append_native_text_log(textlog, message.c_str());
}




ALLEGRO_TEXTLOG *af::textlog = NULL;
ALLEGRO_JOYSTICK *af::joystick = NULL;
ALLEGRO_EVENT_QUEUE *af::event_queue = NULL;
ALLEGRO_TIMER *af::primary_timer = NULL;
bool af::shutdown_program = false;
Screen *af::current_screen = NULL;
double af::time_now = 0;
ALLEGRO_EVENT *af::current_event = NULL;
bool af::initialized = false;
bool af::key_alt = false;
bool af::key_shift = false;
bool af::key_ctrl = false;
bool af::drawing_profiler_graph = false;

