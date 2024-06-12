

#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshDriverCollisionResolver.hpp>

#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


TerrainMeshDriverCollisionResolver::TerrainMeshDriverCollisionResolver(AllegroFlare::Prototypes::TileDrive::TerrainMesh* tunnel_mesh, AllegroFlare::Vec3D* surfer_position, AllegroFlare::Vec3D* surfer_velocity)
   : tunnel_mesh(tunnel_mesh)
   , surfer_position(surfer_position)
   , surfer_velocity(surfer_velocity)
{
}


TerrainMeshDriverCollisionResolver::~TerrainMeshDriverCollisionResolver()
{
}


void TerrainMeshDriverCollisionResolver::set_tunnel_mesh(AllegroFlare::Prototypes::TileDrive::TerrainMesh* tunnel_mesh)
{
   this->tunnel_mesh = tunnel_mesh;
}


void TerrainMeshDriverCollisionResolver::set_surfer_position(AllegroFlare::Vec3D* surfer_position)
{
   this->surfer_position = surfer_position;
}


void TerrainMeshDriverCollisionResolver::set_surfer_velocity(AllegroFlare::Vec3D* surfer_velocity)
{
   this->surfer_velocity = surfer_velocity;
}


AllegroFlare::Prototypes::TileDrive::TerrainMesh* TerrainMeshDriverCollisionResolver::get_tunnel_mesh() const
{
   return tunnel_mesh;
}


AllegroFlare::Vec3D* TerrainMeshDriverCollisionResolver::get_surfer_position() const
{
   return surfer_position;
}


AllegroFlare::Vec3D* TerrainMeshDriverCollisionResolver::get_surfer_velocity() const
{
   return surfer_velocity;
}


void TerrainMeshDriverCollisionResolver::resolve_classic()
{
   surfer_position->x += surfer_velocity->x * 0.01;
   surfer_position->z += surfer_velocity->z * 0.01;
   return;
}

AllegroFlare::Physics::TileMapCollisionStepperStepResult TerrainMeshDriverCollisionResolver::resolve_basic()
{
   if (!(tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"tunnel_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"tunnel_mesh\" not met");
   }
   if (!(surfer_position))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"surfer_position\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"surfer_position\" not met");
   }
   if (!(surfer_velocity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"surfer_velocity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve_basic]: error: guard \"surfer_velocity\" not met");
   }
   AllegroFlare::Physics::TileMapCollisionStepperStepResult result;

   // set the result "before" data
   result.set_subject_position_before(AllegroFlare::Vec2D(surfer_position->x, surfer_position->z));
   result.set_subject_velocity_before(AllegroFlare::Vec2D(surfer_velocity->x, surfer_velocity->z));

   // make an AABB2D to represent the surfer
   float surfer_size = 0.2;
   float surfer_hsize = surfer_size * 0.5;
   AllegroFlare::Physics::AABB2D aabb2d(
      surfer_position->x - surfer_hsize,
      surfer_position->z - surfer_hsize,
      surfer_size,
      surfer_size,
      surfer_velocity->x * 0.01,
      surfer_velocity->z * 0.01
   );

   // create a collision stepper
   AllegroFlare::Physics::TileMapCollisionStepper collision_stepper(
      &tunnel_mesh->get_collision_tile_map_ref(), 
      &aabb2d,
      tunnel_mesh->obtain_tile_width(),
      tunnel_mesh->obtain_tile_height()
   );

   // TODO: replace the usage of this method with the AABB
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collision_infos =
      collision_stepper.get_stepped_tile_collisions(
         surfer_position->x - surfer_hsize,
         surfer_position->z - surfer_hsize,
         surfer_velocity->x * 0.01,
         surfer_velocity->z * 0.01,
         surfer_size,
         surfer_size,
         tunnel_mesh->obtain_tile_width(),
         tunnel_mesh->obtain_tile_height()
      );
   result.set_collisions(collision_infos);

   bool output_collision_debug_data = false;
   if (output_collision_debug_data && !collision_infos.empty())
   {
      std::cout << "COLLISIONS: " << collision_infos.size() << std::endl;
      std::cout << "  - [0] tile_value: " << collision_infos[0].get_tile_value() << std::endl;
      std::cout << "        coord_x:    " << collision_infos[0].get_collided_tile_coordinate().get_x() << std::endl;
      std::cout << "        coord_y:    " << collision_infos[0].get_collided_tile_coordinate().get_y() << std::endl;
      std::cout << "        prev_x:    " << surfer_position->x << std::endl;
      std::cout << "        prev_z:    " << surfer_position->z << std::endl;
      std::cout << "        new_x:    " << aabb2d.get_x() << std::endl;
      std::cout << "        new_z:    " << aabb2d.get_y() << std::endl;
   }

   // move the box by the velocity
   aabb2d.set_x(aabb2d.get_x() + aabb2d.get_velocity_x());
   aabb2d.set_y(aabb2d.get_y() + aabb2d.get_velocity_y());

   // reposition our surfer to the stepper-modified aabb2d
   surfer_position->x = aabb2d.get_x() + surfer_hsize;
   surfer_position->z = aabb2d.get_y() + surfer_hsize;
   surfer_velocity->x = (aabb2d.get_velocity_x() * 100);
   surfer_velocity->z = (aabb2d.get_velocity_y() * 100);

   // set the result "after" data
   result.set_subject_position_after(AllegroFlare::Vec2D(surfer_position->x, surfer_position->z));
   result.set_subject_velocity_after(AllegroFlare::Vec2D(surfer_velocity->x, surfer_velocity->z));
   result.set_subject_was_stopped_by_collision(false);

   return result;
}

