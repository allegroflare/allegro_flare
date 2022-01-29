#ifndef __AF_USEFUL_3D_HEADER
#define __AF_USEFUL_3D_HEADER




#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/Color.hpp>
#include <math.h> // for fabs



namespace allegro_flare
{
   /*
   static vec3d cross_product(vec3d A, vec3d B)
   {
      vec3d vector;
      vector.x = A.y*B.z - B.y*A.z;
      vector.y = B.x*A.z - A.x*B.z;
      vector.z = A.x*B.y - A.y*B.x;
      return vector;
   }




   static float dot_product(vec3d A, vec3d B)
   {
      return A * B;
   }
   */



   // http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-plane-and-ray-disk-intersection/
   // I believe...
   // l0 is the origin of the ray
   // l is the ray direction
   // p0 is a point on the plane
   // n is the plane normal
   // THIS HAS NOT BEEN USED, YET:
   static bool intersectPlane(const AllegroFlare::vec3d &n, const AllegroFlare::vec3d &p0, const AllegroFlare::vec3d& l0, const AllegroFlare::vec3d &l, float &d)
   {
      // assuming vectors are all normalized
      float denom = dot_product(n, l);
      if (denom > 1e-6) {
         AllegroFlare::vec3d p0l0 = p0 - l0;
         d = dot_product(p0l0, n) / denom;
         return (d >= 0);
      }
      return false;
   }




   class Ray // TODO: rename this to Ray3D and make an alternative Ray2D
   {
   public:
      AllegroFlare::vec3d orig;
      AllegroFlare::vec3d dir;
      Ray(AllegroFlare::vec3d orig, AllegroFlare::vec3d dir)
         : orig(orig)
         , dir(dir)
      {}
   };




   class IsectData
   {
   public:
      float t;
      float u;
      float v;
      IsectData()
         : t(0)
         , u(0)
         , v(0)
      {}
   };




   class Triangle
   {
   public:
      AllegroFlare::vec3d v0, v1, v2;

      Triangle(AllegroFlare::vec3d v0, AllegroFlare::vec3d v1, AllegroFlare::vec3d v2)
         : v0(v0)
         , v1(v1)
         , v2(v2)
      {}

      bool intersect(const Ray &ray, IsectData &isectData) const
      {
         //http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
         //#ifdef MOLLER_TRUMBORE
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
         //#else
         //    ...
         //#endif
         return true;
      }

      ALLEGRO_VERTEX _create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
      {
         return AllegroFlare::build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
      }

      void draw(ALLEGRO_COLOR col = AllegroFlare::color::orange)
      {
         ALLEGRO_VERTEX vtx[3];
         vtx[0] = _create_vtx(v0, col);
         vtx[1] = _create_vtx(v1, col);
         vtx[2] = _create_vtx(v2, col);
         al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
      }
   };




   static void draw_3d_line(AllegroFlare::vec3d start, AllegroFlare::vec3d end, ALLEGRO_COLOR col=AllegroFlare::color::red)
   {
      ALLEGRO_VERTEX vtx[2];
      vtx[0] = AllegroFlare::build_vertex(start.x, start.y, start.z, col, 0, 0);
      vtx[1] = AllegroFlare::build_vertex(end.x, end.y, end.z, col, 0, 0);
      al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
   }




   static ALLEGRO_VERTEX create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
   {
      return AllegroFlare::build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
   }




   static AllegroFlare::vec3d centroid(AllegroFlare::vec3d v1, AllegroFlare::vec3d v2, AllegroFlare::vec3d v3)
   {
      return (v1 + v2 + v3) / 3;
   }




   static AllegroFlare::vec3d tovec3d(ALLEGRO_VERTEX v1)
   {
      return AllegroFlare::vec3d(v1.x, v1.y, v1.z);
   }




   static AllegroFlare::vec3d centroid(AllegroFlare::vec3d v1, AllegroFlare::vec3d v2, AllegroFlare::vec3d v3, AllegroFlare::vec3d v4)
   {
      return (v1 + v2 + v3 + v4) / 4;
   }




   static void draw_3d_triangle(AllegroFlare::vec3d v1, AllegroFlare::vec3d v2, AllegroFlare::vec3d v3, ALLEGRO_COLOR col)
   {
      ALLEGRO_VERTEX vtx[3];
      vtx[0] = create_vtx(v1, col);
      vtx[1] = create_vtx(v2, col);
      vtx[2] = create_vtx(v3, col);
      al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   }




   static bool basically_equal(const AllegroFlare::vec3d &first, const AllegroFlare::vec3d &other, float threshold)
   {
      return fabs(first.x - other.x) < threshold && fabs(first.y - other.y) < threshold && fabs(first.z - other.z) < threshold;
   }
}




#endif
