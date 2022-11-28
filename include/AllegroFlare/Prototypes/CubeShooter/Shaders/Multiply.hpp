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
            class Multiply : public AllegroFlare::Shader
            {
            private:
               bool initialized;
               ALLEGRO_COLOR tint;
               float tint_intensity;
               float pulse_created_at;
               float time_now;
               float far_plane;
               void set_values_to_activated_shader();
               static std::string obtain_vertex_source();
               static std::string obtain_fragment_source();

            protected:


            public:
               Multiply();
               virtual ~Multiply();

               void set_tint(ALLEGRO_COLOR tint);
               void set_tint_intensity(float tint_intensity);
               void set_pulse_created_at(float pulse_created_at);
               void set_time_now(float time_now);
               void set_far_plane(float far_plane);
               ALLEGRO_COLOR get_tint() const;
               float get_tint_intensity() const;
               float get_pulse_created_at() const;
               float get_time_now() const;
               float get_far_plane() const;
               void initialize();
               virtual void activate() override;
            };
         }
      }
   }
}



