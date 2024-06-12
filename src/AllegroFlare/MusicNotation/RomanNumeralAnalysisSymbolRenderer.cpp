

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbolRenderer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


RomanNumeralAnalysisSymbolRenderer::RomanNumeralAnalysisSymbolRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol, float x, float y, int primary_symbol_font_size, int inversion_number_font_size)
   : font_bin(font_bin)
   , symbol(symbol)
   , x(x)
   , y(y)
   , primary_symbol_font_size(primary_symbol_font_size)
   , inversion_number_font_size(inversion_number_font_size)
{
}


RomanNumeralAnalysisSymbolRenderer::~RomanNumeralAnalysisSymbolRenderer()
{
}


void RomanNumeralAnalysisSymbolRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void RomanNumeralAnalysisSymbolRenderer::set_symbol(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol)
{
   this->symbol = symbol;
}


void RomanNumeralAnalysisSymbolRenderer::set_x(float x)
{
   this->x = x;
}


void RomanNumeralAnalysisSymbolRenderer::set_y(float y)
{
   this->y = y;
}


void RomanNumeralAnalysisSymbolRenderer::set_primary_symbol_font_size(int primary_symbol_font_size)
{
   this->primary_symbol_font_size = primary_symbol_font_size;
}


void RomanNumeralAnalysisSymbolRenderer::set_inversion_number_font_size(int inversion_number_font_size)
{
   this->inversion_number_font_size = inversion_number_font_size;
}


AllegroFlare::FontBin* RomanNumeralAnalysisSymbolRenderer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* RomanNumeralAnalysisSymbolRenderer::get_symbol() const
{
   return symbol;
}


float RomanNumeralAnalysisSymbolRenderer::get_x() const
{
   return x;
}


float RomanNumeralAnalysisSymbolRenderer::get_y() const
{
   return y;
}


int RomanNumeralAnalysisSymbolRenderer::get_primary_symbol_font_size() const
{
   return primary_symbol_font_size;
}


int RomanNumeralAnalysisSymbolRenderer::get_inversion_number_font_size() const
{
   return inversion_number_font_size;
}


void RomanNumeralAnalysisSymbolRenderer::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer::render]: error: guard \"font_bin\" not met");
   }
   if (!(symbol))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer::render]: error: guard \"symbol\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer::render]: error: guard \"symbol\" not met");
   }
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 1, 1, 1};

   // Render the primary symbol
   ALLEGRO_FONT* primary_symbol_font = obtain_primary_symbol_font();
   ALLEGRO_COLOR primary_symbol_color = color;
   float primary_symbol_x = x;
   float primary_symbol_y = y;
   al_draw_text(
      primary_symbol_font,
      primary_symbol_color,
      primary_symbol_x,
      primary_symbol_y,
      ALLEGRO_ALIGN_CENTER,
      symbol->infer_roman_numeral_string().c_str()
   );

   // Render the figured bass numbers
   float inversion_numbers_x = x;
   float inversion_numbers_y = y;

   return;
}

ALLEGRO_FONT* RomanNumeralAnalysisSymbolRenderer::obtain_primary_symbol_font()
{
   std::string font_identifier = "plantin-mt-light.ttf " + std::to_string(primary_symbol_font_size);
   return font_bin->operator[](font_identifier);
}

ALLEGRO_FONT* RomanNumeralAnalysisSymbolRenderer::obtain_inversion_number_font()
{
   std::string font_identifier = "plantin-mt-light.ttf " + std::to_string(inversion_number_font_size);
   return font_bin->operator[](font_identifier);
}


} // namespace MusicNotation
} // namespace AllegroFlare


