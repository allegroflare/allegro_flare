#pragma once


#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Base
      {
      public:
         static constexpr char* DEFAULT_VERTEX_SOURCE_CODE = (char*)"[unset-default_vertex_source_code]";
         static constexpr char* DEFAULT_FRAGMENT_SOURCE_CODE = (char*)"[unset-default_fragment_source_code]";
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Base";

      private:
         std::string type;
         std::string vertex_source_code;
         std::string fragment_source_code;
         ALLEGRO_SHADER* al_shader;
         bool initialized;
         void build();

      protected:


      public:
         Base(std::string type=AllegroFlare::Shaders::Base::TYPE, std::string vertex_source_code=DEFAULT_VERTEX_SOURCE_CODE, std::string fragment_source_code=DEFAULT_FRAGMENT_SOURCE_CODE);
         virtual ~Base();

         std::string get_type() const;
         std::string get_vertex_source_code() const;
         std::string get_fragment_source_code() const;
         ALLEGRO_SHADER* get_al_shader() const;
         bool get_initialized() const;
         void set_vertex_source_code(std::string vertex_source_code=DEFAULT_VERTEX_SOURCE_CODE);
         void set_fragment_source_code(std::string fragment_source_code=DEFAULT_FRAGMENT_SOURCE_CODE);
         bool is_type(std::string possible_type="");
         bool is_active();
         static bool display_is_opengl(ALLEGRO_DISPLAY* display=nullptr);
         static bool display_is_programmable_pipeline(ALLEGRO_DISPLAY* display=nullptr);
         bool initialize();
         bool attach_source_code(bool throw_on_error=true);
         void destroy();
         virtual void activate();
         virtual void deactivate();
         static void global_deactivate();
         static bool set_sampler(std::string name="[unset-name]", ALLEGRO_BITMAP* bitmap=nullptr, int unit=0);
         static bool set_mat4(std::string name="[unset-name]", ALLEGRO_TRANSFORM* transform=nullptr);
         static bool set_int(std::string name="[unset-name]", int value=0);
         static bool set_float(std::string name="[unset-name]", float value=0.0f);
         static bool set_bool(std::string name="[unset-name]", bool value=false);
         static bool set_int2(std::string name="[unset-name]", int x=0, int y=0);
         static bool set_vec2(std::string name="[unset-name]", float x=0.0f, float y=0.0f);
         static bool set_vec3(std::string name="[unset-name]", float x=0.0f, float y=0.0f, float z=0.0f);
         static bool set_vec3(std::string name="[unset-name]", AllegroFlare::Vec3D vec={});
         static bool set_vec4(std::string name="[unset-name]", float x=0.0f, float y=0.0f, float z=0.0f, float a=0.0f);
         static bool set_sampler_cube(std::string name="[unset-name]", AllegroFlare::Cubemap* cubemap=nullptr, int unit=0);
         void hotload(std::string vertex_source_code="", std::string fragment_source_code="");
         bool vertex_source_code_is_default();
         bool fragment_source_code_is_default();
      };
   }
}



