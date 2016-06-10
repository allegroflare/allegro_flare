



#include <allegro_flare/display.h>

#include <allegro_flare/allegro_flare.h>




Display *Display::find_display(ALLEGRO_DISPLAY *al_display)
{
	for (unsigned i=0; i<displays.size(); i++)
		if (al_display == displays[i]->al_display) return displays[i];
	return NULL;
}




Display::Display(int width, int height, int display_flags)
	: _background_color(color::hex("abc788"))
	, _width(width)
	, _height(height)
	, al_display(NULL)
{
	// set a few options and flags
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
	al_set_new_display_flags(display_flags);

	// create the actual display
 	al_display = al_create_display(width, height);

	// add the display to AllegroFlare's list of displays
	displays.push_back(this);
}




void Display::display_close_func()
{
	Framework::shutdown_program = true;
}




std::vector<Display *> Display::displays;




int Display::width() { return _width; }
int Display::height() { return _height; }
float Display::middle() { return _height/2; }
float Display::center() { return _width/2; }




void Display::set_as_target_bitmap()
{
	al_set_target_bitmap(al_get_backbuffer(al_display));
}




void Display::flip()
{
	al_flip_display();
}




void Display::background_color(const ALLEGRO_COLOR &color)
{
	_background_color = color;
}




void Display::clear()
{
	// in theory, a user would never interface with the backbuffer,
	// they would only draw to sub-bitmaps of the backbuffer, each
	// sub-bitmap belonging to a Screen.  In this way, no transforms
	// or other projections would (should) ever be applied to the
	// backbuffer bitmap.  Clearing and drawing a quad would not be
	// "messed up" by any existing state

	ALLEGRO_BITMAP *bbuffer = al_get_backbuffer(al_display);
	ALLEGRO_COLOR lightened = color::mix(_background_color, color::white, 0.25);
	float w = al_get_bitmap_width(bbuffer);
	float h = al_get_bitmap_height(bbuffer);

	al_set_target_bitmap(bbuffer);

	al_clear_to_color(_background_color);


	ALLEGRO_VERTEX v[4] = {
		{0, 0, 0, 0, 0, _background_color},
		{0, h, 0, 0, 0, lightened},
		{w, h, 0, 0, 0, lightened},
		{w, 0, 0, 0, 0, _background_color},
	};

	al_draw_prim(&v[0], NULL, 0, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}




