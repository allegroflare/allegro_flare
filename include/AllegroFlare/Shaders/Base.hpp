#pragma once


#include <AllegroFlare/Shader.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Base : public AllegroFlare::Shader
      {
      public:
         static constexpr char* TYPE = "Shaders/Base";

      private:
         std::string type;
         std::string vertex_source_code;
         std::string fragment_source_code;

      protected:


      public:
         Base(std::string type=AllegroFlare::Shaders::Base::TYPE, std::string vertex_source_code="", std::string fragment_source_code="");
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



