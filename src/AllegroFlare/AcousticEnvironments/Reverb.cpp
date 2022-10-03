

#include <AllegroFlare/AcousticEnvironments/Reverb.hpp>




namespace AllegroFlare
{
namespace AcousticEnvironments
{


Reverb::Reverb(std::string property)
   : AllegroFlare::AcousticEnvironments::Base(AllegroFlare::AcousticEnvironments::Reverb::TYPE)
   , property(property)
{
}


Reverb::~Reverb()
{
}


std::string Reverb::get_property() const
{
   return property;
}


bool Reverb::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace AcousticEnvironments
} // namespace AllegroFlare


