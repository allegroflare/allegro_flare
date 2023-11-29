

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>

#include <AllegroFlare/Logger.hpp>
#include <algorithm>
#include <map>


namespace AllegroFlare
{
namespace MusicNotation
{


RomanNumeralAnalysisSymbol::RomanNumeralAnalysisSymbol()
   : scale_degree(0)
   , accidental(0)
   , chord_quality(RomanNumeralAnalysisSymbol::ChordQuality::UNDEFINED)
   , extensions({})
   , inversion(0)
{
}


RomanNumeralAnalysisSymbol::~RomanNumeralAnalysisSymbol()
{
}


void RomanNumeralAnalysisSymbol::set_scale_degree(int scale_degree)
{
   this->scale_degree = scale_degree;
}


void RomanNumeralAnalysisSymbol::set_accidental(int accidental)
{
   this->accidental = accidental;
}


void RomanNumeralAnalysisSymbol::set_chord_quality(RomanNumeralAnalysisSymbol::ChordQuality chord_quality)
{
   this->chord_quality = chord_quality;
}


void RomanNumeralAnalysisSymbol::set_extensions(std::vector<std::pair<int, int>> extensions)
{
   this->extensions = extensions;
}


void RomanNumeralAnalysisSymbol::set_inversion(int inversion)
{
   this->inversion = inversion;
}


int RomanNumeralAnalysisSymbol::get_scale_degree() const
{
   return scale_degree;
}


int RomanNumeralAnalysisSymbol::get_accidental() const
{
   return accidental;
}


RomanNumeralAnalysisSymbol::ChordQuality RomanNumeralAnalysisSymbol::get_chord_quality() const
{
   return chord_quality;
}


std::vector<std::pair<int, int>> RomanNumeralAnalysisSymbol::get_extensions() const
{
   return extensions;
}


int RomanNumeralAnalysisSymbol::get_inversion() const
{
   return inversion;
}


std::vector<std::pair<int, int>> RomanNumeralAnalysisSymbol::calculate_root_position_figured_bass_notes_with_extensions()
{
   std::vector<std::pair<int, int>> result;

   // Add the notes to the chord
   switch(chord_quality)
   {
      case UNDEFINED:
         result.push_back({0, 0});
      break;

      case MAJOR:
         result.push_back({0, 0});
         result.push_back({2, 0});
         result.push_back({7, 0});
      break;

      case MINOR:
         result.push_back({0, 0});
         result.push_back({2, -1});
         result.push_back({4, 0});
      break;

      case DIMINISHED:
         result.push_back({0, 0});
         result.push_back({2, -1});
         result.push_back({4, -1});
      break;

      case AUGMENTED:
         result.push_back({0, 0});
         result.push_back({2, 1});
         result.push_back({4, 1});
      break;
   }

   // Add the extensions
   for (auto &extension : extensions)
   {
      result.push_back(extension);
   }

   // Rotate based on the inversion
   int modded_inversion = inversion % result.size();
   std::rotate(result.begin(), result.begin() + modded_inversion, result.end());

   return result;
}

std::string RomanNumeralAnalysisSymbol::infer_roman_numeral_string()
{
   std::map<int, std::string> major_map = {
      { 0,   "I" },
      { 1,   "II" },
      { 2,   "III" },
      { 3,   "IV" },
      { 4,   "V" },
      { 5,   "VI" },
      { 6,   "VII" },
      { 7,   "VIII" },
      { 8,   "IX" },
      { 9,   "X" },
      { 10,  "XII" },
      { 11,  "XIII" },
   };
   std::map<int, std::string> minor_map = {
      { 0,   "i" },
      { 1,   "ii" },
      { 2,   "iii" },
      { 3,   "iv" },
      { 4,   "v" },
      { 5,   "vi" },
      { 6,   "vii" },
      { 7,   "viii" },
      { 8,   "ix" },
      { 9,   "x" },
      { 10,  "xii" },
      { 11,  "xiii" },
   };


   bool uses_major_map = (chord_quality == UNDEFINED || chord_quality == MAJOR || chord_quality == AUGMENTED); 
   bool uses_minor_map = (chord_quality == MINOR || chord_quality == DIMINISHED); 
   std::string result;

   if (uses_major_map)
   {
      if (major_map.count(scale_degree) == 0)
      {
         // item not found
         AllegroFlare::Logger::throw_error("AllegroFlare::MusicNotation::RomanNumeralAnalysysSymbol",
                                         "Cannot load the item with the identifier \"" + std::to_string(scale_degree)
                                         + "\", in the major_map, it does not exist.");
      }
      else
      {
         result = major_map[scale_degree];
      }
   }
   else if(uses_minor_map)
   {
      if (minor_map.count(scale_degree) == 0)
      {
         // item not found
         AllegroFlare::Logger::throw_error("AllegroFlare::MusicNotation::RomanNumeralAnalysysSymbol",
                                         "Cannot load the item with the identifier \"" + std::to_string(scale_degree)
                                         + "\", in the minor_map, it does not exist.");
      }
      else
      {
         result = minor_map[scale_degree];
      }
   }
   else
   {
      // neither the major_map or the minor_map was found to be used
      AllegroFlare::Logger::throw_error("AllegroFlare::MusicNotation::RomanNumeralAnalysysSymbol",
                                      "Could not calculate if minor map or major map should be used.");
   }

   return result;
}


} // namespace MusicNotation
} // namespace AllegroFlare


