#pragma once


#include <AllegroFlare/RenderSurfaces/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace RenderSurfaces
   {
      class Bitmap : public AllegroFlare::RenderSurfaces::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RenderSurfaces/Bitmap";

      private:
         std::string property;

      protected:


      public:
         Bitmap(std::string property="[unset-property]");
         ~Bitmap();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



