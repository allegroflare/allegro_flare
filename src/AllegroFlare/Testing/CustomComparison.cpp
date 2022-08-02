

#include <AllegroFlare/Testing/CustomComparison.hpp>


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Color& color, ::std::ostream* os)
   {
      *os << "AllegroFlare::Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
   }
}