AllegroFlare::Physics::TileMapCollisionStepperStepResult TerrainMeshDriverCollisionResolver::resolve()
{
   if (!(tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"tunnel_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"tunnel_mesh\" not met");
   }
   if (!(surfer_position))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"surfer_position\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"surfer_position\" not met");
   }
   if (!(surfer_velocity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"surfer_velocity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver::resolve]: error: guard \"surfer_velocity\" not met");
   }
   AllegroFlare::Physics::TileMapCollisionStepperStepResult result;

   // set the result "before" data
   result.set_subject_position_before(AllegroFlare::Vec2D(surfer_position->x, surfer_position->z));
   result.set_subject_velocity_before(AllegroFlare::Vec2D(surfer_velocity->x, surfer_velocity->z));

   // make an AABB2D to represent the surfer
   float surfer_size = 0.2;
   float surfer_hsize = surfer_size * 0.5;
   AllegroFlare::Physics::AABB2D aabb2d(
      surfer_position->x - surfer_hsize,
      surfer_position->z - surfer_hsize,
      surfer_size,
      surfer_size,
      surfer_velocity->x * 0.01,
      surfer_velocity->z * 0.01
   );

   // create a collision stepper
   AllegroFlare::Physics::TileMapCollisionStepper collision_stepper(
      &tunnel_mesh->get_collision_tile_map_ref(), 
      &aabb2d,
      tunnel_mesh->obtain_tile_width(),
      tunnel_mesh->obtain_tile_height()
   );

   // step the collision and collect the collision info
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collision_infos =
      collision_stepper.step();
   result.set_collisions(collision_infos);

   bool output_collision_debug_data = false;
   if (output_collision_debug_data && !collision_infos.empty())
   {
      std::cout << "COLLISIONS: " << collision_infos.size() << std::endl;
      std::cout << "  - [0] tile_value: " << collision_infos[0].get_tile_value() << std::endl;
      std::cout << "        coord_x:    " << collision_infos[0].get_collided_tile_coordinate().get_x() << std::endl;
      std::cout << "        coord_y:    " << collision_infos[0].get_collided_tile_coordinate().get_y() << std::endl;
      std::cout << "        prev_x:    " << surfer_position->x << std::endl;
      std::cout << "        prev_z:    " << surfer_position->z << std::endl;
      std::cout << "        new_x:    " << aabb2d.get_x() << std::endl;
      std::cout << "        new_z:    " << aabb2d.get_y() << std::endl;
   }

   // reposition our surfer to the stepper-modified aabb2d
   surfer_position->x = aabb2d.get_x() + surfer_hsize;
   surfer_position->z = aabb2d.get_y() + surfer_hsize;
   surfer_velocity->x = (aabb2d.get_velocity_x() * 100);
   surfer_velocity->z = (aabb2d.get_velocity_y() * 100);

   // set the result "after" data
   result.set_subject_position_after(AllegroFlare::Vec2D(surfer_position->x, surfer_position->z));
   result.set_subject_velocity_after(AllegroFlare::Vec2D(surfer_velocity->x, surfer_velocity->z));

   // set flag if subject was stopped by a collision during this step
   bool subject_was_stopped_by_collision = false;
   for (auto &collision_info : collision_infos)
   {
      if (collision_info.get_stopped_by_this_collision())
      {
         subject_was_stopped_by_collision = true;
         break;
      }
   }
   result.set_subject_was_stopped_by_collision(subject_was_stopped_by_collision);
     
   return result;
}


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


