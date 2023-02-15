#pragma once


#include <string>


namespace AllegroFlare { class Cubemap; };


namespace AllegroFlare
{
   class CubemapTextureBinder
   {
   private:
      std::string name;
      AllegroFlare::Cubemap *cubemap;
      int unit;

   public:
      CubemapTextureBinder(std::string name="[unset-name]", AllegroFlare::Cubemap *cubemap=nullptr, int unit=0);
      ~CubemapTextureBinder();

      bool bind();
   };
}


