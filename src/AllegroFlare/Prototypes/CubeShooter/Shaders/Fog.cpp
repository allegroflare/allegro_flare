

#include <AllegroFlare/Prototypes/CubeShooter/Shaders/Fog.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{
namespace Shaders
{


Fog::Fog()
   : AllegroFlare::Shaders::Base("CubeShooter/Shaders/Fog", obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
   , tint(ALLEGRO_COLOR{1, 1, 1, 1})
   , tint_intensity(1.0f)
{
}


Fog::~Fog()
{
}


void Fog::set_tint(ALLEGRO_COLOR tint)
{
   this->tint = tint;
}


void Fog::set_tint_intensity(float tint_intensity)
{
   this->tint_intensity = tint_intensity;
}


ALLEGRO_COLOR Fog::get_tint() const
{
   return tint;
}


float Fog::get_tint_intensity() const
{
   return tint_intensity;
}


void Fog::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Shaders::Fog::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Shaders::Fog::initialize]: error: guard \"(!initialized)\" not met");
   }
   AllegroFlare::Shaders::Base::initialize();
   initialized = true;
   return;
}

void Fog::activate()
{
   if (!initialized)
   {
      throw std::runtime_error("[CubeShooter::Shaders::Fog] Attempting to activate() "
                               "shader before it has been initialized");
   }
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
   return;
}

void Fog::set_values_to_activated_shader()
{
   set_vec3("tint", tint.r, tint.g, tint.b);
   set_float("tint_intensity", tint_intensity);
   return;
}

std::string Fog::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     uniform mat4 al_projview_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;
     varying float depth;

     void main()
     {
        varying_color = al_color;
        varying_texcoord = al_texcoord;
        gl_Position = al_projview_matrix * al_pos;
        depth = gl_Position.z / 100.0; // NOTE: 100.0 is the far plane in Camera3D
                                       // TODO: pass in far_plane as a varying
                                       // https://stackoverflow.com/a/17621928/6072362
     }
   )DELIM";
   return source;
}

std::string Fog::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     uniform sampler2D al_tex;
     uniform float tint_intensity;
     uniform vec3 tint;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;
     varying float depth;

     void main()
     {
        // render a depth style effect
        gl_FragColor = vec4(depth, depth, depth, 1.0);
        return;
     }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


