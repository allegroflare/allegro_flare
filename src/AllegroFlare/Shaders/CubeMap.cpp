

#include <AllegroFlare/Shaders/CubeMap.hpp>




namespace AllegroFlare
{
namespace Shaders
{


CubeMap::CubeMap(std::string property)
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::CubeMap::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , property(property)
{
}


CubeMap::~CubeMap()
{
}


std::string CubeMap::get_property() const
{
   return property;
}


bool CubeMap::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}

std::string CubeMap::obtain_vertex_source()
{
   // TODO: replace this code with CubeMap code
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

std::string CubeMap::obtain_fragment_source()
{
   // TODO: replace this code with CubeMap code
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

     void main()
     {
       vec4 c;
       if (al_use_tex)
         c = varying_color * texture2D(al_tex, varying_texcoord);
       else
         c = varying_color;
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
         gl_FragColor = c;
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


} // namespace Shaders
} // namespace AllegroFlare


