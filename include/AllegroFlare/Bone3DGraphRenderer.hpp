#pragma once


#include <AllegroFlare/Bone3D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   class Bone3DGraphRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::Bone3D* root_bone;

   public:
      Bone3DGraphRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Bone3D* root_bone={});
      ~Bone3DGraphRenderer();

      void render();
      void render_recursive(AllegroFlare::Bone3D* bone=nullptr);
      ALLEGRO_FONT* obtain_font();
   };
}



