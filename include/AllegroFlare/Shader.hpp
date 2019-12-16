#pragma once



#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>



namespace AllegroFlare
{
   class Shader
   {
   private:
      std::string vertex_source_code;
      std::string fragment_source_code;
      ALLEGRO_SHADER *shader;
      void build();
      void attach_source_code();


   public:
      Shader(std::string vertex_source_code="", std::string fragment_source_code="");
      ~Shader();

      // initialize
      void initialize();

      // set uniforms and attributes
      // (these apply only to the /currently active/ shader, and not necessairly
      // this Shader object)
      static bool set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit);
      static bool set_mat4(const char *name, ALLEGRO_TRANSFORM *t);
      static bool set_int(const char *name, int i);
      static bool set_float(const char *name, float f);
      static bool set_bool(const char *name, bool b);
      static bool set_vec3(const char *name, float x, float y, float z);
      static bool set_vec3(const char *name, const AllegroFlare::vec3d vec);
      static bool set_vec4(const char *name, float x, float y, float z, float a);

      // activate and deactivate
      void activate();
      void deactivate();
   };
}



