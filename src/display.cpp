

#include <allegro_flare/display.h>
#include <allegro_flare/allegro_flare.h>



Display *Display::find_display(ALLEGRO_DISPLAY *display)
{
	for (unsigned i=0; i<displays.size(); i++)
		if (display == displays[i]->display) return displays[i];
	return NULL;
}



Display::Display(int width, int height, int display_flags)
	: _background_color(color::hex("abc788"))
	, _width(width)
	, _height(height)
{
	// set a few options and flags
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST); // hmm... not sure about this one either
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
	al_set_new_display_flags(display_flags);

	// create the actual display
 	display = al_create_display(width, height);

	// add the display to AllegroFlare's list of displays
	displays.push_back(this);

	// HACK: This is a sanity check.  When using an AMD Radeon HD 7670M on my system,
	// newly created displays are positioned offscren, at (32767, 32767).
	// In the event that this occurs, then a display will be repositioned
	// back to a sane coordinate on the desktop.
	int dx, dy;
	al_get_window_position(display, &dx, &dy);
	if (dx >= 1920 || dy >= 1080)
	{
		std::cout << "Display positioned at (" << dx << ", " << dy << ")." << std::endl;

		int new_pos_x = 1920/2 - width/2;
		int new_pos_y = 1080/2 - height/2;

		std::cout << "Repositioning display to (" << new_pos_x << ", " << new_pos_y << ")" << std::endl;
		al_set_window_position(display, new_pos_x, new_pos_y);
	}

}



void Display::display_close_func()
{
	af::shutdown_program = true;
}



std::vector<Display *> Display::displays;



int Display::width() { return _width; }
int Display::height() { return _height; }
float Display::middle() { return _height/2; }
float Display::center() { return _width/2; }



void Display::set_as_target_bitmap()
{
	al_set_target_bitmap(al_get_backbuffer(display));
}



void Display::flip()
{
	al_flip_display();
}


void Display::background_color(const ALLEGRO_COLOR &color)
{
	_background_color = color;
}
