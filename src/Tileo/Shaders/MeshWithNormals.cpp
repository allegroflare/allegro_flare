

#include <Tileo/Shaders/MeshWithNormals.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tileo
{
namespace Shaders
{


MeshWithNormals::MeshWithNormals()
   : Tileo::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


MeshWithNormals::~MeshWithNormals()
{
}


void MeshWithNormals::initialize()
{
   if (!initialized) Tileo::Shaders::Base::initialize();
   initialized = true;
}

void MeshWithNormals::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::Shaders::MeshWithNormals::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::Shaders::MeshWithNormals::activate]: error: guard \"initialized\" not met");
   }
   Tileo::Shaders::Base::activate();
}

void MeshWithNormals::set_flat_color(ALLEGRO_COLOR flat_color, float intensity)
{
   AllegroFlare::Shaders::Base::set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
   AllegroFlare::Shaders::Base::set_float("tint_intensity", intensity);
   return;
}

void MeshWithNormals::set_light_direction(AllegroFlare::vec3d light_direction)
{
   AllegroFlare::Shaders::Base::set_vec3("light_direction", light_direction.x, light_direction.y, light_direction.z);
   return;
}

void MeshWithNormals::set_light_spread(int light_spread)
{
   AllegroFlare::Shaders::Base::set_int("light_spread", light_spread);
   return;
}

void MeshWithNormals::set_light_attenuation(float light_attenuation)
{
   AllegroFlare::Shaders::Base::set_float("light_attenuation", light_attenuation);
   return;
}

void MeshWithNormals::set_primary_texture(ALLEGRO_BITMAP* primary_texture_bitmap)
{
   AllegroFlare::Shaders::Base::set_sampler("primary_texture", primary_texture_bitmap, 1);
   return;
}

void MeshWithNormals::set_normal_texture(ALLEGRO_BITMAP* normal_texture_bitmap)
{
   AllegroFlare::Shaders::Base::set_sampler("normal_texture", normal_texture_bitmap, 2);
   return;
}

std::string MeshWithNormals::obtain_vertex_source()
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

     // normals logic:
     attribute vec2 al_user_attr_0; // this is the normal_u/normal_v
     varying vec2 varying_normal_texcoord; // analagous to varying_texcoord

     // positional logic:
     varying vec3 world_position;

     void main()
     {
       varying_color = al_color;
       if (al_use_tex_matrix)
       {
         vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
         varying_texcoord = vec2(uv.x, uv.y);

         // normals logic:
         vec4 normal_uv = al_tex_matrix * vec4(al_user_attr_0, 0, 1);
         varying_normal_texcoord = vec2(normal_uv.x, normal_uv.y);
       }
       else
       {
         varying_texcoord = al_texcoord;
       }
       gl_Position = al_projview_matrix * al_pos;
       world_position = gl_Position.xyz;
     }
   )DELIM";
   return source;
}

