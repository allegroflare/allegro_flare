#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class FlatColor : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/FlatColor";

      private:
         ALLEGRO_COLOR tint;
         float tint_intensity;
         bool initialized;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         FlatColor();
         ~FlatColor();

         void set_tint(ALLEGRO_COLOR tint);
         void set_tint_intensity(float tint_intensity);
         ALLEGRO_COLOR get_tint() const;
         float get_tint_intensity() const;
         void initialize();
         void activate();
      };
   }
}



