#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class TiledTintColor : public AllegroFlare::Shaders::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/TiledTintColor";

      private:
         ALLEGRO_COLOR tint_color;
         bool tint_color_is_used;
         bool initialized;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         TiledTintColor();
         ~TiledTintColor();

         ALLEGRO_COLOR get_tint_color() const;
         bool get_tint_color_is_used() const;
         void initialize();
         void set_tint_color(ALLEGRO_COLOR tint_color=ALLEGRO_COLOR{1, 1, 1, 1});
         void set_tint_color_is_used(bool tint_color_is_used=false);
         void activate();
      };
   }
}



