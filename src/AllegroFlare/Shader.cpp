

#define ALLEGRO_UNSTABLE


#include <AllegroFlare/Shader.hpp>

#include <iostream>
#include <sstream>

#include <AllegroFlare/Logger.hpp>
//#include <AllegroFlare/Cubemap.hpp>
//#include <AllegroFlare/CubemapTextureBinder.hpp>



namespace AllegroFlare
{



void Shader::build()
{
   if (!al_build_shader(shader))
   {
      std::stringstream error_message;
      error_message << "There were errors when building the shader. The shader log contained the following message: "
                    << al_get_shader_log(shader);
      AllegroFlare::Logger::throw_error("AllegroFlare::Shader::build", error_message.str());
   }
}



bool Shader::attach_source_code(bool throw_on_error)
{
   if (!al_attach_shader_source(shader, ALLEGRO_VERTEX_SHADER, vertex_source_code.c_str()))
   {
      // TODO: Replace these messages with AllegroFlare::Logger::throw_from
      std::stringstream error_message;
      error_message << "There was an error attaching the VERTEX shader source code:"
         << std::endl << al_get_shader_log(shader);
      if (throw_on_error)
      {
         throw std::runtime_error(error_message.str());
      }
      else
      {
         // TODO: improve the formatting of this error message
         std::cout << error_message.str() << std::endl;
      }
   }

   if (!al_attach_shader_source(shader, ALLEGRO_PIXEL_SHADER, fragment_source_code.c_str()))
   {
      // TODO: Replace these messages with AllegroFlare::Logger::throw_from
      std::stringstream error_message;
      error_message << "There was an error attaching the FRAGMENT shader source code:"
         << std::endl << al_get_shader_log(shader);
      if (throw_on_error)
      {
         throw std::runtime_error(error_message.str());
      }
      else
      {
         // TODO: improve the formatting of this error message
         std::cout << error_message.str() << std::endl;
      }
   }

   return true;
}



Shader::Shader(std::string vertex_source_code, std::string fragment_source_code)
   : vertex_source_code(vertex_source_code)
   , fragment_source_code(fragment_source_code)
   , shader(nullptr)
   , initialized(false)
{
}



Shader::~Shader()
{
   if (!initialized) return;

   if (!al_is_system_installed())
   {
      AllegroFlare::Logger::warn_from("AllegroFlare::Shader::~Shader()",
            "Attempting to destroy a shader but Allegro is not installed. It's possible Allegro was never "
            "initialized, or, Allegro was uninstalled and this shader dtor is being called after the fact. "
            "There will probably be a crash going forward."
      );
   }
   if (shader) al_destroy_shader(shader);
}



void Shader::initialize()
{
   // DEBUG:
   shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!shader) throw std::runtime_error("Could not create Shader");

   attach_source_code();

   build();

   initialized = true;
}



bool Shader::get_initialized()
{
   return initialized;
}



ALLEGRO_SHADER *Shader::get_al_shader()
{
   return shader;
}



//FLATTENED: bool Shader::set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit)
//{
   //return al_set_shader_sampler(name, bitmap, unit);
//}



//bool Shader::set_mat4(const char *name, ALLEGRO_TRANSFORM *t)
//{
   //return al_set_shader_matrix(name, t);
//}



//bool Shader::set_int(const char *name, int i)
//{
   //return al_set_shader_int(name, i);
//}



//bool Shader::set_float(const char *name, float f)
//{
   //return al_set_shader_float(name, f);
//}



//bool Shader::set_bool(const char *name, bool b)
//{
   //return al_set_shader_bool(name, b);
//}



//bool Shader::set_vec2(const char *name, float x, float y)
//{
   //float vec2[2] = {x, y};
   //return al_set_shader_float_vector(name, 2, &vec2[0], 1);
//}


//bool Shader::set_vec3(const char *name, float x, float y, float z)
//{
   //float vec3[3] = {x, y, z};
   //return al_set_shader_float_vector(name, 3, &vec3[0], 1);
//}



//bool Shader::set_vec3(const char *name, const AllegroFlare::vec3d vec)
//{
   //return set_vec3(name, vec.x, vec.y, vec.z);
//}



//bool Shader::set_vec4(const char *name, float x, float y, float z, float a)
//{
   //float vec4[4] = {x, y, z, a};
   //return al_set_shader_float_vector(name, 4, &vec4[0], 1);
//}



//bool Shader::set_sampler_cube(const char *name, AllegroFlare::Cubemap *cubemap, int unit)
//{
   //AllegroFlare::CubemapTextureBinder cubemap_texture_binder(name, cubemap, unit);
   //return cubemap_texture_binder.bind();
//}



//void Shader::activate()
//{
   //al_use_shader(shader);
//}



//void Shader::deactivate()
//{
   //al_use_shader(nullptr);
//}



//void Shader::global_deactivate()
//{
   //al_use_shader(nullptr);
//}



} // namespace AllegroFlare



