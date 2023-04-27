

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>


//bool operator==(const AllegroFlare::Vec3D& vec, const AllegroFlare::Vec3D& other_vec)
//{
   //if (vec.x != other_vec.x) return false;
   //if (vec.y != other_vec.y) return false;
   //if (vec.z != other_vec.z) return false;
   //return true;
//}


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Vec3D& vec, ::std::ostream* os)
   {
      *os << "AllegroFlare::Vec3D(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
   }
}


