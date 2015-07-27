

#include <allegro5/allegro_color.h>

#include <allegro_flare/allegro_flare.h> // just for af::drawing_profiler_graph
#include <allegro_flare/screen.h>
#include <allegro_flare/display.h>
#include <allegro_flare/profile_timer.h>



void Screen::on_events(ALLEGRO_EVENT *ev)
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->active && instance[i]->timer_func)
			screens[i]->on_event(ev);
}


#include <iostream>
void Screen::primary_timer_funcs()
{
	// humm... this should be rethought but it works for now.

	// do screens with NULL displays first
	for (unsigned i=0; i<screens.size(); i++)
	{
		if (screens[i]->display == NULL) screens[i]->primary_timer_func();
	}

	// then do screens in order sorted by displays.
	for (unsigned d=0; d<Display::displays.size(); d++)
	{
		Display::displays[d]->clear();
		for (unsigned i=0; i<screens.size(); i++)
		{
			if (screens[i]->display == Display::displays[d])
			{
				Display::displays[d]->set_as_target_bitmap(); // < THIS LINE will also reset the current
															  // transform and screen setting to ortho,
															  // so if you want do draw a 3D scene, you'll
															  // need to setup the projection again from here

				// these next three lines were recently added, they insure that 2D will be drawn correctly
				// (if projection was used in the previous frame)
				al_set_render_state(ALLEGRO_DEPTH_TEST, 0); //< disable the depth test, otherwise bitmaps will be drawn in the incorrect order
				al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);  // not sure if this is needed
				al_clear_depth_buffer(1); // not sure if this is needed

				screens[i]->primary_timer_func();
			}
		}
		stop_profile_timer("Full Cycle");
		//if (af::drawing_profiler_graph) draw_profile_timer_graph();
		Display::displays[d]->flip();
		start_profile_timer("Full Cycle");
	}
}



void Screen::timer_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		screens[i]->timer_func();
}



void Screen::display_switch_in_funcs()
{
	for (unsigned d=0; d<Display::displays.size(); d++)
	{
		for (unsigned i=0; i<screens.size(); i++)
		{
			if (screens[i]->display == NULL || screens[i]->display == Display::displays[d])
				screens[i]->display_switch_in_func();
		}
	}
}



void Screen::display_switch_out_funcs()
{
	for (unsigned d=0; d<Display::displays.size(); d++)
	{
		for (unsigned i=0; i<screens.size(); i++)
		{
			if (screens[i]->display == NULL || screens[i]->display == Display::displays[d])
				screens[i]->display_switch_out_func();
		}
	}
}



void Screen::key_down_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->key_down_func();
}


void Screen::key_up_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->key_up_func();
}


void Screen::key_char_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->key_char_func();
}


void Screen::mouse_axes_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->mouse_axes_func();
}


void Screen::mouse_warp_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->mouse_warp_func();
}


void Screen::mouse_down_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->mouse_down_func();
}


void Screen::mouse_up_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->mouse_up_func();
}


void Screen::joy_axis_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->joy_axis_func();
}


void Screen::joy_button_up_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->joy_button_up_func();
}


void Screen::joy_button_down_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->joy_button_down_func();
}


void Screen::joy_config_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		screens[i]->joy_config_func();
}


void Screen::user_event_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->user_event_func();
}


void Screen::native_menu_click_funcs()
{
	for (unsigned i=0; i<screens.size(); i++)
		//if (instance[i]->input_active)
			screens[i]->native_menu_click_func();
}


void Screen::send_signal(int signal, void *data)
{
	for (unsigned i=0; i<screens.size(); i++)
		screens[i]->receive_signal(signal, data);
}


void Screen::send_signal(std::string const &signal, void *data)
{
	for (unsigned i=0; i<screens.size(); i++)
		screens[i]->receive_signal(signal, data);
}



Screen::Screen(Display *display)
	//: background_color(al_color_name("darkolivegreen"))
	//, updating(true)
	//, input_active(true)
	//, drawing(true)
	: display(display)
{
	screens.push_back(this);
}



Screen::~Screen()
{
	for (unsigned i=0; i<screens.size(); i++)
		if (screens[i] == this)
		{
			screens.erase(screens.begin() + i);
			i--;
		}
}


	
void Screen::bring_to_front(Screen *s)
{
	if (!s) return;

	for (unsigned i=0; i<screens.size(); i++)
		if (screens[i] == s)
		{
			screens.erase(screens.begin()+i);
			break;
		}
	screens.push_back(s);
}



void Screen::set_on_display(Display *display)
{
	this->display = display;
}


int Screen::get_num_screens()
{
	return screens.size();
}


void Screen::on_event(ALLEGRO_EVENT *ev) {}
void Screen::primary_timer_func() {}
void Screen::timer_func() {}
void Screen::mouse_axes_func() {}
void Screen::mouse_warp_func() {}
void Screen::display_switch_in_func() {}
void Screen::display_switch_out_func() {}
void Screen::mouse_down_func() {}
void Screen::mouse_up_func() {}
void Screen::key_down_func() {}
void Screen::key_up_func() {}
void Screen::key_char_func() {}
void Screen::joy_button_down_func() {}
void Screen::joy_button_up_func() {}
void Screen::joy_axis_func() {}
void Screen::joy_config_func() {}
void Screen::user_event_func() {}
void Screen::native_menu_click_func() {}
void Screen::receive_signal(int signal, void *data) {}
void Screen::receive_signal(std::string const &signal, void *data) {}


std::vector<Screen *> Screen::screens;



bool Screen::signal_has_header(std::string header, std::string signal)
{
	return (signal.substr(0, header.length()) == header);
}

std::string Screen::strip_signal_header(std::string header, std::string signal)
{
	return signal.substr(header.length(), signal.length()-header.length());
	return "";
}
