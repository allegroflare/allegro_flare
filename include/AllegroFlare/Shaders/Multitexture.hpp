#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>
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
         ALLEGRO_BITMAP* texture_a;
         ALLEGRO_BITMAP* texture_b;
         bool initialized;
         void set_values_to_activated_shader();
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();

      protected:


      public:
         Multitexture();
         ~Multitexture();

         ALLEGRO_BITMAP* get_texture_a() const;
         ALLEGRO_BITMAP* get_texture_b() const;
         void initialize();
         void activate();
         void set_texture_a(ALLEGRO_BITMAP* texture_a=nullptr);
         void set_texture_b(ALLEGRO_BITMAP* texture_b=nullptr);
      };
   }
}



