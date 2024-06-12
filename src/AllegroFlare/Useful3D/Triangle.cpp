

#include <AllegroFlare/Useful3D/Triangle.hpp>

#include <AllegroFlare/Useful.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Useful3D
{


Triangle::Triangle(AllegroFlare::vec3d v0, AllegroFlare::vec3d v1, AllegroFlare::vec3d v2)
   : v0(v0)
   , v1(v1)
   , v2(v2)
{
}


Triangle::~Triangle()
{
}


bool Triangle::intersect(AllegroFlare::Useful3D::Ray* ray_, AllegroFlare::Useful3D::IntersectData* intersect_data)
{
   if (!(ray_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Useful3D::Triangle::intersect]: error: guard \"ray_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Useful3D::Triangle::intersect]: error: guard \"ray_\" not met");
   }
   if (!(intersect_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Useful3D::Triangle::intersect]: error: guard \"intersect_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Useful3D::Triangle::intersect]: error: guard \"intersect_data\" not met");
   }
   IntersectData &isectData = (*intersect_data);
   Ray &ray = (*ray_);

   //http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
   AllegroFlare::vec3d edge1 = v1 - v0;
   AllegroFlare::vec3d edge2 = v2 - v0;
   AllegroFlare::vec3d pvec = cross_product(ray.dir, edge2);

   float det = dot_product(edge1, pvec);
   if (det == 0) return false;
   float invDet = 1 / det;
   AllegroFlare::vec3d tvec = ray.orig - v0;
   isectData.u = dot_product(tvec, pvec) * invDet;
   if (isectData.u < 0 || isectData.u > 1) return false;
   AllegroFlare::vec3d qvec = cross_product(tvec, edge1);
   isectData.v = dot_product(ray.dir, qvec) * invDet;
   if (isectData.v < 0 || isectData.u + isectData.v > 1) return false;
   isectData.t = dot_product(edge2, qvec) * invDet;

   return true;
}

void Triangle::draw(ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Useful3D::Triangle::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Useful3D::Triangle::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_VERTEX vtx[3];
   vtx[0] = AllegroFlare::build_vertex(v0.x, v0.y, v0.z, color, 0, 0);
   vtx[1] = AllegroFlare::build_vertex(v1.x, v1.y, v1.z, color, 0, 0);
   vtx[2] = AllegroFlare::build_vertex(v2.x, v2.y, v2.z, color, 0, 0);
   al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   return;
}


} // namespace Useful3D
} // namespace AllegroFlare


