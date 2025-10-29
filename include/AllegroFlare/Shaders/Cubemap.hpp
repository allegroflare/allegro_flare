#pragma once


#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Cubemap : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Cubemap";

      private:
         AllegroFlare::Cubemap* cube_map;
         AllegroFlare::Vec3D camera_position;
         AllegroFlare::Vec3D camera_viewing_direction;
         ALLEGRO_TRANSFORM object_placement_transform;
         bool reflecting;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         Cubemap(AllegroFlare::Cubemap* cube_map=nullptr, bool reflecting=true);
         virtual ~Cubemap();

         void set_cube_map(AllegroFlare::Cubemap* cube_map);
         void set_camera_position(AllegroFlare::Vec3D camera_position);
         void set_camera_viewing_direction(AllegroFlare::Vec3D camera_viewing_direction);
         void set_reflecting(bool reflecting);
         AllegroFlare::Cubemap* get_cube_map() const;
         AllegroFlare::Vec3D get_camera_position() const;
         AllegroFlare::Vec3D get_camera_viewing_direction() const;
         bool get_reflecting() const;
         virtual void activate() override;
         void set_object_placement(AllegroFlare::Placement3D* object_placement=nullptr);
      };
   }
}



