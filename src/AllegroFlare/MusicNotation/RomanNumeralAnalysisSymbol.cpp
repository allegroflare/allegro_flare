

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>




namespace AllegroFlare
{
namespace MusicNotation
{


RomanNumeralAnalysisSymbol::RomanNumeralAnalysisSymbol()
   : scale_degree(0)
   , chord_quality(RomanNumeralAnalysisSymbol::ChordQuality::UNDEFINED)
   , inversion(0)
   , extensions({})
{
}


RomanNumeralAnalysisSymbol::~RomanNumeralAnalysisSymbol()
{
}


void RomanNumeralAnalysisSymbol::set_scale_degree(int scale_degree)
{
   this->scale_degree = scale_degree;
}


void RomanNumeralAnalysisSymbol::set_chord_quality(RomanNumeralAnalysisSymbol::ChordQuality chord_quality)
{
   this->chord_quality = chord_quality;
}


void RomanNumeralAnalysisSymbol::set_inversion(int inversion)
{
   this->inversion = inversion;
}


void RomanNumeralAnalysisSymbol::set_extensions(std::vector<int> extensions)
{
   this->extensions = extensions;
}


int RomanNumeralAnalysisSymbol::get_scale_degree() const
{
   return scale_degree;
}


RomanNumeralAnalysisSymbol::ChordQuality RomanNumeralAnalysisSymbol::get_chord_quality() const
{
   return chord_quality;
}


int RomanNumeralAnalysisSymbol::get_inversion() const
{
   return inversion;
}


std::vector<int> RomanNumeralAnalysisSymbol::get_extensions() const
{
   return extensions;
}




} // namespace MusicNotation
} // namespace AllegroFlare


