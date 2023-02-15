

#include <AllegroFlare/Shaders/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


Base::Base(std::string type, std::string vertex_source_code, std::string fragment_source_code)
   : AllegroFlare::Shader(vertex_source_code, fragment_source_code)
   , type(type)
   , vertex_source_code(vertex_source_code)
   , fragment_source_code(fragment_source_code)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
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
   AllegroFlare::Shader::vertex_source_code = vertex_source_code;
   AllegroFlare::Shader::fragment_source_code = fragment_source_code;

   attach_source_code(false);
   build();

   return;
}


} // namespace Shaders
} // namespace AllegroFlare


