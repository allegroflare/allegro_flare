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
         ALLEGRO_COLOR flat_color;
         float flat_color_intensity;
         float darkness;
         float saturation;
         float red_channel_multiplier;
         float green_channel_multiplier;
         float blue_channel_multiplier;
         float hue_rotation;
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
         ALLEGRO_COLOR get_flat_color() const;
         float get_flat_color_intensity() const;
         float get_darkness() const;
         float get_saturation() const;
         float get_red_channel_multiplier() const;
         float get_green_channel_multiplier() const;
         float get_blue_channel_multiplier() const;
         float get_hue_rotation() const;
         void initialize();
         void set_flat_color(ALLEGRO_COLOR flat_color=ALLEGRO_COLOR{1, 1, 1, 1});
         void set_tint_color(ALLEGRO_COLOR tint_color=ALLEGRO_COLOR{1, 1, 1, 1});
         void set_tint_color_is_used(bool tint_color_is_used=false);
         void set_saturation(float saturation=1.0f);
         void set_flat_color_intensity(float flat_color_intensity=1.0f);
         void set_darkness(float darkness=0.0f);
         void set_red_channel_multiplier(float red_channel_multiplier=0.0f);
         void set_green_channel_multiplier(float green_channel_multiplier=0.0f);
         void set_blue_channel_multiplier(float blue_channel_multiplier=0.0f);
         void set_hue_rotation(float hue_rotation=0.0f);
         void activate();
      };
   }
}



