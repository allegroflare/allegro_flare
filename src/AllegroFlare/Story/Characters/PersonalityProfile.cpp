

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfile::PersonalityProfile(std::string character_name, std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions)
   : character_name(character_name)
   , personality_dimensions(personality_dimensions)
{
}


PersonalityProfile::~PersonalityProfile()
{
}


void PersonalityProfile::set_character_name(std::string character_name)
{
   this->character_name = character_name;
}


void PersonalityProfile::set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions)
{
   this->personality_dimensions = personality_dimensions;
}


std::string PersonalityProfile::get_character_name() const
{
   return character_name;
}


std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> PersonalityProfile::get_personality_dimensions() const
{
   return personality_dimensions;
}


AllegroFlare::Story::Characters::PersonalityProfileDimension PersonalityProfile::get_personality_dimension_by_index(std::size_t index)
{
   if (!((index >= 0)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfile::get_personality_dimension_by_index: error: guard \"(index >= 0)\" not met");
   }
   if (!((index < personality_dimensions.size())))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index < personality_dimensions.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfile::get_personality_dimension_by_index: error: guard \"(index < personality_dimensions.size())\" not met");
   }
   return personality_dimensions[index];
}

std::string PersonalityProfile::build_writeup_for_dimension(std::string character_name, std::string dimension_name, std::string dimension_description, uint32_t dimension_ranking_level, std::string dimension_descriptor_for_level)
{
   std::stringstream writeup;

   writeup << "In the personality category of \"" << dimension_name << "\" (" << dimension_description
           << "), " << character_name << " ranks " << ranking_level_to_text(dimension_ranking_level) << ", meaning "
           << character_name << " " << dimension_descriptor_for_level << ".";

   return writeup.str();
}

std::string PersonalityProfile::ranking_level_to_text(uint32_t ranking_level)
{
   if (!((ranking_level >= 0)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfile::ranking_level_to_text: error: guard \"(ranking_level >= 0)\" not met");
   }
   if (!((ranking_level < 5)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfile::ranking_level_to_text: error: guard \"(ranking_level < 5)\" not met");
   }
   std::map<uint32_t, std::string> dictionary = {
      { 0, "VERY_LOW" },
      { 1, "LOW" },
      { 2, "BALANCED" },
      { 3, "HIGH" },
      { 4, "VERY_HIGH" },
   };
   return dictionary[ranking_level];
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


