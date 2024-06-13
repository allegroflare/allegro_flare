

#include <AllegroFlare/Shaders/PostProcessing/DipToBlack.hpp>

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


DipToBlack::DipToBlack()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::PostProcessing::DipToBlack::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , surface_width(1920)
   , surface_height(1080)
   , transition_playhead_position(0.0f)
   , color(ALLEGRO_COLOR{0, 0, 0, 1})
   , initialized(false)
{
}


DipToBlack::~DipToBlack()
{
}


float DipToBlack::get_transition_playhead_position() const
{
   return transition_playhead_position;
}


ALLEGRO_COLOR DipToBlack::get_color() const
{
   return color;
}


void DipToBlack::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void DipToBlack::set_transition_playhead_position(float transition_playhead_position)
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

void DipToBlack::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
   // TODO: include this condition
   //if (this_is_the_currently_active_shader)
   //{
      set_vec3("color", color.r, color.g, color.b);
   //}
   return;
}

void DipToBlack::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::DipToBlack::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::DipToBlack::activate]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_vec2("surface_dimensions", surface_width, surface_height);
   set_float("transition_playhead_position", transition_playhead_position);
   set_vec3("color", color.r, color.g, color.b);
}

std::string DipToBlack::obtain_vertex_source()
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

std::string DipToBlack::obtain_fragment_source()
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
     uniform vec3 color;

     bool alpha_test_func(float x, int op, float compare);

     void main()
     {
       vec4 c;
       if (al_use_tex)
       {
          c = varying_color * texture2D(al_tex, varying_texcoord);
       }
       else
       {
          c = varying_color;
       }

       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
         gl_FragColor = mix(c, vec4(color, 1), transition_playhead_position);
       }
       else
       {
         discard;
       }
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


