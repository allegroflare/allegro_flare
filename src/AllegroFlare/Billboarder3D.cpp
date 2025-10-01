

#include <AllegroFlare/Billboarder3D.hpp>

#include <AllegroFlare/Useful.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Billboarder3D::Billboarder3D()
   : camera(nullptr)
{
}


Billboarder3D::~Billboarder3D()
{
}


void Billboarder3D::set_camera(AllegroFlare::Camera3D* camera)
{
   this->camera = camera;
}


AllegroFlare::Camera3D* Billboarder3D::get_camera() const
{
   return camera;
}


void Billboarder3D::set_billboard_placement(AllegroFlare::Placement3D* placement)
{
   if (!(placement))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Billboarder3D::set_billboard_placement]: error: guard \"placement\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Billboarder3D::set_billboard_placement]: error: guard \"placement\" not met");
   }
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Billboarder3D::set_billboard_placement]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Billboarder3D::set_billboard_placement]: error: guard \"camera\" not met");
   }
   // The camera's view matrix is built with rotations in the order Z, Y, X.
   // To make the object face the camera, its own rotation must match this sequence.
   placement->rotation_order = Placement3D::RotationOrder::ZYX;

   // Assign the camera's rotation values to the placement.
   // Placement3D expects rotation values in a [0, 1] unit range, so we must
   // convert the camera's values if they are in radians.
   placement->rotation.x = camera->tilt_in_unit_values
                         ? camera->tilt
                         : camera->tilt / AllegroFlare::TAU;

   placement->rotation.y = camera->spin_in_unit_values
                         ? camera->spin
                         : camera->spin / AllegroFlare::TAU;

   placement->rotation.z = camera->roll_in_unit_values
                         ? camera->roll
                         : camera->roll / AllegroFlare::TAU;

   return;
}


} // namespace AllegroFlare