std::string MeshWithNormals::obtain_fragment_source()
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
     uniform float tint_intensity;
     uniform vec3 tint;

     // lights logic:
     uniform vec3 light_direction;
     uniform int light_spread;
     uniform float light_attenuation;

     // normals logic:
     uniform sampler2D primary_texture; // analagous to al_tex
     uniform sampler2D normal_texture; // analagous to al_tex
     varying vec2 varying_normal_texcoord; // analagous to varying_texcoord

     bool alpha_test_func(float x, int op, float compare);
     void alter_by_tint(inout vec4 color);
     void alter_by_normal_texture_color(inout vec4 color, in vec4 normal_color);
     void downsample_color_8bit(inout vec4 color);
     void downsample_color_16bit(inout vec4 color);
     void downsample_color_32bit(inout vec4 color);

     // positional logic
     varying vec3 world_position;

     void main()
     {
       vec4 c, normal_c;
       if (al_use_tex)
       {
         c = varying_color * texture2D(primary_texture, varying_texcoord);
         normal_c = varying_color * texture2D(normal_texture, varying_normal_texcoord);
       }
       else
       {
         c = varying_color;
       }

       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
         alter_by_normal_texture_color(c, normal_c);
         alter_by_tint(c);
         downsample_color_8bit(c);

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

     void alter_by_tint(inout vec4 color)
     {
        return;

        float inverse_tint_intensity = 1.0 - tint_intensity;
        color.r = (color.r * inverse_tint_intensity + tint.r * tint_intensity) * color.a;
        color.g = (color.g * inverse_tint_intensity + tint.g * tint_intensity) * color.a;
        color.b = (color.b * inverse_tint_intensity + tint.b * tint_intensity) * color.a;
        color.a = color.a;
     }

     void downsample_color_8bit(inout vec4 color)
     {
        color.r = floor(color.r * 9. + 0.5) / 9.;
        color.g = floor(color.g * 8. + 0.5) / 8.;
        color.b = floor(color.b * 4. + 0.5) / 4.;
     }

     void downsample_color_16bit(inout vec4 color)
     {
        color.r = floor(color.r * 12. + 0.5) / 12.;
        color.g = floor(color.g * 16. + 0.5) / 16.;
        color.b = floor(color.b * 9. + 0.5) / 9.;
     }

     void downsample_color_32bit(inout vec4 color)
     {
        color.r = floor(color.r * 24. + 0.5) / 24.;
        color.g = floor(color.g * 24. + 0.5) / 24.;
        color.b = floor(color.b * 24. + 0.5) / 24.;
     }

     void alter_by_normal_texture_color(inout vec4 color, in vec4 normal_color)
     {
        vec3 light_position = vec3(0, 0, 0); //vec3(1920/4, 1080/4, 0);
        //light_dir_vec = light_position

        vec3 angle_of_incidence = -vec3(world_position.xy, -1.0); //z; //light_direction;

        //vec3 normalized_normal_texture_angle = normalize(vec3(normal_color.r, normal_color.g, normal_color.b));
        vec3 normalized_normal_texture_angle = normalize(
           vec3(2.0 * normal_color.r - 1.0, 2.0 * normal_color.g - 1.0, 2.0 * normal_color.b - 1.0)
        );
        //vec3 normalized_normal_texture_angle = normalize(vec3(1., 1., 0.));
        vec3 normalized_light_angle = normalize(
          vec3(angle_of_incidence.x, angle_of_incidence.y, angle_of_incidence.z)
        );

        float dot_product = dot(normalized_light_angle, normalized_normal_texture_angle);

        float m = pow(dot_product, light_attenuation);
        //float m = dot_product;

        color.r = color.r *= m; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
        color.g = color.g *= m; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
        color.b = color.b *= m; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
        color.a = color.a;

       
     }

     void alter_by_normal_texture_color_GLOBAL_LIGHT(inout vec4 color, in vec4 normal_color)
     {
        //vec3 normalized_normal_texture_angle = normalize(vec3(normal_color.r, normal_color.g, normal_color.b));
        vec3 normalized_normal_texture_angle = normalize(
           vec3(2.0 * normal_color.r - 1.0, 2.0 * normal_color.g - 1.0, 2.0 * normal_color.b - 1.0)
        );
        //vec3 normalized_normal_texture_angle = normalize(vec3(1., 1., 0.));
        vec3 normalized_light_angle = normalize(vec3(light_direction.x, light_direction.y, light_direction.z));

        float dot_product = dot(normalized_light_angle, normalized_normal_texture_angle);

        float m = pow(dot_product, light_attenuation);
        //float m = dot_product;

        color.r = color.r *= m; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
        color.g = color.g *= m; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
        color.b = color.b *= m; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
        color.a = color.a;
     }

     void alter_by_normal_texture_color_OLD(inout vec4 color, in vec4 normal_color)
     {
        //int spread = 1;
        int light_direction_y = int(floor(light_direction.y * 8.0 + 0.5));
        int angle_to_light_y = int(floor(normal_color.g * 8.0 + 0.5));
        bool in_shadow =
          (abs(float(light_direction_y) - float(angle_to_light_y)) > float(4));
        bool in_light =
          (abs(float(light_direction_y) - float(angle_to_light_y)) < max(1.0, float(light_spread * 2)));

        if (in_shadow)
        {
           // darken
           color.r = color.r *= 0.9; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
           color.g = color.g *= 0.9; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
           color.b = color.b *= 0.9; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
           color.a = color.a *= 0.9;
        }

        if (in_light)
        {
           //return;
           // brighten
           color.r = color.r += 0.2; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
           color.g = color.g += 0.2; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
           color.b = color.b += 0.2; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
           color.a = color.a += 0.2;
        }
        else
        {
           return;
           color.r = color.r *= 0.9; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
           color.g = color.g *= 0.9; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
           color.b = color.b *= 0.9; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
           color.a = color.a *= 0.9;
        }
     }

   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace Tileo


