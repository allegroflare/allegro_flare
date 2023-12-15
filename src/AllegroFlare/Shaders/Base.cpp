

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
   , al_shader(nullptr)
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


std::string Base::get_vertex_source_code() const
{
   return vertex_source_code;
}


std::string Base::get_fragment_source_code() const
{
   return fragment_source_code;
}


ALLEGRO_SHADER* Base::get_al_shader() const
{
   return al_shader;
}


bool Base::get_initialized() const
{
   return initialized;
}


void Base::set_vertex_source_code(std::string vertex_source_code)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Base::set_vertex_source_code]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::set_vertex_source_code: error: guard \"(!initialized)\" not met");
   }
   // TODO: Test this
   this->vertex_source_code = vertex_source_code;
   return;
}

void Base::set_fragment_source_code(std::string fragment_source_code)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Base::set_fragment_source_code]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::set_fragment_source_code: error: guard \"(!initialized)\" not met");
   }
   // TODO: Test this
   this->fragment_source_code = fragment_source_code;
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

bool Base::is_active()
{
   return (get_al_shader() == al_get_current_shader());
}

bool Base::display_is_opengl(ALLEGRO_DISPLAY* display)
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Base::display_is_opengl]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::display_is_opengl: error: guard \"display\" not met");
   }
   // TODO: Test this
   return (ALLEGRO_OPENGL == (al_get_display_flags(display) & ALLEGRO_OPENGL));
}

bool Base::display_is_programmable_pipeline(ALLEGRO_DISPLAY* display)
{
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Base::display_is_programmable_pipeline]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::display_is_programmable_pipeline: error: guard \"display\" not met");
   }
   // TODO: Test this
   return (ALLEGRO_PROGRAMMABLE_PIPELINE == (al_get_display_flags(display) & ALLEGRO_PROGRAMMABLE_PIPELINE));
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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"al_get_current_display()\" not met");
   }
   if (!(display_is_opengl(al_get_current_display())))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"display_is_opengl(al_get_current_display())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"display_is_opengl(al_get_current_display())\" not met");
   }
   if (!(display_is_programmable_pipeline(al_get_current_display())))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"display_is_programmable_pipeline(al_get_current_display())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"display_is_programmable_pipeline(al_get_current_display())\" not met");
   }
   al_shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!al_shader) throw std::runtime_error("Could not create Shader");
   attach_source_code();
   build();
   initialized = true;
   return true;
}

bool Base::attach_source_code(bool throw_on_error)
{
   if (!((!vertex_source_code_is_default())))
   {
      std::stringstream error_message;
      error_message << "[Base::attach_source_code]: error: guard \"(!vertex_source_code_is_default())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::attach_source_code: error: guard \"(!vertex_source_code_is_default())\" not met");
   }
   if (!((!fragment_source_code_is_default())))
   {
      std::stringstream error_message;
      error_message << "[Base::attach_source_code]: error: guard \"(!fragment_source_code_is_default())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::attach_source_code: error: guard \"(!fragment_source_code_is_default())\" not met");
   }
   if (!al_attach_shader_source(al_shader, ALLEGRO_VERTEX_SHADER, vertex_source_code.c_str()))
   {
      // TODO: Replace these messages with AllegroFlare::Logger::throw_from
      std::stringstream error_message;
      error_message << "There was an error attaching the VERTEX shader source code:"
         << std::endl << al_get_shader_log(al_shader);
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

   if (!al_attach_shader_source(al_shader, ALLEGRO_PIXEL_SHADER, fragment_source_code.c_str()))
   {
      // TODO: Replace these messages with AllegroFlare::Logger::throw_from
      std::stringstream error_message;
      error_message << "There was an error attaching the FRAGMENT shader source code:"
         << std::endl << al_get_shader_log(al_shader);
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
   if (!al_build_shader(al_shader))
   {
      std::stringstream error_message;
      error_message << "There were errors when building the shader. The shader log contained the following message: "
                    << al_get_shader_log(al_shader);
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
   if (al_shader) al_destroy_shader(al_shader);
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
   al_use_shader(al_shader);
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

bool Base::set_int2(std::string name, int x, int y)
{
   // TODO: Test that this works
   int vec2[2] = {x, y};
   return al_set_shader_int_vector(name.c_str(), 2, &vec2[0], 1);
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
   if (al_shader)
   {
      al_destroy_shader(al_shader);
      al_shader = nullptr;
   }
   al_shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!al_shader) throw std::runtime_error("Could not create Shader");

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

bool Base::vertex_source_code_is_default()
{
   // TODO: Test this method
   return vertex_source_code == DEFAULT_VERTEX_SOURCE_CODE;
}

bool Base::fragment_source_code_is_default()
{
   // TODO: Test this method
   return fragment_source_code == DEFAULT_FRAGMENT_SOURCE_CODE;
}


} // namespace Shaders
} // namespace AllegroFlare


