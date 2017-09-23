#ifndef __AF_DRAWING_INTERFACE_HEADER
#define __AF_DRAWING_INTERFACE_HEADER




#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>




class DrawingInterface
{
private:
	std::string drawing_mode_name;

public:
	DrawingInterface(std::string drawing_mode_name);
	virtual ~DrawingInterface();
	std::string get_mode_name();

	// preparation and content
	virtual void prepare_surface(int surface_width, int surface_height) = 0;
	virtual void finish_surface() = 0;

	// files and output
	virtual std::string get_output() = 0;
	virtual bool save_file(std::string file_basename) = 0;

	// drawing primitives
	virtual void draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness) = 0;
	virtual void draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR outline_color, float thickness) = 0;
	virtual void draw_text(std::string text, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font=NULL) = 0;
	virtual void draw_ustr_chr(int32_t ustr_char, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font=NULL) = 0;
};




#endif
