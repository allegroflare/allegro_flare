#pragma once


#include <AllegroFlare/Shader.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      class Base : public AllegroFlare::Shader
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/Base";

      private:
         std::string type;
         std::string vertex_source_code;
         std::string fragment_source_code;

      protected:


      public:
         Base(std::string type=AllegroFlare::Shaders::Base::TYPE, std::string vertex_source_code="", std::string fragment_source_code="");
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
         static bool set_sampler(std::string name="[unset-name]", ALLEGRO_BITMAP* bitmap=nullptr, int unit=0);
         static bool set_mat4(std::string name="[unset-name]", ALLEGRO_TRANSFORM* transform=nullptr);
         void hotload(std::string vertex_source_code="", std::string fragment_source_code="");
      };
   }
}



