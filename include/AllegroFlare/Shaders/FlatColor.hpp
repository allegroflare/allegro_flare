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
         ALLEGRO_COLOR color;
         float color_intensity;
         bool initialized;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         FlatColor();
         ~FlatColor();

         ALLEGRO_COLOR get_color() const;
         float get_color_intensity() const;
         void initialize();
         void set_color(ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         void set_color_intensity(float color_intensity=1.0f);
         void activate();
      };
   }
}



