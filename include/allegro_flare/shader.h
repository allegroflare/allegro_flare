#ifndef __AF_SHADER_HEADER
#define __AF_SHADER_HEADER




#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>




using namespace AllegroFlare;




namespace allegro_flare
{
   struct ALLEGRO_FLARE_CUBEMAP_TEXTURE;




   class Shader
   {
   private:
      ALLEGRO_SHADER *shader;
      void build();

   public:
      Shader(const char *vertex_source_filename, const char *fragment_source_filename);
      Shader();
      ~Shader();

      // initialize
      void attach_source_files(const char *vertex_source_filename, const char *fragment_source_filename);
      void attach_source_code(const char *vertex_source_code, const char *fragment_source_code);

      // activate and deactivate
      void use();
      static void stop();

      // set uniforms and attributes
      // (these apply only to the /currently active/ shader, and not necessairly
      // this Shader object)
      static bool set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit);
      static bool set_sampler_cube(const char *name, ALLEGRO_FLARE_CUBEMAP_TEXTURE *cubemap, int unit);
      static bool set_mat4(const char *name, ALLEGRO_TRANSFORM *t);
      static bool set_int(const char *name, int i);
      static bool set_float(const char *name, float f);
      static bool set_bool(const char *name, bool b);
      static bool set_vec3(const char *name, float x, float y, float z);
      static bool set_vec3(const char *name, const vec3d vec);
      static bool set_vec4(const char *name, float x, float y, float z, float a);
   };
}




#endif
