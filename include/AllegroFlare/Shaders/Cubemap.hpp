#pragma once


#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/Vec3D.hpp>
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
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         Cubemap(AllegroFlare::Cubemap* cube_map=nullptr, AllegroFlare::Vec3D camera_position=AllegroFlare::Vec3D(0, 0, 0));
         virtual ~Cubemap();

         void set_cube_map(AllegroFlare::Cubemap* cube_map);
         void set_camera_position(AllegroFlare::Vec3D camera_position);
         AllegroFlare::Cubemap* get_cube_map() const;
         AllegroFlare::Vec3D get_camera_position() const;
         virtual void activate() override;
      };
   }
}



