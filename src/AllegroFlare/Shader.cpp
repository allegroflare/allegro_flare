

#define ALLEGRO_UNSTABLE


#include <AllegroFlare/Shader.hpp>

#include <iostream>
#include <sstream>



namespace AllegroFlare
{
   void Shader::build()
   {
      if (!al_build_shader(shader))
      {
         std::cerr << "There were errors when building the shader:" << std::endl;
         std::cerr << al_get_shader_log(shader) << std::endl;
      }
   }



   void Shader::attach_source_files(const char *vertex_source_filename, const char *fragment_source_filename)
   {
      if (!al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vertex_source_filename))
      {
         std::stringstream error_message;
         error_message << "There was an error attaching the VERTEX shader source from file:"
            << std::endl << "\"" << vertex_source_filename << "\""
            << std::endl << al_get_shader_log(shader)
            << std::endl;
         throw std::runtime_error(error_message.str());
      }

      if (!al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, fragment_source_filename))
      {
         std::stringstream error_message;
         error_message << "There was an error attaching the FRAGMENT shader source from file:"
            << std::endl << "\"" << fragment_source_filename << "\""
            << std::endl << al_get_shader_log(shader)
            << std::endl;
         throw std::runtime_error(error_message.str());
      }

      build();
   }



   //void Shader::attach_source_code(const char *vertex_source_code, const char *fragment_source_code)
   //{
      //if (vertex_source_code)
      //{
         //if (!al_attach_shader_source(shader, ALLEGRO_VERTEX_SHADER, vertex_source_code))
            //std::cerr << "There was an error attaching the VERTEX shader source code:"
               //<< std::endl << al_get_shader_log(shader)
               //<< std::endl;
      //}

      //if (fragment_source_code)
      //{
         //if (!al_attach_shader_source(shader, ALLEGRO_PIXEL_SHADER, fragment_source_code))
            //std::cerr << "There was an error attaching the FRAGMENT shader source code:"
               //<< std::endl << al_get_shader_log(shader)
               //<< std::endl;
      //}

      //build();
   //}



   Shader::Shader(std::string vertex_source_filename, std::string fragment_source_filename)
      : vertex_source_filename(vertex_source_filename)
      , fragment_source_filename(fragment_source_filename)
      , shader(nullptr)
   {
   }



   Shader::~Shader()
   {
      al_destroy_shader(shader);
   }



   void Shader::initialize()
   {
      shader = al_create_shader(ALLEGRO_SHADER_GLSL);
      if (!shader) throw std::runtime_error("Could not create Shader");

      attach_source_files(vertex_source_filename.c_str(), fragment_source_filename.c_str());
   }



   bool Shader::set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit)
   {
      return al_set_shader_sampler(name, bitmap, unit);
   }



   bool Shader::set_mat4(const char *name, ALLEGRO_TRANSFORM *t)
   {
      return al_set_shader_matrix(name, t);
   }



   bool Shader::set_int(const char *name, int i)
   {
      return al_set_shader_int(name, i);
   }



   bool Shader::set_float(const char *name, float f)
   {
      return al_set_shader_float(name, f);
   }



   bool Shader::set_bool(const char *name, bool b)
   {
      return al_set_shader_bool(name, b);
   }



   bool Shader::set_vec3(const char *name, float x, float y, float z)
   {
      float vec3[3] = {x, y, z};
      return al_set_shader_float_vector(name, 3, &vec3[0], 1);
   }



   bool Shader::set_vec3(const char *name, const AllegroFlare::vec3d vec)
   {
      return set_vec3(name, vec.x, vec.y, vec.z);
   }



   bool Shader::set_vec4(const char *name, float x, float y, float z, float a)
   {
      float vec4[4] = {x, y, z, a};
      return al_set_shader_float_vector(name, 4, &vec4[0], 1);
   }



   void Shader::activate()
   {
      al_use_shader(shader);
   }



   void Shader::deactivate()
   {
      al_use_shader(nullptr);
   }
}



