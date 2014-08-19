


#include <allegro_flare/screens/unicode_font_viewer_screen.h>

#include <allegro_flare/allegro_flare.h>






UnicodeFontViewerScreen::UnicodeFontViewerScreen(Display *display, std::string font_identifier_str)
	: Screen(display)
	, fonts("data/fonts")
	, unicode_font(fonts["Bravura.otf 40"])
	, ui_font(fonts["union__.ttf 20"])
	, ui_font_mini(fonts["union__.ttf 9"])
	, unicode_range_start(0x1D000)
{}




void UnicodeFontViewerScreen::draw_unicode_character(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
	static ALLEGRO_USTR *ustr = NULL;
	if (!ustr) ustr = al_ustr_new("");
	al_ustr_set_chr(ustr, 0, icon);
	al_draw_ustr(font, color, x, y, flags, ustr);
}




void UnicodeFontViewerScreen::primary_timer_func()
{
	int32_t unicode_range_end = unicode_range_start+0x00ff;

	al_draw_text(ui_font, color::green, 20, 20, ALLEGRO_FLAGS_EMPTY, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
	al_draw_text(ui_font, color::green, 20, 60, ALLEGRO_FLAGS_EMPTY, tostring("range " + tostring(unicode_range_start) + "-" + tostring(unicode_range_end)).c_str());

	//int y=90;
	int line = 0;
	int num_rows = 30;
	int line_height = 80;
	int row_width = 45;
	int row = 0;
	for (int32_t character=unicode_range_start; character<=unicode_range_end; character++)
	{
		int x = 100 + row*row_width;
		int y = 100 + line*line_height;
		draw_unicode_character(unicode_font, color::black, character, ALLEGRO_ALIGN_CENTER, x, y);
		al_draw_text(ui_font_mini, color::green, x, y, ALLEGRO_FLAGS_EMPTY, tostring(character).c_str());
		row += 1;
		if (row > num_rows) { row = 0; line++; }
	}
}




void UnicodeFontViewerScreen::key_char_func()
{
	switch(af::current_event->keyboard.keycode)
	{
	case ALLEGRO_KEY_RIGHT:
		unicode_range_start += 0x0100;
		break;
	case ALLEGRO_KEY_LEFT:
		unicode_range_start -= 0x0100;
		break;
	}
}

