

#include <AllegroFlare/Shaders/FlatColor.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


FlatColor::FlatColor()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::FlatColor::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , tint(ALLEGRO_COLOR{1, 1, 1, 1})
   , tint_intensity(1.0f)
   , initialized(false)
{
}


FlatColor::~FlatColor()
{
}


void FlatColor::set_tint(ALLEGRO_COLOR tint)
{
   this->tint = tint;
}


void FlatColor::set_tint_intensity(float tint_intensity)
{
   this->tint_intensity = tint_intensity;
}


ALLEGRO_COLOR FlatColor::get_tint() const
{
   return tint;
}


float FlatColor::get_tint_intensity() const
{
   return tint_intensity;
}


void FlatColor::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void FlatColor::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[FlatColor::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlatColor::activate: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
   //AllegroFlare::Shaders::Base::activate();
}

void FlatColor::set_values_to_activated_shader()
{
   set_vec3("tint", tint.r, tint.g, tint.b);
   set_float("tint_intensity", tint_intensity);
   return;
}

std::string FlatColor::obtain_vertex_source()
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

std::string FlatColor::obtain_fragment_source()
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

     //bool alpha_test_func(float x, int op, float compare);
     uniform vec3 tint;
     uniform float tint_intensity;


     vec4 tint_it_plz(vec4 tmp)
     {
        float inverse_tint_intensity = 1.0 - tint_intensity;
        tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
        tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
        tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
        tmp.a = tmp.a;
        return tmp;
     }

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
         gl_FragColor = tint_it_plz(c);
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


} // namespace Shaders
} // namespace AllegroFlare


