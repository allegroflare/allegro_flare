

#include <AllegroFlare/Story/Characters/PersonalityDimension.hpp>

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


PersonalityDimension::PersonalityDimension(std::string name, std::string description, std::string descriptor_very_low, std::string descriptor_low, std::string descriptor_balanced, std::string descriptor_high, std::string descriptor_very_high)
   : name(name)
   , description(description)
   , descriptor_very_low(descriptor_very_low)
   , descriptor_low(descriptor_low)
   , descriptor_balanced(descriptor_balanced)
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


void PersonalityDimension::set_descriptor_balanced(std::string descriptor_balanced)
{
   this->descriptor_balanced = descriptor_balanced;
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


std::string PersonalityDimension::get_descriptor_balanced() const
{
   return descriptor_balanced;
}


std::string PersonalityDimension::get_descriptor_high() const
{
   return descriptor_high;
}


std::string PersonalityDimension::get_descriptor_very_high() const
{
   return descriptor_very_high;
}


std::string PersonalityDimension::get_descriptor_for_level(uint32_t ranking_level)
{
   if (!((ranking_level >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityDimension::get_descriptor_for_level]: error: guard \"(ranking_level >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityDimension::get_descriptor_for_level]: error: guard \"(ranking_level >= 0)\" not met");
   }
   if (!((ranking_level < 5)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityDimension::get_descriptor_for_level]: error: guard \"(ranking_level < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityDimension::get_descriptor_for_level]: error: guard \"(ranking_level < 5)\" not met");
   }
   std::map<uint32_t, std::string> dictionary = {
      { 0, descriptor_very_low },
      { 1, descriptor_low },
      { 2, descriptor_balanced },
      { 3, descriptor_high },
      { 4, descriptor_very_high },
   };
   return dictionary[ranking_level];
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


