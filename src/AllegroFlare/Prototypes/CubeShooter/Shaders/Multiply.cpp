

#include <AllegroFlare/Prototypes/CubeShooter/Shaders/Multiply.hpp>

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


Multiply::Multiply()
   : AllegroFlare::Shaders::Base("CubeShooter/Shaders/Multiply", obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
   , tint(ALLEGRO_COLOR{1, 1, 1, 1})
   , tint_intensity(1.0f)
   , pulse_created_at(0.0f)
   , time_now(0.0f)
   , far_plane(100.0f)
{
}


Multiply::~Multiply()
{
}


void Multiply::set_tint(ALLEGRO_COLOR tint)
{
   this->tint = tint;
}


void Multiply::set_tint_intensity(float tint_intensity)
{
   this->tint_intensity = tint_intensity;
}


void Multiply::set_pulse_created_at(float pulse_created_at)
{
   this->pulse_created_at = pulse_created_at;
}


void Multiply::set_time_now(float time_now)
{
   this->time_now = time_now;
}


void Multiply::set_far_plane(float far_plane)
{
   this->far_plane = far_plane;
}


ALLEGRO_COLOR Multiply::get_tint() const
{
   return tint;
}


float Multiply::get_tint_intensity() const
{
   return tint_intensity;
}


float Multiply::get_pulse_created_at() const
{
   return pulse_created_at;
}


float Multiply::get_time_now() const
{
   return time_now;
}


float Multiply::get_far_plane() const
{
   return far_plane;
}


void Multiply::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Shaders::Multiply::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Shaders::Multiply::initialize]: error: guard \"(!initialized)\" not met");
   }
   AllegroFlare::Shaders::Base::initialize();
   initialized = true;
   return;
}

void Multiply::activate()
{
   if (!initialized)
   {
      throw std::runtime_error("[CubeShooter::Shaders::Base::Multiply] Attempting to activate() "
                               "shader before it has been initialized");
   }
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
   return;
}

void Multiply::set_values_to_activated_shader()
{
   float pulse_distance = (time_now - pulse_created_at);
   set_vec3("tint", tint.r, tint.g, tint.b);
   set_float("tint_intensity", tint_intensity);
   set_float("pulse_distance", pulse_distance);
   return;
}

std::string Multiply::obtain_vertex_source()
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
        // NOTE: depth position info from:
        // https://stackoverflow.com/a/17621928/6072362
        depth = gl_Position.z / 100.0; // NOTE: 100.0 is the far plane in Camera3D, TODO: pass in as a varying
     }
   )DELIM";
   return source;
}

std::string Multiply::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     uniform sampler2D al_tex;
     uniform float tint_intensity;
     uniform float pulse_distance;
     uniform vec3 tint;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;
     varying float depth;

     void main()
     {
        // render a semi-transparent geometry effect
        gl_FragColor = varying_color * gl_FragCoord.a;

        //// render a depth style effect
        //gl_FragColor = vec4(depth, depth, depth, 1.0);

        float h = 0.02 * 0.5;
        if (depth > pulse_distance - h && depth < pulse_distance + h) gl_FragColor = vec4(0.8, 0.85, 0.99, 1.0);
     }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


