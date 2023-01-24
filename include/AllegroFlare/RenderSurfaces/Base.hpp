#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace RenderSurfaces
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"RenderSurfaces/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::RenderSurfaces::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual bool set_as_target() = 0;
         virtual ALLEGRO_BITMAP* obtain_surface() = 0;
         bool is_target();
         virtual int get_width() = 0;
         virtual int get_height() = 0;
         float get_center();
         float get_middle();
         bool is_type(std::string possible_type="");
         bool is_a_display_surface();
      };
   }
}



