#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Physics/CollisionMeshFace.hpp>
#include <AllegroFlare/StableVectorStr.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class CollisionMesh
      {
      private:
         AllegroFlare::Model3D* model;
         std::vector<AllegroFlare::Physics::CollisionMeshFace> faces;
         AllegroFlare::StableVectorStr<AllegroFlare::Physics::CollisionMeshFace> dynamic_faces;
         bool loaded;

      protected:


      public:
         CollisionMesh();
         ~CollisionMesh();

         void set_model(AllegroFlare::Model3D* model);
         bool get_loaded() const;
         int get_num_faces();
         std::vector<AllegroFlare::Physics::CollisionMeshFace>& get_faces_ref();
         std::vector<AllegroFlare::Physics::CollisionMeshFace>& get_dynamic_faces_ref();
         void add_dynamic_face(std::string name="[unset-name]", AllegroFlare::Physics::CollisionMeshFace face={});
         void activate_dynamic_face(std::string name="[unset-name]");
         void deactivate_dynamic_face(std::string name="[unset-name]");
         bool is_dynamic_face_active(std::string name="[unset-name]");
         bool dynamic_face_exists(std::string name="[unset-name]");
         void load();
         std::vector<std::string> load_dynamic_faces(std::string root_name="[unset-root_name]", AllegroFlare::Model3D* model=nullptr);
         void draw(ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6}, ALLEGRO_COLOR dynamic_faces_color_on=ALLEGRO_COLOR{0.7, 0.55, 0.5, 0.7}, ALLEGRO_COLOR dynamic_faces_color_off=ALLEGRO_COLOR{0.7*0.35, 0.55*0.35, 0.5*0.35, 0.7*0.35});
         static ALLEGRO_VERTEX _create_vtx(AllegroFlare::Vec3D vec={}, ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6});
      };
   }
}



