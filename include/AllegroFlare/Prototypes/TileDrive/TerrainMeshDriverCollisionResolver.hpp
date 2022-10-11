#pragma once


#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class TerrainMeshDriverCollisionResolver
         {
         private:
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* tunnel_mesh;
            AllegroFlare::Vec3D* surfer_position;
            AllegroFlare::Vec3D* surfer_velocity;

         protected:


         public:
            TerrainMeshDriverCollisionResolver(AllegroFlare::Prototypes::TileDrive::TerrainMesh* tunnel_mesh=nullptr, AllegroFlare::Vec3D* surfer_position=nullptr, AllegroFlare::Vec3D* surfer_velocity=nullptr);
            ~TerrainMeshDriverCollisionResolver();

            void set_tunnel_mesh(AllegroFlare::Prototypes::TileDrive::TerrainMesh* tunnel_mesh);
            void set_surfer_position(AllegroFlare::Vec3D* surfer_position);
            void set_surfer_velocity(AllegroFlare::Vec3D* surfer_velocity);
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* get_tunnel_mesh() const;
            AllegroFlare::Vec3D* get_surfer_position() const;
            AllegroFlare::Vec3D* get_surfer_velocity() const;
            void resolve_classic();
            AllegroFlare::Physics::TileMapCollisionStepperStepResult resolve_basic();
            AllegroFlare::Physics::TileMapCollisionStepperStepResult resolve();
         };
      }
   }
}



