

#include <Wicked/Entities/Basic3D.hpp>




namespace Wicked
{
namespace Entities
{


Basic3D::Basic3D()
   : Wicked::Entities::Base()
   , place()
   , velocity()
{
}


Basic3D::~Basic3D()
{
}


void Basic3D::set_place(AllegroFlare::Placement3D place)
{
   this->place = place;
}


void Basic3D::set_velocity(AllegroFlare::Placement3D velocity)
{
   this->velocity = velocity;
}


AllegroFlare::Placement3D Basic3D::get_place() const
{
   return place;
}


AllegroFlare::Placement3D Basic3D::get_velocity() const
{
   return velocity;
}


AllegroFlare::Placement3D &Basic3D::get_place_ref()
{
   return place;
}


AllegroFlare::Placement3D &Basic3D::get_velocity_ref()
{
   return velocity;
}


void Basic3D::TODO()
{
   // see Wicked/Entity for additional properties, notably "model"
   return;
}


} // namespace Entities
} // namespace Wicked


