

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Color.hpp>


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Color& color, ::std::ostream* os)
   {
      *os << "AllegroFlare::Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
   }
}


