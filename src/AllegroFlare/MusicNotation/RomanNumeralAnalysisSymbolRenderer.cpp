

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbolRenderer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


RomanNumeralAnalysisSymbolRenderer::RomanNumeralAnalysisSymbolRenderer(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol)
   : symbol(symbol)
{
}


RomanNumeralAnalysisSymbolRenderer::~RomanNumeralAnalysisSymbolRenderer()
{
}


void RomanNumeralAnalysisSymbolRenderer::set_symbol(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol)
{
   this->symbol = symbol;
}


AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* RomanNumeralAnalysisSymbolRenderer::get_symbol() const
{
   return symbol;
}


void RomanNumeralAnalysisSymbolRenderer::render()
{
   if (!(symbol))
   {
      std::stringstream error_message;
      error_message << "[RomanNumeralAnalysisSymbolRenderer::render]: error: guard \"symbol\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("RomanNumeralAnalysisSymbolRenderer::render: error: guard \"symbol\" not met");
   }
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare


