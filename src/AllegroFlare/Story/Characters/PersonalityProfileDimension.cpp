

#include <AllegroFlare/Story/Characters/PersonalityProfileDimension.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfileDimension::PersonalityProfileDimension(std::string title, std::string description, int scoring, int scoring_max, std::string scoring_descriptor)
   : title(title)
   , description(description)
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


void PersonalityProfileDimension::set_description(std::string description)
{
   this->description = description;
}


void PersonalityProfileDimension::set_scoring(int scoring)
{
   this->scoring = scoring;
}


void PersonalityProfileDimension::set_scoring_max(int scoring_max)
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


std::string PersonalityProfileDimension::get_description() const
{
   return description;
}


int PersonalityProfileDimension::get_scoring() const
{
   return scoring;
}


int PersonalityProfileDimension::get_scoring_max() const
{
   return scoring_max;
}


std::string PersonalityProfileDimension::get_scoring_descriptor() const
{
   return scoring_descriptor;
}


float PersonalityProfileDimension::get_scoring_normalized()
{
   if (!((scoring_max != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileDimension::get_scoring_normalized]: error: guard \"(scoring_max != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileDimension::get_scoring_normalized]: error: guard \"(scoring_max != 0)\" not met");
   }
   return scoring / (float)scoring_max;
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


