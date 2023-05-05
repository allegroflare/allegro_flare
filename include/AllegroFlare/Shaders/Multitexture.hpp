#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Multitexture : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Multitexture";

      private:
         bool initialized;
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         Multitexture();
         ~Multitexture();

         void initialize();
         void activate();
      };
   }
}



