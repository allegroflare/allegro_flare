

#include <AllegroFlare/Physics/CollisionMeshFace.hpp>

#include <AllegroFlare/Useful.hpp>
#include <allegro5/allegro_primitives.h>


namespace AllegroFlare
{
namespace Physics
{


CollisionMeshFace::CollisionMeshFace()
   : av0({})
   , av1({})
   , av2({})
   , v0({})
   , v1({})
   , v2({})
   , normal({})
   , centroid({})
   , disabled(false)
   , parent_models_object_num(0)
   , parent_models_face_num(0)
{
}


CollisionMeshFace::~CollisionMeshFace()
{
}


AllegroFlare::Physics::CollisionMeshFace CollisionMeshFace::build(AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2, int parent_models_object_num, int parent_models_face_num, AllegroFlare::Vec3D normal)
{
   AllegroFlare::Physics::CollisionMeshFace result;

   result.av0 = av0;
   result.av1 = av1;
   result.av2 = av2;
   result.v0 = AllegroFlare::vec3d(av0.x, av0.y, av0.z);
   result.v1 = AllegroFlare::vec3d(av1.x, av1.y, av1.z);
   result.v2 = AllegroFlare::vec3d(av2.x, av2.y, av2.z);
   result.normal = normal;
   result.centroid = (result.v0 + result.v1 + result.v2) / 3;
   result.parent_models_object_num = parent_models_object_num;
   result.parent_models_face_num = parent_models_face_num;

   //: av0(av0)
   //, av1(av1)
   //, av2(av2)
   //, v0(AllegroFlare::vec3d(av0.x, av0.y, av0.z))
   //, v1(AllegroFlare::vec3d(av1.x, av1.y, av1.z))
   //, v2(AllegroFlare::vec3d(av2.x, av2.y, av2.z))
   //, normal(normal)
   //, centroid((v0+v1+v2)/3)
   //, parent_models_object_num(parent_models_object_num)
   //, parent_models_face_num(parent_models_face_num)

   return result;
}

bool CollisionMeshFace::intersect(AllegroFlare::Useful3D::Ray* r, AllegroFlare::Useful3D::IntersectData* isectData)
{
   // TODO: Test this method
   // Source: http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
   // See also: https://www.youtube.com/watch?v=fK1RPmF_zjQ&ab_channel=enigmatutorials
   //#ifdef MOLLER_TRUMBORE
   AllegroFlare::vec3d edge1 = v1 - v0;
   AllegroFlare::vec3d edge2 = v2 - v0;
   //AllegroFlare::vec3d pvec = cross_product(r.dir, edge2);
   AllegroFlare::vec3d pvec = AllegroFlare::cross_product(r->dir, edge2);
   float det = dot_product(edge1, pvec);
   if (det == 0) return false;
   float invDet = 1 / det;
   AllegroFlare::vec3d tvec = r->orig - v0;
   isectData->u = dot_product(tvec, pvec) * invDet;
   if (isectData->u < 0 || isectData->u > 1) return false;
   AllegroFlare::vec3d qvec = AllegroFlare::cross_product(tvec, edge1);
   isectData->v = dot_product(r->dir, qvec) * invDet;
   if (isectData->v < 0 || isectData->u + isectData->v > 1) return false;
   isectData->t = dot_product(edge2, qvec) * invDet;
   return true;
}

void CollisionMeshFace::draw(ALLEGRO_COLOR col)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL vtx[4];
   vtx[0] = _create_vtx(v0, col);
   vtx[1] = _create_vtx(v1, col);
   vtx[2] = _create_vtx(v2, col);
   vtx[3] = _create_vtx(v0, col);
   //al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   al_draw_prim(vtx, NULL, NULL, 0, 4, ALLEGRO_PRIM_LINE_LIST);
   return;
}

AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL CollisionMeshFace::_create_vtx(AllegroFlare::Vec3D vec, ALLEGRO_COLOR col)
{
   //static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
   //{
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL ret_val;
      ret_val.x = vec.x;
      ret_val.y = vec.y;
      ret_val.z = vec.z;
      ret_val.u = 0;
      ret_val.v = 0;
      ret_val.nx = 0;
      ret_val.ny = 1;
      ret_val.nz = 0;
      ret_val.color = col;
      //return build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
      return ret_val;
   //}
}


} // namespace Physics
} // namespace AllegroFlare


