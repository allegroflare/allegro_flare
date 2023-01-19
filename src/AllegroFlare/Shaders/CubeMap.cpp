

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
   // NOTE: this code was formerly in data/shaders/cube_vertex.glsl
   static const std::string source = R"DELIM(
      attribute vec4 al_pos;
      attribute vec3 al_user_attr_0;

      uniform mat4 al_projview_matrix;
      uniform mat4 position_transform;
      uniform vec3 camera_position;

      varying vec3 normal;
      varying vec3 eye_dir;
      uniform samplerCube cube_map_A;
      uniform samplerCube cube_map_B;

      void main()
      {
         gl_Position = al_projview_matrix * position_transform * al_pos;
         normal = (position_transform * vec4(al_user_attr_0, 0.0)).xyz;
         // this NORMAL val will probably ned to be multiplied by the position transform
          //	normal = (al_user_attr_0).xyz;
         vec3 world_position = (position_transform * al_pos).xyz;
         eye_dir = vec3(camera_position - world_position);
      }
   )DELIM";
   return source;
}

std::string CubeMap::obtain_fragment_source()
{
   // NOTE: this code was formerly in data/shaders/cube_fragment.glsl
   static const std::string source = R"DELIM(
      varying vec3 normal;
      varying vec3 eye_dir;
      uniform samplerCube cube_map_A;
      uniform samplerCube cube_map_B;
      //uniform sampler2D al_tex;
      uniform bool reflecting;

      void main()
      {
         vec3 reflected_dir = normalize(reflect(eye_dir, normalize(normal)));

         vec3 incoming_angle = reflecting ? reflected_dir : eye_dir;
         //vec3 incoming_angle = eye_dir;

         incoming_angle.y = -incoming_angle.y;
         incoming_angle.x = -incoming_angle.x;
         //incoming_angle.z = -incoming_angle.z;

         vec4 color = textureCube(cube_map_A, incoming_angle);
         //color = textureCube(cube_map_B, incoming_angle);
       

         vec4 golden_color = vec4(1.0, 0.74, 0.0, 1.0);

         color = golden_color * 0.6 + color * 0.7;
       
       
         gl_FragColor = color;
      }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace AllegroFlare


