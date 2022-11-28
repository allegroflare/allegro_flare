#pragma once


#include <AllegroFlare/Shader.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         namespace Shaders
         {
            class Fog : public AllegroFlare::Shader
            {
            private:
               bool initialized;
               ALLEGRO_COLOR tint;
               float tint_intensity;
               void set_values_to_activated_shader();
               static std::string obtain_vertex_source();
               static std::string obtain_fragment_source();

            protected:


            public:
               Fog();
               virtual ~Fog();

               void set_tint(ALLEGRO_COLOR tint);
               void set_tint_intensity(float tint_intensity);
               ALLEGRO_COLOR get_tint() const;
               float get_tint_intensity() const;
               void initialize();
               virtual void activate() override;
            };
         }
      }
   }
}



