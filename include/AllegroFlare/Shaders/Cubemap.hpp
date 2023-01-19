#pragma once


#include <AllegroFlare/Cubemap.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Cubemap : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Cubemap";

      private:
         AllegroFlare::Cubemap* cube_map;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         Cubemap(AllegroFlare::Cubemap* cube_map=nullptr);
         virtual ~Cubemap();

         void set_cube_map(AllegroFlare::Cubemap* cube_map);
         AllegroFlare::Cubemap* get_cube_map() const;
         virtual void activate() override;
      };
   }
}



