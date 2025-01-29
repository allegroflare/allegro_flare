

#include <AllegroFlare/Shaders/TiledTintColor.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


TiledTintColor::TiledTintColor()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::TiledTintColor::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , tint_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , tint_color_is_used(false)
   , initialized(false)
{
}


TiledTintColor::~TiledTintColor()
{
}


ALLEGRO_COLOR TiledTintColor::get_tint_color() const
{
   return tint_color;
}


bool TiledTintColor::get_tint_color_is_used() const
{
   return tint_color_is_used;
}


void TiledTintColor::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void TiledTintColor::set_tint_color(ALLEGRO_COLOR tint_color)
{
   this->tint_color = tint_color;
   if (is_active()) set_vec3("tint_color", tint_color.r, tint_color.g, tint_color.b);
   return;
}

void TiledTintColor::set_tint_color_is_used(bool tint_color_is_used)
{
   this->tint_color_is_used = tint_color_is_used;
   if (is_active()) set_bool("tint_color_is_used", tint_color_is_used);
   return;
}

void TiledTintColor::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::TiledTintColor::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::TiledTintColor::activate]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
   //AllegroFlare::Shaders::Base::activate();
}

void TiledTintColor::set_values_to_activated_shader()
{
   set_bool("tint_color_is_used", tint_color_is_used);
   set_vec3("tint_color", tint_color.r, tint_color.g, tint_color.b);
   return;
}

std::string TiledTintColor::obtain_vertex_source()
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

std::string TiledTintColor::obtain_fragment_source()
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

     bool alpha_test_func(float x, int op, float compare);

     uniform bool tint_color_is_used;
     uniform vec3 tint_color;

     vec4 hue_adjust(vec4 color, float hueAdjust)
     {
        // Original source from:
        // https://stackoverflow.com/questions/9234724/how-to-change-hue-of-a-texture-with-glsl
        // ChatGPT has made some suggestions to potentially improve performance on this function:
        // https://chatgpt.com/c/678d9da9-4378-800f-8236-b233c91aa12a

        const vec4  kRGBToYPrime = vec4 (0.299, 0.587, 0.114, 0.0);
        const vec4  kRGBToI     = vec4 (0.596, -0.275, -0.321, 0.0);
        const vec4  kRGBToQ     = vec4 (0.212, -0.523, 0.311, 0.0);

        const vec4  kYIQToR   = vec4 (1.0, 0.956, 0.621, 0.0);
        const vec4  kYIQToG   = vec4 (1.0, -0.272, -0.647, 0.0);
        const vec4  kYIQToB   = vec4 (1.0, -1.107, 1.704, 0.0);

        // Sample the input pixel
        //vec4    color   = texture2DRect (inputTexture, gl_TexCoord [ 0 ].xy);

        // Convert to YIQ
        float   YPrime  = dot (color, kRGBToYPrime);
        float   I      = dot (color, kRGBToI);
        float   Q      = dot (color, kRGBToQ);

        // Calculate the hue and chroma
        float   hue     = atan (Q, I);
        float   chroma  = sqrt (I * I + Q * Q);

        // Make the user's adjustments
        hue += hueAdjust;

        // Convert back to YIQ
        Q = chroma * sin (hue);
        I = chroma * cos (hue);

        // Convert back to RGB
        vec4    yIQ   = vec4 (YPrime, I, Q, 0.0);
        color.r = dot (yIQ, kYIQToR);
        color.g = dot (yIQ, kYIQToG);
        color.b = dot (yIQ, kYIQToB);

        return color;
     }

     vec4 tint_color_it_plz(vec4 tmp)
     {
        //float inverse_color_intensity = 1.0 - flat_color_intensity;
        tmp.r = tmp.r * tint_color.r;
        tmp.g = tmp.g * tint_color.g;
        tmp.b = tmp.b * tint_color.b;
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
          // Apply the tint if relevant
          if (tint_color_is_used) c = tint_color_it_plz(c);
        
          gl_FragColor = c;
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


