#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class AllegroDefault : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/AllegroDefault";

      private:
         bool initialized;
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         AllegroDefault();
         ~AllegroDefault();

         void initialize();
         void activate();
      };
   }
}



