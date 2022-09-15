

#include <Wicked/Entities/Doors/Basic2D.hpp>




namespace Wicked
{
namespace Entities
{
namespace Doors
{


Basic2D::Basic2D(std::string target_map_name, float target_spawn_x, float target_spawn_y)
   : Wicked::Entities::Basic2D()
   , target_map_name(target_map_name)
   , target_spawn_x(target_spawn_x)
   , target_spawn_y(target_spawn_y)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_target_map_name(std::string target_map_name)
{
   this->target_map_name = target_map_name;
}


void Basic2D::set_target_spawn_x(float target_spawn_x)
{
   this->target_spawn_x = target_spawn_x;
}


void Basic2D::set_target_spawn_y(float target_spawn_y)
{
   this->target_spawn_y = target_spawn_y;
}


std::string Basic2D::get_target_map_name() const
{
   return target_map_name;
}


float Basic2D::get_target_spawn_x() const
{
   return target_spawn_x;
}


float Basic2D::get_target_spawn_y() const
{
   return target_spawn_y;
}


std::string Basic2D::run()
{
   return "Hello World!";
}


} // namespace Doors
} // namespace Entities
} // namespace Wicked


