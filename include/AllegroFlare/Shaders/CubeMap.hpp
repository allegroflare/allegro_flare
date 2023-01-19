#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class CubeMap : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/CubeMap";

      private:
         std::string property;
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         CubeMap(std::string property="[unset-property]");
         ~CubeMap();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



