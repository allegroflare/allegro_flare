

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

   //if (shader) al_destroy_shader(shader);
   this->vertex_source_code = vertex_source_code;
   this->fragment_source_code = fragment_source_code;

   if (shader) al_destroy_shader(shader);
   shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   if (!shader) throw std::runtime_error("Could not create Shader");

   this->vertex_source_code = vertex_source_code;
   this->fragment_source_code = fragment_source_code;

   AllegroFlare::Shaders::Base::attach_source_code();
   AllegroFlare::Shaders::Base::build();

   //shader = al_create_shader(ALLEGRO_SHADER_GLSL);
   //if (!shader) throw std::runtime_error("Could not create Shader");
   //initialized = false;

   return;
}


} // namespace Shaders
} // namespace AllegroFlare


