

#include <allegro_flare/display.h>
#include <allegro_flare/allegro_flare.h>



Display *Display::find_display(ALLEGRO_DISPLAY *display)
{
	for (unsigned i=0; i<displays.size(); i++)
		if (display == displays[i]->display) return displays[i];
	return NULL;
}



Display::Display(int width, int height, int display_flags)
	: _background_color(color::hex("6ca3fe"))
	, _width(width)
	, _height(height)
{

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST); // hmm... not sure about this one either
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
//	al_set_new_display_flags(display_flags | ALLEGRO_OPENGL);	// Previously, OpenGL was forced because AllegroFlare
																// required certain specific features.  However,
																// now having the program run in OpenGL mode causes
																// offscreen bitmaps to not be drawn correctly. So
																// this feature has been removed.
	
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
