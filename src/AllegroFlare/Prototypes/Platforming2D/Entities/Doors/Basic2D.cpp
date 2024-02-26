

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Doors/Basic2D.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{
namespace Doors
{


Basic2D::Basic2D(std::string game_event_name_to_emit, std::string target_map_name, float target_spawn_x, float target_spawn_y)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , game_event_name_to_emit(game_event_name_to_emit)
   , target_map_name(target_map_name)
   , target_spawn_x(target_spawn_x)
   , target_spawn_y(target_spawn_y)
   , is_locked(false)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_game_event_name_to_emit(std::string game_event_name_to_emit)
{
   this->game_event_name_to_emit = game_event_name_to_emit;
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


void Basic2D::set_is_locked(bool is_locked)
{
   this->is_locked = is_locked;
}


std::string Basic2D::get_game_event_name_to_emit() const
{
   return game_event_name_to_emit;
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


bool Basic2D::get_is_locked() const
{
   return is_locked;
}




} // namespace Doors
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


