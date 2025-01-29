

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
   , flat_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , flat_color_intensity(0.0f)
   , darkness(0.0f)
   , saturation(1.0f)
   , red_channel_multiplier(1.0f)
   , green_channel_multiplier(1.0f)
   , blue_channel_multiplier(1.0f)
   , hue_rotation(1.0f)
   , initialized(false)
{
}


TiledTintColor::~TiledTintColor()
{
}


ALLEGRO_COLOR TiledTintColor::get_flat_color() const
{
   return flat_color;
}


float TiledTintColor::get_flat_color_intensity() const
{
   return flat_color_intensity;
}


float TiledTintColor::get_darkness() const
{
   return darkness;
}


float TiledTintColor::get_saturation() const
{
   return saturation;
}


float TiledTintColor::get_red_channel_multiplier() const
{
   return red_channel_multiplier;
}


float TiledTintColor::get_green_channel_multiplier() const
{
   return green_channel_multiplier;
}


float TiledTintColor::get_blue_channel_multiplier() const
{
   return blue_channel_multiplier;
}


float TiledTintColor::get_hue_rotation() const
{
   return hue_rotation;
}


void TiledTintColor::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void TiledTintColor::set_flat_color(ALLEGRO_COLOR flat_color)
{
   this->flat_color = flat_color;
   if (is_active()) set_vec3("flat_color", flat_color.r, flat_color.g, flat_color.b);
   return;
}

void TiledTintColor::set_saturation(float saturation)
{
   if (!((saturation >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::TiledTintColor::set_saturation]: error: guard \"(saturation >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::TiledTintColor::set_saturation]: error: guard \"(saturation >= 0.0f)\" not met");
   }
   if (!((saturation <= 2.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::TiledTintColor::set_saturation]: error: guard \"(saturation <= 2.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::TiledTintColor::set_saturation]: error: guard \"(saturation <= 2.0f)\" not met");
   }
   this->saturation = saturation;
   if (is_active()) set_float("saturation", saturation);
   return;
}

void TiledTintColor::set_flat_color_intensity(float flat_color_intensity)
{
   if (!((flat_color_intensity >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::TiledTintColor::set_flat_color_intensity]: error: guard \"(flat_color_intensity >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::TiledTintColor::set_flat_color_intensity]: error: guard \"(flat_color_intensity >= 0.0f)\" not met");
   }
   if (!((flat_color_intensity <= 1.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::TiledTintColor::set_flat_color_intensity]: error: guard \"(flat_color_intensity <= 1.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::TiledTintColor::set_flat_color_intensity]: error: guard \"(flat_color_intensity <= 1.0f)\" not met");
   }
   this->flat_color_intensity = flat_color_intensity;
   if (is_active()) set_float("flat_color_intensity", flat_color_intensity);
   return;
}

void TiledTintColor::set_darkness(float darkness)
{
   this->darkness = darkness;
   if (is_active()) set_float("inv_darkness", 1.0 - darkness);
   return;
}

void TiledTintColor::set_red_channel_multiplier(float red_channel_multiplier)
{
   this->red_channel_multiplier = red_channel_multiplier;
   if (is_active()) set_float("red_channel_multiplier", red_channel_multiplier);
   return;
}

void TiledTintColor::set_green_channel_multiplier(float green_channel_multiplier)
{
   this->green_channel_multiplier = green_channel_multiplier;
   if (is_active()) set_float("green_channel_multiplier", green_channel_multiplier);
   return;
}

void TiledTintColor::set_blue_channel_multiplier(float blue_channel_multiplier)
{
   this->blue_channel_multiplier = blue_channel_multiplier;
   if (is_active()) set_float("blue_channel_multiplier", blue_channel_multiplier);
   return;
}

void TiledTintColor::set_hue_rotation(float hue_rotation)
{
   this->hue_rotation = hue_rotation;
   if (is_active()) set_float("hue_rotation", hue_rotation);
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
   set_vec3("flat_color", flat_color.r, flat_color.g, flat_color.b);
   set_float("flat_color_intensity", flat_color_intensity);
   set_float("inv_darkness", 1.0 - darkness);
   set_float("red_channel_multiplier", red_channel_multiplier);
   set_float("green_channel_multiplier", green_channel_multiplier);
   set_float("blue_channel_multiplier", blue_channel_multiplier);
   set_float("hue_rotation", hue_rotation);
   set_float("saturation", saturation);
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

     uniform vec3 flat_color;
     uniform float flat_color_intensity;
     uniform float inv_darkness;
     uniform float red_channel_multiplier;
     uniform float green_channel_multiplier;
     uniform float blue_channel_multiplier;
     uniform float hue_rotation; // Normalized [0-1] value for hue rotation
     uniform float saturation; // 0 == gray, 1.0 == normal, 2.0 == double_saturation

     vec3 saturation_adjust(vec3 rgb, float adjustment)
     // From:
     // https://github.com/minus34/cesium1/blob/master/Cesium/Shaders/Builtin/Functions/saturation.glsl
     {
        // Algorithm from Chapter 16 of OpenGL Shading Language
        const vec3 W = vec3(0.2125, 0.7154, 0.0721);
        vec3 intensity = vec3(dot(rgb, W));
        return mix(intensity, rgb, adjustment);
     }

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

     vec4 flat_color_it_plz(vec4 tmp)
     {
        float inverse_color_intensity = 1.0 - flat_color_intensity;
        tmp.r = (tmp.r * inverse_color_intensity + flat_color.r * flat_color_intensity) * tmp.a;
        tmp.g = (tmp.g * inverse_color_intensity + flat_color.g * flat_color_intensity) * tmp.a;
        tmp.b = (tmp.b * inverse_color_intensity + flat_color.b * flat_color_intensity) * tmp.a;
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

       // Apply the 
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
          // Apply hue rotation
          //float angle = hue_rotation * 2.0 * 3.14159265; // Convert normalized value to radians
          //c.rgb = rotate_hue(c.rgb, angle);
          //c.rgb = hue_adjust(c.rgb
          //c = hue_adjust(c, 0.0);
          if (hue_rotation < -0.01 || hue_rotation > 0.01) c = hue_adjust(c, hue_rotation * 2.0 * 3.14159265);

          // Apply saturation adjustment
          if (saturation < 0.99 || saturation > 1.01) c.rgb = saturation_adjust(c.rgb, saturation);

          // Adjust the darkness
          c.r = c.r * inv_darkness * red_channel_multiplier;
          c.g = c.g * inv_darkness * green_channel_multiplier;
          c.b = c.b * inv_darkness * blue_channel_multiplier;
        
          gl_FragColor = flat_color_it_plz(c);
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


