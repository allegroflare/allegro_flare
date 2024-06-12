

#include <AllegroFlare/Shaders/Multitexture.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


Multitexture::Multitexture()
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::Multitexture::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , texture_a(nullptr)
   , texture_b(nullptr)
   , initialized(false)
{
}


Multitexture::~Multitexture()
{
}


void Multitexture::set_texture_a(ALLEGRO_BITMAP* texture_a)
{
   this->texture_a = texture_a;
}


void Multitexture::set_texture_b(ALLEGRO_BITMAP* texture_b)
{
   this->texture_b = texture_b;
}


ALLEGRO_BITMAP* Multitexture::get_texture_a() const
{
   return texture_a;
}


ALLEGRO_BITMAP* Multitexture::get_texture_b() const
{
   return texture_b;
}


void Multitexture::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void Multitexture::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::Multitexture::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::Multitexture::activate]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
}

void Multitexture::set_values_to_activated_shader()
{
   // TODO: set values
   //set_sampler_cube("cube_map_A", cube_map, 5); // ?? why 5? dunno
   set_sampler("texture_a", texture_a, 1);
   set_sampler("texture_b", texture_b, 2);
   //set_vec3("camera_position", camera_position);
   //set_mat4("position_transform", &object_placement_transform);
   //set_bool("reflecting", reflecting);
   return;
}

std::string Multitexture::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     attribute vec2 al_user_attr_0; // this is the uv2 coordinates
     uniform mat4 al_projview_matrix;
     uniform bool al_use_tex_matrix;
     uniform mat4 al_tex_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord_1;
     varying vec2 varying_texcoord_2;
     void main()
     {
       varying_color = al_color;
       if (al_use_tex_matrix)
       {
         // WARNING: The current design has the al_tex_matrix derived from the texture used in the al_draw_prim call.
         // This means 1) A texture must be passed during the al_draw_prim_call, 2) all textures used in the shader
         // must be of the same dimensions.  Ideally this would change so that a nullptr could be passed and
         // dimensions could be extracted for each texture.
         // TODO: Address the warning above

         vec4 uv1 = al_tex_matrix * vec4(al_texcoord, 0, 1);
         varying_texcoord_1 = vec2(uv1.x, uv1.y);

         vec4 uv2 = al_tex_matrix * vec4(al_user_attr_0, 0, 1);
         varying_texcoord_2 = vec2(uv2.x, uv2.y);
       }
       else
       {
         varying_texcoord_1 = al_texcoord;
         varying_texcoord_2 = al_user_attr_0;
       }
       gl_Position = al_projview_matrix * al_pos;
     }
   )DELIM";
   return source;
}

std::string Multitexture::obtain_fragment_source()
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

     uniform sampler2D texture_a;
     uniform sampler2D texture_b;
     varying vec2 varying_texcoord_1;
     varying vec2 varying_texcoord_2;

     bool alpha_test_func(float x, int op, float compare);

     void main()
     {
       vec4 c;
       if (al_use_tex)
       {
         vec4 c1 = varying_color * texture2D(texture_a, varying_texcoord_1);
         vec4 c2 = varying_color * texture2D(texture_b, varying_texcoord_2);
         c = c1 * c2;
         //c = varying_color * texture2D(texture_b, varying_texcoord_2);
         //c = varying_color * texture2D(al_tex, varying_texcoord_2);
       }
       else
       {
         c = varying_color;
       }
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
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


