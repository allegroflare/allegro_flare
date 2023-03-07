

#include <AllegroFlare/VirtualControllers/GenericController.hpp>




namespace AllegroFlare
{
namespace VirtualControllers
{


GenericController::GenericController()
   : AllegroFlare::VirtualControllers::Base(AllegroFlare::VirtualControllers::GenericController::TYPE, AllegroFlare::VirtualControllers::GenericController::DEFAULT_NAME)
   , primary_stick_position()
   , secondary_stick_position()
{
}


GenericController::~GenericController()
{
}


void GenericController::set_primary_stick_position(AllegroFlare::Vec2D primary_stick_position)
{
   this->primary_stick_position = primary_stick_position;
}


void GenericController::set_secondary_stick_position(AllegroFlare::Vec2D secondary_stick_position)
{
   this->secondary_stick_position = secondary_stick_position;
}


AllegroFlare::Vec2D GenericController::get_primary_stick_position() const
{
   return primary_stick_position;
}


AllegroFlare::Vec2D GenericController::get_secondary_stick_position() const
{
   return secondary_stick_position;
}




} // namespace VirtualControllers
} // namespace AllegroFlare


