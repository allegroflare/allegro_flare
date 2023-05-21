

#include <AllegroFlare/Story/Characters/PersonalityProfileDimension.hpp>




namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfileDimension::PersonalityProfileDimension(std::string title, uint32_t scoring, uint32_t scoring_max, std::string scoring_descriptor)
   : title(title)
   , scoring(scoring)
   , scoring_max(scoring_max)
   , scoring_descriptor(scoring_descriptor)
{
}


PersonalityProfileDimension::~PersonalityProfileDimension()
{
}


void PersonalityProfileDimension::set_title(std::string title)
{
   this->title = title;
}


void PersonalityProfileDimension::set_scoring(uint32_t scoring)
{
   this->scoring = scoring;
}


void PersonalityProfileDimension::set_scoring_max(uint32_t scoring_max)
{
   this->scoring_max = scoring_max;
}


void PersonalityProfileDimension::set_scoring_descriptor(std::string scoring_descriptor)
{
   this->scoring_descriptor = scoring_descriptor;
}


std::string PersonalityProfileDimension::get_title() const
{
   return title;
}


uint32_t PersonalityProfileDimension::get_scoring() const
{
   return scoring;
}


uint32_t PersonalityProfileDimension::get_scoring_max() const
{
   return scoring_max;
}


std::string PersonalityProfileDimension::get_scoring_descriptor() const
{
   return scoring_descriptor;
}


float PersonalityProfileDimension::get_scoring_normalized()
{
   return scoring / (float)scoring_max;
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


