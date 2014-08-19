

#include <allegro_flare/display.h>
#include <allegro_flare/allegro_flare.h>



Display *Display::find_display(ALLEGRO_DISPLAY *display)
{
	for (unsigned i=0; i<displays.size(); i++)
		if (display == displays[i]->display) return displays[i];
	return NULL;
}



Display::Display(int width, int height, int display_flags)
	: _background_color(color::darkgoldenrod)
	, _width(width)
	, _height(height)
{
	//if (fullscreen) al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	al_set_new_display_flags(display_flags);
	//al_set_new_display_flags(display_flags | ALLEGRO_PROGRAMMABLE_PIPELINE);
	//al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE); // requires vsync to be OFF
 	display = al_create_display(width, height);
	displays.push_back(this);
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
