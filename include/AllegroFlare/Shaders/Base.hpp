#pragma once


#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Base : public AllegroFlare::Shader
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Base";

      private:
         std::string type;
         std::string vertex_source_code;
         std::string fragment_source_code;

      protected:


      public:
         Base(std::string type=AllegroFlare::Shaders::Base::TYPE, std::string vertex_source_code="", std::string fragment_source_code="");
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
         static bool set_sampler(std::string name="[unset-name]", ALLEGRO_BITMAP* bitmap=nullptr, int unit=0);
         static bool set_mat4(std::string name="[unset-name]", ALLEGRO_TRANSFORM* transform=nullptr);
         static bool set_int(std::string name="[unset-name]", int value=0);
         static bool set_float(std::string name="[unset-name]", float value=0.0f);
         static bool set_bool(std::string name="[unset-name]", bool value=false);
         static bool set_vec2(std::string name="[unset-name]", float x=0.0f, float y=0.0f);
         static bool set_vec3(std::string name="[unset-name]", float x=0.0f, float y=0.0f, float z=0.0f);
         static bool set_vec3(std::string name="[unset-name]", AllegroFlare::Vec3D vec={});
         static bool set_vec4(std::string name="[unset-name]", float x=0.0f, float y=0.0f, float z=0.0f, float a=0.0f);
         static bool set_sampler_cube(std::string name="[unset-name]", AllegroFlare::Cubemap* cubemap=nullptr, int unit=0);
         void hotload(std::string vertex_source_code="", std::string fragment_source_code="");
      };
   }
}



