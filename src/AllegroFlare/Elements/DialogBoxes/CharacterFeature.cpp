

#include <AllegroFlare/Elements/DialogBoxes/CharacterFeature.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


CharacterFeature::CharacterFeature(std::string character_name, std::string description, std::string character_image_identifier, float duration)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::CharacterFeature::TYPE)
   , character_name(character_name)
   , description(description)
   , character_image_identifier(character_image_identifier)
   , duration(duration)
{
}


CharacterFeature::~CharacterFeature()
{
}


void CharacterFeature::set_character_name(std::string character_name)
{
   this->character_name = character_name;
}


void CharacterFeature::set_description(std::string description)
{
   this->description = description;
}


void CharacterFeature::set_character_image_identifier(std::string character_image_identifier)
{
   this->character_image_identifier = character_image_identifier;
}


void CharacterFeature::set_duration(float duration)
{
   this->duration = duration;
}


std::string CharacterFeature::get_character_name() const
{
   return character_name;
}


std::string CharacterFeature::get_description() const
{
   return description;
}


std::string CharacterFeature::get_character_image_identifier() const
{
   return character_image_identifier;
}


float CharacterFeature::get_duration() const
{
   return duration;
}




} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


