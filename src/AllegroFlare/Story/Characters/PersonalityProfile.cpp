

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>




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




} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


