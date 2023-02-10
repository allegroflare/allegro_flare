#pragma once



#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/Cubemap.hpp>



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
      bool initialized;


   public:
      Shader(std::string vertex_source_code="", std::string fragment_source_code="");
      virtual ~Shader();

      // initialize
      void initialize();
      void rebuild_with_new_source(std::string vertex_source_code, std::string fragment_source_code);

      // set uniforms and attributes
      // (these apply only to the /currently active/ shader, and not necessairly
      // this Shader object)
      static bool set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit);
      static bool set_sampler_cube(const char *name, AllegroFlare::Cubemap *cubemap, int unit);
      static bool set_mat4(const char *name, ALLEGRO_TRANSFORM *t);
      static bool set_int(const char *name, int i);
      static bool set_float(const char *name, float f);
      static bool set_bool(const char *name, bool b);
      static bool set_vec2(const char *name, float x, float y);
      static bool set_vec3(const char *name, float x, float y, float z);
      static bool set_vec3(const char *name, const AllegroFlare::vec3d vec);
      static bool set_vec4(const char *name, float x, float y, float z, float a);

      // activate and deactivate
      virtual void activate();
      virtual void deactivate();

      // force deactivate
      static void global_deactivate(); // needed for one case in WickedDemos/SceneRenderer, please factor out
   };
}



