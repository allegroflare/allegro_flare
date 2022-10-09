#pragma once


#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class TunnelMeshSurferCollisionResolver
         {
         private:
            AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh;
            AllegroFlare::Vec3D* surfer_position;
            AllegroFlare::Vec3D* surfer_velocity;

         protected:


         public:
            TunnelMeshSurferCollisionResolver(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh=nullptr, AllegroFlare::Vec3D* surfer_position=nullptr, AllegroFlare::Vec3D* surfer_velocity=nullptr);
            ~TunnelMeshSurferCollisionResolver();

            void set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh);
            void set_surfer_position(AllegroFlare::Vec3D* surfer_position);
            void set_surfer_velocity(AllegroFlare::Vec3D* surfer_velocity);
            AllegroFlare::Prototypes::MindDive::TunnelMesh* get_tunnel_mesh() const;
            AllegroFlare::Vec3D* get_surfer_position() const;
            AllegroFlare::Vec3D* get_surfer_velocity() const;
            void resolve_classic();
            AllegroFlare::Physics::TileMapCollisionStepperStepResult resolve_basic();
            AllegroFlare::Physics::TileMapCollisionStepperStepResult resolve();
         };
      }
   }
}



