



#include <AllegroFlare/DrawingInterfaces/SVG.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp> // for escape_xml_chars(), as_hex()
#include <AllegroFlare/UsefulPHP.hpp>



using namespace AllegroFlare;



namespace AllegroFlare
{
namespace DrawingInterfaces
{



   SVG::SVG()
      : Base("DrawingInterfaces::SVG")
      //: current_drawing_mode(drawing_mode)
      //, current_document_output()
      //, current_canvas_id(next_html5_canvas_id++)
   {}



   SVG::~SVG()
   {}



   /*
   std::string SVG::get_xml_encoded_ustr(ALLEGRO_USTR *ustr)
   {
      std::stringstream output;
      //al_ustr_get(const ALLEGRO_USTR *ub, int pos)
      for (unsigned i=0; i<al_ustr_length(ustr); i++)
      {
         output << "&#x" << al_ustr_get(ustr, i) << ";";
      }
      return output.str();
   }
   */


   /*

#include <string>
#include <map>
#include <iostream>

   std::string SVG::escape_xml_chars(std::string xml)
   {
      std::map<char, std::string> transformations;
      transformations['&']  = std::string("&amp;");
      transformations['\''] = std::string("&apos;");
      transformations['"']  = std::string("&quot;");
      transformations['>']  = std::string("&gt;");
      transformations['<']  = std::string("&lt;");

      // Build list of characters to be searched for.
      //
      std::string reserved_chars;
      for (auto ti = transformations.begin(); ti != transformations.end(); ti++)
      {
         reserved_chars += ti->first;
      }

      size_t pos = 0;
      while (std::string::npos != (pos = xml.find_first_of(reserved_chars, pos)))
      {
         xml.replace(pos, 1, transformations[xml[pos]]);
         pos++;
      }

      return xml;
   }

   */


   /*
   std::string SVG::as_hex(int32_t num)
   {
      std::stringstream stream;
      stream << std::hex << num;
      return stream.str();
   }
   */


   /*
   std::string Base::get_canvas_id()
   {
      if (current_drawing_mode == HTML5_CANVAS) return std::string("canvas") + tostring(current_canvas_id);
   }
   */




   void SVG::prepare_surface(int surface_width, int surface_height)
   {
      current_document_output.clear();

      //current_document_output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << "\n";
      //current_document_output << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" baseProfile=\"basic\" id=\"svg-root\" width=\"100%\" height=\"100%\" viewBox=\"0 0 480 360\">" << "\n";
      current_document_output << "<svg width=\"" << surface_width << "\" height=\"" << surface_height << "\">" << "\n";
      //current_document_output << "<title id=\"test-title\">color-prop-01-b</title>" << "\n";
      //current_document_output << "<desc id=\"test-desc\">Test that viewer has the basic capability to process the color property</desc>" << "\n";
   }




   void SVG::draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
   {
      current_document_output << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"stroke: " << color::get_css_str(color) << "; stroke-width: " << thickness << ";\" />" << "\n";
   }




   void SVG::draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR outline_color, float thickness)
   {
      current_document_output << "<rect x=\"" << x1 << "\" y=\"" << y1 << "\" width=\"" << (x2-x1) << "\" height=\"" << (y2-y1) << "\" style=\"stroke: " << color::get_css_str(outline_color) << "; fill: none; stroke-width: " << thickness << ";\" />" << "\n";
   }




   void SVG::draw_text(std::string text, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
   {
      current_document_output << "<text x=\"" << x << "\" y=\"" << y << "\" font-family=\"" << font_family << "\" font-size=\"" << (font_size/4) << "px\" fill=\"" << color::get_css_str(color) << "\">" << escape_xml_chars(text) << "</text>" << "\n";
   }




   void SVG::draw_ustr_chr(int32_t ustr_char, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
   {
      current_document_output << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-family: " << font_family << "; font-size:" << (font_size/4) << "px; fill:" << color::get_css_str(color) << ";\">&#x" << as_hex(ustr_char) << ";</text>" << "\n";
   }




   void SVG::finish_surface()
   {
      current_document_output << "</svg>" << "\n";
   }




   bool SVG::save_file(std::string file_basename)
   {
      return php::file_put_contents(file_basename + ".svg", get_output());
   }




   std::string SVG::get_output()
   {
      return current_document_output.str();
   }




} // namespace DrawingInterfaces
} // namespace AllegroFlare



