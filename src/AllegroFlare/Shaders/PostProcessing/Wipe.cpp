

#include <AllegroFlare/Shaders/PostProcessing/Wipe.hpp>

#include <algorithm>
#include <iostream>
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

void Wipe::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Wipe::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Wipe::activate: error: guard \"initialized\" not met");
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

     bool alpha_test_func(float x, int op, float compare);

     vec4 modify_color(vec4 color)
     {
        //float horizontal_intensity = (varying_texcoord.x / surface_dimensions.x);

        vec4 blue = vec4(0.0, 0.06, 0.4, 1.0);
        float multiplier = 0.6;
        float inv_multiplier = 1.0 - multiplier;

        return color * inv_multiplier + blue * multiplier;
     }

     void main()
     {
       vec2 normalized_coord_xy = gl_FragCoord.xy / surface_dimensions;
       vec2 pixel_xy = gl_FragCoord.xy / surface_dimensions;

       if (normalized_coord_xy.x < transition_playhead_position) { gl_FragColor = vec4(0, 0, 0, 1); return; }

       vec4 c;
       if (al_use_tex)
         c = varying_color * texture2D(al_tex, varying_texcoord);
       else
         c = varying_color;
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
         c = modify_color(c);
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


