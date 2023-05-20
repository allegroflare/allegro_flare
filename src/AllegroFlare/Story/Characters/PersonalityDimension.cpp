

#include <AllegroFlare/Story/Characters/PersonalityDimension.hpp>




namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityDimension::PersonalityDimension(std::string name, std::string description, std::string descriptor_very_low, std::string descriptor_low, std::string descriptor_medium, std::string descriptor_high, std::string descriptor_very_high)
   : name(name)
   , description(description)
   , descriptor_very_low(descriptor_very_low)
   , descriptor_low(descriptor_low)
   , descriptor_medium(descriptor_medium)
   , descriptor_high(descriptor_high)
   , descriptor_very_high(descriptor_very_high)
{
}


PersonalityDimension::~PersonalityDimension()
{
}


void PersonalityDimension::set_name(std::string name)
{
   this->name = name;
}


void PersonalityDimension::set_description(std::string description)
{
   this->description = description;
}


void PersonalityDimension::set_descriptor_very_low(std::string descriptor_very_low)
{
   this->descriptor_very_low = descriptor_very_low;
}


void PersonalityDimension::set_descriptor_low(std::string descriptor_low)
{
   this->descriptor_low = descriptor_low;
}


void PersonalityDimension::set_descriptor_medium(std::string descriptor_medium)
{
   this->descriptor_medium = descriptor_medium;
}


void PersonalityDimension::set_descriptor_high(std::string descriptor_high)
{
   this->descriptor_high = descriptor_high;
}


void PersonalityDimension::set_descriptor_very_high(std::string descriptor_very_high)
{
   this->descriptor_very_high = descriptor_very_high;
}


std::string PersonalityDimension::get_name() const
{
   return name;
}


std::string PersonalityDimension::get_description() const
{
   return description;
}


std::string PersonalityDimension::get_descriptor_very_low() const
{
   return descriptor_very_low;
}


std::string PersonalityDimension::get_descriptor_low() const
{
   return descriptor_low;
}


std::string PersonalityDimension::get_descriptor_medium() const
{
   return descriptor_medium;
}


std::string PersonalityDimension::get_descriptor_high() const
{
   return descriptor_high;
}


std::string PersonalityDimension::get_descriptor_very_high() const
{
   return descriptor_very_high;
}




} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


