

#include <AllegroFlare/AcousticEnvironments/Reverb.hpp>

#include <allegro5/allegro_audio.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AcousticEnvironments
{


Reverb::Reverb(std::string property)
   : AllegroFlare::AcousticEnvironments::Base(AllegroFlare::AcousticEnvironments::Reverb::TYPE)
   , property(property)
   , master_mixer(nullptr)
   , initialized(false)
{
}


Reverb::~Reverb()
{
}


std::string Reverb::get_property() const
{
   return property;
}


void Reverb::initialize()
{
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   master_mixer = al_get_default_mixer();
   initialized = true;
   return;
}


} // namespace AcousticEnvironments
} // namespace AllegroFlare


