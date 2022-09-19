#pragma once


#include <Tileo/Shaders/Base.hpp>
#include <string>


namespace Tileo
{
   namespace Shaders
   {
      class AllegroDefault : private Tileo::Shaders::Base
      {
      private:
         bool initialized;

      public:
         AllegroDefault();
         ~AllegroDefault();

         void initialize();
         void activate();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}



