#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace Tileo
{
   namespace Shaders
   {
      class Base : public AllegroFlare::Shaders::Base
      {
      private:
         std::string vertex_source_code;
         std::string fragment_source_code;

      protected:


      public:
         Base(std::string vertex_source_code="", std::string fragment_source_code="");
         ~Base();

      };
   }
}



