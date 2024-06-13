

#include <AllegroFlare/Shaders/Cubemap.hpp>

#include <AllegroFlare/Placement3D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Shaders
{


Cubemap::Cubemap(AllegroFlare::Cubemap* cube_map, bool reflecting)
   : AllegroFlare::Shaders::Base(AllegroFlare::Shaders::Cubemap::TYPE, obtain_vertex_source(), obtain_fragment_source())
   , cube_map(cube_map)
   , camera_position(AllegroFlare::Vec3D(0, 0, 0))
   , object_placement_transform({})
   , reflecting(reflecting)
{
}


Cubemap::~Cubemap()
{
}


void Cubemap::set_cube_map(AllegroFlare::Cubemap* cube_map)
{
   this->cube_map = cube_map;
}


void Cubemap::set_camera_position(AllegroFlare::Vec3D camera_position)
{
   this->camera_position = camera_position;
}


void Cubemap::set_reflecting(bool reflecting)
{
   this->reflecting = reflecting;
}


AllegroFlare::Cubemap* Cubemap::get_cube_map() const
{
   return cube_map;
}


AllegroFlare::Vec3D Cubemap::get_camera_position() const
{
   return camera_position;
}


bool Cubemap::get_reflecting() const
{
   return reflecting;
}


void Cubemap::activate()
{
   AllegroFlare::Shaders::Base::activate();
   set_values_to_activated_shader();
   return;
}

void Cubemap::set_object_placement(AllegroFlare::Placement3D* object_placement)
{
   if (!(object_placement))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Shaders::Cubemap::set_object_placement]: error: guard \"object_placement\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Shaders::Cubemap::set_object_placement]: error: guard \"object_placement\" not met");
   }
   object_placement->build_transform(&object_placement_transform);

   // TODO: if this shader is active, send the value to the shader directly
   return;
}

void Cubemap::set_values_to_activated_shader()
{
   set_sampler_cube("cube_map_A", cube_map, 5); // ?? why 5? dunno
   set_vec3("camera_position", camera_position);
   set_mat4("position_transform", &object_placement_transform);
   set_bool("reflecting", reflecting);
   // TODO: set_float("tint_intensity", tint_intensity);
   return;
}

std::string Cubemap::obtain_vertex_source()
{
   // HERE: Finishing this code
   // NOTE: this code was formerly in data/shaders/cube_vertex.glsl
   static const std::string source = R"DELIM(
      attribute vec4 al_pos;
      attribute vec3 al_user_attr_0; // Not sure if this is needed?

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

std::string Cubemap::obtain_fragment_source()
{
   // HERE: Finishing this code
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
       

         // TODO: add this "golden_color" as an optional pass-in-able value
         //vec4 golden_color = vec4(1.0, 0.74, 0.0, 1.0);

         //color = golden_color * 0.6 + color * 0.7;
       
       
         gl_FragColor = color;
      }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace AllegroFlare


