

#include <AllegroFlare/Physics/AABB3D.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


AABB3D::AABB3D(AllegroFlare::Vec3D min, AllegroFlare::Vec3D max)
   : min(min)
   , max(max)
{
}


AABB3D::~AABB3D()
{
}


void AABB3D::set_min(AllegroFlare::Vec3D min)
{
   this->min = min;
}


void AABB3D::set_max(AllegroFlare::Vec3D max)
{
   this->max = max;
}


AllegroFlare::Vec3D AABB3D::get_min() const
{
   return min;
}


AllegroFlare::Vec3D AABB3D::get_max() const
{
   return max;
}


void AABB3D::expand(float amount)
{
   if (!((amount > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AABB3D::expand]: error: guard \"(amount > 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AABB3D::expand: error: guard \"(amount > 0.0f)\" not met");
   }
   min.x -= amount;
   min.y -= amount;
   min.z -= amount;
   max.x += amount;
   max.y += amount;
   max.z += amount;
   return;
}

bool AABB3D::collides(AllegroFlare::Physics::AABB3D* other, AllegroFlare::Vec3D self_offset, AllegroFlare::Vec3D other_offset)
{
   if (!(other))
   {
      std::stringstream error_message;
      error_message << "[AABB3D::collides]: error: guard \"other\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AABB3D::collides: error: guard \"other\" not met");
   }
   // TODO: consider less assignment, add values directly into the conditional

   AllegroFlare::Vec3D a_min = min + self_offset;
   AllegroFlare::Vec3D a_max = max + self_offset;
   AllegroFlare::Vec3D b_min = other->min + other_offset;
   AllegroFlare::Vec3D b_max = other->max + other_offset;

   return (
      a_min.x <= b_max.x &&
      a_max.x >= b_min.x &&
      a_min.y <= b_max.y &&
      a_max.y >= b_min.y &&
      a_min.z <= b_max.z &&
      a_max.z >= b_min.z
   );
}

bool AABB3D::collides_with_point(AllegroFlare::Vec3D point, AllegroFlare::Vec3D self_offset, AllegroFlare::Vec3D other_offset)
{
   // TODO: Test this!!
   // TODO: consider less assignment, add values directly into the conditional

   AllegroFlare::Vec3D a_min = min + self_offset;
   AllegroFlare::Vec3D a_max = max + self_offset;
   point += other_offset;
   //AllegroFlare::Vec3D b_min = point + other_offset;
   //AllegroFlare::Vec3D b_max = point + other_offset;

   // TODO: Could simplify this calculation to not 
   return (
      a_min.x <= point.x &&
      a_max.x >= point.x &&
      a_min.y <= point.y &&
      a_max.y >= point.y &&
      a_min.z <= point.z &&
      a_max.z >= point.z
   );
}

void AABB3D::draw(ALLEGRO_COLOR color, AllegroFlare::Vec3D offset)
{
   // TODO: this function
   // SEE: This chat: https://chat.openai.com/chat/98d67e07-868f-4703-9675-49b9d0b48afd

   //float x, float y, float z, ALLEGRO_COLOR col, float size)

   //ALLEGRO_VERTEX v[6];
   //float hsize = size/2;

   //for (unsigned i=0; i<6; i++)
      //v[i] = build_vertex(x, y, z, col, 0, 0);

   //v[0].x -= hsize;
   //v[1].x += hsize;

   //v[2].y -= hsize;
   //v[3].y += hsize;

   //v[4].z -= hsize;
   //v[5].z += hsize;

   //al_draw_prim(&v, NULL, NULL, 0, 6, ALLEGRO_PRIM_LINE_LIST);

   return;
}


} // namespace Physics
} // namespace AllegroFlare


