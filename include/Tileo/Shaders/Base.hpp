#pragma once


#include <AllegroFlare/Shader.hpp>
#include <string>


namespace Tileo
{
   namespace Shaders
   {
      class Base : public AllegroFlare::Shader
      {
      private:
         std::string vertex_source_code;
         std::string fragment_source_code;

      public:
         Base(std::string vertex_source_code="", std::string fragment_source_code="");
         ~Base();

      };
   }
}



