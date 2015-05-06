#ifndef __AF_UNICODE_FONT_VIEWER_SCREEN
#define __AF_UNICODE_FONT_VIEWER_SCREEN




//#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/screen.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/bins/font_bin.h>


class UnicodeFontViewerScreen : public Screen
{
private:
	FontBin fonts;
	ALLEGRO_FONT *unicode_font, *ui_font, *ui_font_mini;
	int32_t unicode_range_start;

public:
	UnicodeFontViewerScreen(Display *display, std::string font_identifier_str);

	void draw_unicode_character(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y);

	void primary_timer_func();// override;

	void key_char_func();// override;
};




#endif