

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfile::PersonalityProfile(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> personality_dimensions)
   : personality_dimensions(personality_dimensions)
{
}


PersonalityProfile::~PersonalityProfile()
{
}


void PersonalityProfile::set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> personality_dimensions)
{
   this->personality_dimensions = personality_dimensions;
}


std::vector<AllegroFlare::Story::Characters::PersonalityDimension> PersonalityProfile::get_personality_dimensions() const
{
   return personality_dimensions;
}


AllegroFlare::Story::Characters::PersonalityDimension PersonalityProfile::get_personality_dimension_by_index(std::size_t index)
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


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


