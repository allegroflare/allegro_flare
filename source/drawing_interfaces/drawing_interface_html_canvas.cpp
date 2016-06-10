



#include <allegro_flare/drawing_interfaces/drawing_interface_html_canvas.h>

#include <allegro_flare/color.h> 
#include <allegro_flare/useful.h> 
#include <allegro_flare/useful_php.h> 




int DrawingInterfaceHTMLCanvas::next_html5_canvas_id = 1;




DrawingInterfaceHTMLCanvas::DrawingInterfaceHTMLCanvas()
	: DrawingInterface("html5 canvas")
{}




std::string DrawingInterfaceHTMLCanvas::get_canvas_id()
{
	return std::string("canvas") + tostring(current_canvas_id);
}




void DrawingInterfaceHTMLCanvas::prepare_surface(int surface_width, int surface_height)
{
	current_document_output.clear();

	current_document_output << "<canvas id=\"" << get_canvas_id() << "\" width=\"" << surface_width << "\" height=\"" << surface_height << " style=\"border: 1px solid black;\"></canvas>\n";
	current_document_output << "<script type=\"text/javascript\">\n";
	current_document_output << "var canvas = document.getElementById(\"" << get_canvas_id() << "\");\n";
	current_document_output << "var context = canvas.getContext(\"2d\");\n";
	current_document_output << "\n";
}




void DrawingInterfaceHTMLCanvas::draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
{
	current_document_output << "context.beginPath();" << "\n";
	current_document_output << "context.moveTo(" << x1 << ", " << y1 << ");" << "\n";
	current_document_output << "context.lineTo(" << x2 << ", " << y2 << ");" << "\n";
	current_document_output << "context.strokeStyle=\"" << color::get_css_str(color) << "\";" << "\n";
	current_document_output << "context.lineWidth=\"" << thickness << "\";" << "\n";
	current_document_output << "context.stroke();" << "\n";
	current_document_output << "\n";
}




void DrawingInterfaceHTMLCanvas::draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR outline_color, float thickness)
{
	current_document_output << "context.strokeStyle=\"" << color::get_css_str(outline_color) << "\";" << "\n";
	current_document_output << "context.lineWidth=\"" << thickness << "\";" << "\n";
	current_document_output << "context.strokeRect(" << x1 << ", " << y1 << ", " << (x2-x1) << ", " << (y2-y1) << ");" << "\n";
	current_document_output << "\n";
}




void DrawingInterfaceHTMLCanvas::draw_text(std::string text, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
{
	current_document_output << "context.fillStyle=\"" << color::get_css_str(color) << "\";" << "\n";
	current_document_output << "context.font=\"" << (font_size/4) << "px " << font_family << "\";" << "\n";
	current_document_output << "context.fillText(\"" << text << "\", " << x << ", " << y << ");" << "\n";
	current_document_output << "\n";
}




void DrawingInterfaceHTMLCanvas::draw_ustr_chr(int32_t ustr_char, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
{
	current_document_output << "context.fillStyle=\"" << color::get_css_str(color) << "\";" << "\n";
	current_document_output << "context.font=\"" << (font_size/4) << "px " << font_family << "\";" << "\n";
	current_document_output << "context.fillText(String.fromCharCode(" << ustr_char << "), " << x << ", " << y << ");" << "\n";
	current_document_output << "\n";
}




void DrawingInterfaceHTMLCanvas::finish_surface()
{
	current_document_output << "</script>" << "\n";
}




bool DrawingInterfaceHTMLCanvas::save_file(std::string file_basename)
{
	std::string filename = file_basename + ".canvas.html";

	if (php::file_exists(filename)) al_remove_filename(file_basename.c_str());
	php::file_put_contents(filename, get_output());

	return true;
}




std::string DrawingInterfaceHTMLCanvas::get_output()
{
	return current_document_output.str();
}




