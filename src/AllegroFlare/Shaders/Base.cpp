

#include <AllegroFlare/Shaders/Base.hpp>

#include <AllegroFlare/CubemapTextureBinder.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


Base::Base(std::string type, std::string vertex_source_code, std::string fragment_source_code)
   : type(type)
   , vertex_source_code(vertex_source_code)
   , fragment_source_code(fragment_source_code)
   , shader(nullptr)
   , initialized(false)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


ALLEGRO_SHADER* Base::get_shader() const
{
   return shader;
}


bool Base::get_initialized() const
{
   return initialized;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

ALLEGRO_SHADER* Base::get_al_shader()
{
   // TODO: remove dependent calls to this function and remove this function, rename "shader" to "al_shader"
   return shader;
}

bool Base::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"(!initialized)\" not met");
   }
   shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!shader) throw std::runtime_error("Could not create Shader");
   attach_source_code();
   build();
   initialized = true;
   return true;
}

bool Base::attach_source_code(bool throw_on_error)
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

void Base::build()
{
   if (!al_build_shader(shader))
   {
      std::stringstream error_message;
      error_message << "There were errors when building the shader. The shader log contained the following message: "
                    << al_get_shader_log(shader);
      AllegroFlare::Logger::throw_error("AllegroFlare::Shaders::Base::build", error_message.str());
   }
}

void Base::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Base::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::destroy: error: guard \"initialized\" not met");
   }
   // TODO: find a safer usage of this function.  Some examples
   //   - prevent function calls after destruction
   //   - find callers and besure destroy is called
   if (shader) al_destroy_shader(shader);
}

void Base::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Base::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::activate: error: guard \"initialized\" not met");
   }
   al_use_shader(shader);
   //set_values_to_activated_shader(); // TODO: <-- introduce this function here
}

void Base::deactivate()
{
   al_use_shader(nullptr);
}

void Base::global_deactivate()
{
   // NOTE: needed for one case in WickedDemos/SceneRenderer
   // TODO: please factor out this function
   al_use_shader(nullptr);
}

bool Base::set_sampler(std::string name, ALLEGRO_BITMAP* bitmap, int unit)
{
   return al_set_shader_sampler(name.c_str(), bitmap, unit);
}

bool Base::set_mat4(std::string name, ALLEGRO_TRANSFORM* transform)
{
   return al_set_shader_matrix(name.c_str(), transform);
}

bool Base::set_int(std::string name, int value)
{
   return al_set_shader_int(name.c_str(), value);
}

bool Base::set_float(std::string name, float value)
{
   return al_set_shader_float(name.c_str(), value);
}

bool Base::set_bool(std::string name, bool value)
{
   return al_set_shader_bool(name.c_str(), value);
}

bool Base::set_vec2(std::string name, float x, float y)
{
   float vec2[2] = {x, y};
   return al_set_shader_float_vector(name.c_str(), 2, &vec2[0], 1);
}

bool Base::set_vec3(std::string name, float x, float y, float z)
{
   float vec3[3] = {x, y, z};
   return al_set_shader_float_vector(name.c_str(), 3, &vec3[0], 1);
}

bool Base::set_vec3(std::string name, AllegroFlare::Vec3D vec)
{
   return set_vec3(name.c_str(), vec.x, vec.y, vec.z);
}

bool Base::set_vec4(std::string name, float x, float y, float z, float a)
{
   float vec4[4] = {x, y, z, a};
   return al_set_shader_float_vector(name.c_str(), 4, &vec4[0], 1);
}

bool Base::set_sampler_cube(std::string name, AllegroFlare::Cubemap* cubemap, int unit)
{
   AllegroFlare::CubemapTextureBinder cubemap_texture_binder(name, cubemap, unit);
   return cubemap_texture_binder.bind();
}

void Base::hotload(std::string vertex_source_code, std::string fragment_source_code)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Base::hotload]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::hotload: error: guard \"initialized\" not met");
   }
   al_use_shader(nullptr); // TODO: only disable the shader if it is the currently active one. Restore otherwise
                           // TODO: consider doing the thing

   // Destroy our current shader
   // TODO: determine if the shader can actually be re-used
   if (shader)
   {
      al_destroy_shader(shader);
      shader = nullptr;
   }
   shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!shader) throw std::runtime_error("Could not create Shader");

   // set our local copy of the code
   this->vertex_source_code = vertex_source_code;
   this->fragment_source_code = fragment_source_code;

   // set our base copy of the code
   // TODO: after flattening AllegroFlare::Shader into AllegroFlare::Shaders::Base, this line should be removed
   //AllegroFlare::Shader::vertex_source_code = vertex_source_code;
   //AllegroFlare::Shader::fragment_source_code = fragment_source_code;

   attach_source_code(false);
   build();

   return;
}


} // namespace Shaders
} // namespace AllegroFlare


