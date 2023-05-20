

#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>




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




} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


