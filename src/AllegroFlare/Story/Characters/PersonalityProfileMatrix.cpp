

#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfileMatrix::PersonalityProfileMatrix(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions)
   : dimensions(dimensions)
{
}


PersonalityProfileMatrix::~PersonalityProfileMatrix()
{
}


void PersonalityProfileMatrix::set_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions)
{
   this->dimensions = dimensions;
}


std::vector<AllegroFlare::Story::Characters::PersonalityDimension> PersonalityProfileMatrix::get_dimensions() const
{
   return dimensions;
}


std::size_t PersonalityProfileMatrix::num_dimensions()
{
   return dimensions.size();
}

AllegroFlare::Story::Characters::PersonalityDimension PersonalityProfileMatrix::get_personality_dimension_by_index(std::size_t index)
{
   if (!((index >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileMatrix::get_personality_dimension_by_index]: error: guard \"(index >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileMatrix::get_personality_dimension_by_index]: error: guard \"(index >= 0)\" not met");
   }
   if (!((index < dimensions.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileMatrix::get_personality_dimension_by_index]: error: guard \"(index < dimensions.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileMatrix::get_personality_dimension_by_index]: error: guard \"(index < dimensions.size())\" not met");
   }
   return dimensions[index];
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


