

#include <AllegroFlare/DialogSystem/Scenes/Basic.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace Scenes
{


Basic::Basic(std::string location_name, std::string background_image_identifier, std::string ambience_sound_effect_identifier)
   : AllegroFlare::DialogSystem::Scenes::Base(AllegroFlare::DialogSystem::Scenes::Basic::TYPE)
   , location_name(location_name)
   , background_image_identifier(background_image_identifier)
   , ambience_sound_effect_identifier(ambience_sound_effect_identifier)
{
}


Basic::~Basic()
{
}


void Basic::set_location_name(std::string location_name)
{
   this->location_name = location_name;
}


void Basic::set_background_image_identifier(std::string background_image_identifier)
{
   this->background_image_identifier = background_image_identifier;
}


void Basic::set_ambience_sound_effect_identifier(std::string ambience_sound_effect_identifier)
{
   this->ambience_sound_effect_identifier = ambience_sound_effect_identifier;
}


std::string Basic::get_location_name() const
{
   return location_name;
}


std::string Basic::get_background_image_identifier() const
{
   return background_image_identifier;
}


std::string Basic::get_ambience_sound_effect_identifier() const
{
   return ambience_sound_effect_identifier;
}




} // namespace Scenes
} // namespace DialogSystem
} // namespace AllegroFlare


