

#define ALLEGRO_UNSTABLE


#include <AllegroFlare/Shader.hpp>

#include <iostream>
#include <sstream>

#include <AllegroFlare/Logger.hpp>


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



   void Shader::attach_source_code()
   {
      if (!al_attach_shader_source(shader, ALLEGRO_VERTEX_SHADER, vertex_source_code.c_str()))
      {
         // TODO: Replace these messages with AllegroFlare::Logger::throw_from
         std::stringstream error_message;
         error_message << "There was an error attaching the VERTEX shader source code:"
            << std::endl << al_get_shader_log(shader);
         throw std::runtime_error(error_message.str());
      }

      if (!al_attach_shader_source(shader, ALLEGRO_PIXEL_SHADER, fragment_source_code.c_str()))
      {
         // TODO: Replace these messages with AllegroFlare::Logger::throw_from
         std::stringstream error_message;
         error_message << "There was an error attaching the FRAGMENT shader source code:"
            << std::endl << al_get_shader_log(shader);
         throw std::runtime_error(error_message.str());
      }
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



   void Shader::rebuild_with_new_source(std::string vertex_source_code, std::string fragment_source_code)
   {
                              // HERE:
      al_use_shader(nullptr); // TODO: only disable the current shader is the active one.
                              // TODO: consider doing the thing
                              // HERE:

      if (!initialized) throw std::runtime_error("AllegroFlare::Shader::rebuild_with_new_source: must be initialized.");

      if (shader) al_destroy_shader(shader);
      this->vertex_source_code = vertex_source_code;
      this->fragment_source_code = fragment_source_code;

      attach_source_code();

      build();

      //shader = al_create_shader(ALLEGRO_SHADER_GLSL);
      //if (!shader) throw std::runtime_error("Could not create Shader");
      //initialized = false;
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



   bool Shader::set_vec2(const char *name, float x, float y)
   {
      float vec2[2] = {x, y};
      return al_set_shader_float_vector(name, 2, &vec2[0], 1);
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



   bool Shader::set_sampler_cube(const char *name, AllegroFlare::Cubemap *cubemap, int unit)
   {
      if (!cubemap) return false;
      // grab the currently active shader program
      GLint currProgram;
      glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
      GLint shader_program_object = currProgram;

      // get and verify that the uniform name is there and valid
      GLint handle = glGetUniformLocation(shader_program_object, name);
      if (handle < 0)
      {
         // this warning is silenced because there are instances where a user
         // intentionally attempts to assign the uniform even knowing it is not there.
         // a better reporting mechanisim might be used for all Shader::set_* functions.
         //std::cout << "uniform not found for \"" << name << "\" in shader" << std::endl;
         return false;
      }

      // bind it
      glActiveTexture(GL_TEXTURE0 + unit);
      glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, cubemap->get_id());
      glUniform1i(handle, unit);

      // check for errors
      GLenum err = glGetError();
      if (err != 0)
      {
         // NOTE: in the internal Allegro 5 code, this pattern returns the acual message, rather
         // than the error number.  However, the funciton to get the message for the error
         // is an internal Allegro function.  This will work for now.
         std::cout << "[Shader::set_sampler] error: glGetError() returned " << err << std::endl;
         return err;
      }
      return true;
   }



   void Shader::activate()
   {
      al_use_shader(shader);
   }



   void Shader::deactivate()
   {
      al_use_shader(nullptr);
   }



   void Shader::global_deactivate()
   {
      al_use_shader(nullptr);
   }
}



