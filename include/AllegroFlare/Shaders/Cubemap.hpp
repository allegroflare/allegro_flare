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
         static constexpr int CUBEMAP_SHADER_UNIFORM_TEXTURE_INDEX = 5;
         static constexpr bool DEFAULT_REFLECTING = false;
         static constexpr char* CUBE_MAP_A_UNIFORM_IDENTIFIER = (char*)"cube_map_A";
         static constexpr char* CAMERA_POSITION_UNIFORM_IDENTIFIER = (char*)"camera_position";
         static constexpr char* CAMERA_VIEWING_DIRECTION_UNIFORM_IDENTIFIER = (char*)"camera_viewing_direction";
         static constexpr char* POSITION_TRANSFORM_UNIFORM_IDENTIFIER = (char*)"position_transform";
         static constexpr char* REFLECTING_UNIFORM_IDENTIFIER = (char*)"reflecting";
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
         Cubemap(AllegroFlare::Cubemap* cube_map=nullptr, bool reflecting=DEFAULT_REFLECTING);
         virtual ~Cubemap();

         AllegroFlare::Cubemap* get_cube_map() const;
         AllegroFlare::Vec3D get_camera_position() const;
         AllegroFlare::Vec3D get_camera_viewing_direction() const;
         bool get_reflecting() const;
         virtual void activate() override;
         void set_cube_map(AllegroFlare::Cubemap* cube_map=nullptr);
         void set_camera_position(AllegroFlare::Vec3D camera_position={});
         void set_camera_viewing_direction(AllegroFlare::Vec3D camera_viewing_direction={});
         void set_reflecting(bool reflecting=false);
         void set_object_placement(AllegroFlare::Placement3D* object_placement=nullptr);
      };
   }
}



