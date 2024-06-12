

#include <AllegroFlare/Shaders/PostProcessing/Blinds.hpp>

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


Blinds::Blinds()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::PostProcessing::Blinds::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , surface_width(1920)
   , surface_height(1080)
   , transition_playhead_position(0.0f)
   , num_blinds(14)
   , blinds_color(ALLEGRO_COLOR{0, 0, 0, 1})
   , initialized(false)
{
}


Blinds::~Blinds()
{
}


float Blinds::get_transition_playhead_position() const
{
   return transition_playhead_position;
}


int Blinds::get_num_blinds() const
{
   return num_blinds;
}


ALLEGRO_COLOR Blinds::get_blinds_color() const
{
   return blinds_color;
}


void Blinds::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void Blinds::set_transition_playhead_position(float transition_playhead_position)
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

void Blinds::set_num_blinds(int num_blinds)
{
   if (!((num_blinds >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::Blinds::set_num_blinds]: error: guard \"(num_blinds >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::Blinds::set_num_blinds]: error: guard \"(num_blinds >= 1)\" not met");
   }
   if (!((num_blinds < 100)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::Blinds::set_num_blinds]: error: guard \"(num_blinds < 100)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::Blinds::set_num_blinds]: error: guard \"(num_blinds < 100)\" not met");
   }
   this->num_blinds = num_blinds;
   // TODO: include this condition
   //if (this_is_the_currently_active_shader)
   //{
      set_float("num_blinds", (int)num_blinds);
   //}
   return;
}

void Blinds::set_blinds_color(ALLEGRO_COLOR blinds_color)
{
   this->blinds_color = blinds_color;
   // TODO: include this condition
   //if (this_is_the_currently_active_shader)
   //{
      set_vec3("blinds_color", blinds_color.r, blinds_color.g, blinds_color.b);
   //}
   return;
}

void Blinds::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::PostProcessing::Blinds::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::PostProcessing::Blinds::activate]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_vec2("surface_dimensions", surface_width, surface_height);
   set_float("transition_playhead_position", transition_playhead_position);
   set_float("num_blinds", (int)num_blinds);
   set_vec3("blinds_color", blinds_color.r, blinds_color.g, blinds_color.b);
}

std::string Blinds::obtain_vertex_source()
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

std::string Blinds::obtain_fragment_source()
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
     uniform float num_blinds;
     uniform vec3 blinds_color;

     bool alpha_test_func(float x, int op, float compare);

     void main()
     {
       //float num_blinds = 16.0;
       vec2 normalized_coord_xy = gl_FragCoord.xy / surface_dimensions;
       vec2 pixel_xy = gl_FragCoord.xy / surface_dimensions;
       float blind_value = mod(normalized_coord_xy.y, 1.0 / num_blinds);
         //(normalized_coord_xy.x / num_blinds);

       float i_transition_playhead_position = 1.0 - transition_playhead_position;
       i_transition_playhead_position *= i_transition_playhead_position;

       if (blind_value > (i_transition_playhead_position / num_blinds))
       {
          gl_FragColor = vec4(blinds_color, 1);
          return;
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


