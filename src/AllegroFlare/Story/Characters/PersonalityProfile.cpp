

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>




namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfile::PersonalityProfile(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions)
   : dimensions(dimensions)
{
}


PersonalityProfile::~PersonalityProfile()
{
}


void PersonalityProfile::set_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions)
{
   this->dimensions = dimensions;
}


std::vector<AllegroFlare::Story::Characters::PersonalityDimension> PersonalityProfile::get_dimensions() const
{
   return dimensions;
}




} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


