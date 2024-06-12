

#include <AllegroFlare/Shaders/PostProcessing/Wipe.hpp>

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{
namespace PostProcessing
{


Wipe::Wipe()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::PostProcessing::Wipe::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , surface_width(1920)
   , surface_height(1920)
   , transition_playhead_position(0.0f)
   , direction(AllegroFlare::Shaders::PostProcessing::Wipe::DIRECTION_LEFT)
   , initialized(false)
{
}


Wipe::~Wipe()
{
}


float Wipe::get_transition_playhead_position() const
{
   return transition_playhead_position;
}


std::string Wipe::get_direction() const
{
   return direction;
}


void Wipe::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void Wipe::set_transition_playhead_position(float transition_playhead_position)
{
   transition_playhead_position = std::max(0.0f, std::min(1.0f, transition_playhead_position));
   this->transition_playhead_position = transition_playhead_position;
   // TODO: include this condition
   //if (this_is_the_currently_active_shader)
   //{
      set_float("transition_playhead_position", transition_playhead_position);
   //}
   return;
}

void Wipe::set_direction(std::string direction)
{
   if (!(is_valid_direction(direction)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::Wipe::set_direction]: error: guard \"is_valid_direction(direction)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::Wipe::set_direction]: error: guard \"is_valid_direction(direction)\" not met");
   }
   this->direction = direction;
   // TODO: include this condition
   //if (this_is_the_currently_active_shader)
   //{
      set_bool("transition_wiping_left", direction == DIRECTION_LEFT);
   //}
   return;
}

bool Wipe::is_valid_direction(std::string possibly_valid_direction)
{
   std::set<std::string> valid_directions = {
      DIRECTION_LEFT,
      DIRECTION_RIGHT,
   };
   return (valid_directions.count(possibly_valid_direction) > 0);
}

void Wipe::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::Wipe::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::Wipe::activate]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_vec2("surface_dimensions", surface_width, surface_height);
   set_float("transition_playhead_position", transition_playhead_position);
}

std::string Wipe::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     uniform mat4 al_projview_matrix;
     uniform bool al_use_tex_matrix;
     uniform mat4 al_tex_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     void main()
     {
       varying_color = al_color;
       if (al_use_tex_matrix) {
         vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
         varying_texcoord = vec2(uv.x, uv.y);
       }
       else
         varying_texcoord = al_texcoord;
       gl_Position = al_projview_matrix * al_pos;
     }
   )DELIM";
   return source;
}

std::string Wipe::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     #ifdef GL_ES
     precision lowp float;
     #endif
     uniform sampler2D al_tex;
     uniform bool al_use_tex;
     uniform bool al_alpha_test;
     uniform int al_alpha_func;
     uniform float al_alpha_test_val;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;
     uniform vec2 surface_dimensions;
     uniform float transition_playhead_position;
     uniform bool transition_wiping_left;

     bool alpha_test_func(float x, int op, float compare);

     void main()
     {
       vec2 normalized_coord_xy = gl_FragCoord.xy / surface_dimensions;
       vec2 pixel_xy = gl_FragCoord.xy / surface_dimensions;

       if (transition_wiping_left)
       {
          if (normalized_coord_xy.x < transition_playhead_position) { gl_FragColor = vec4(0, 0, 0, 1); return; }
       }
       else
       {
          if (normalized_coord_xy.x > (1.0 - transition_playhead_position))
          {
             gl_FragColor = vec4(0, 0, 0, 1); return;
          }
       }

       vec4 c;
       if (al_use_tex)
         c = varying_color * texture2D(al_tex, varying_texcoord);
       else
         c = varying_color;
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
         gl_FragColor = c;
       }
       else
         discard;
     }

     bool alpha_test_func(float x, int op, float compare)
     {
       if (op == 0) return false;
       else if (op == 1) return true;
       else if (op == 2) return x < compare;
       else if (op == 3) return x == compare;
       else if (op == 4) return x <= compare;
       else if (op == 5) return x > compare;
       else if (op == 6) return x != compare;
       else if (op == 7) return x >= compare;
       return false;
     }
   )DELIM";
   return source;
}


} // namespace PostProcessing
} // namespace Shaders
} // namespace AllegroFlare


