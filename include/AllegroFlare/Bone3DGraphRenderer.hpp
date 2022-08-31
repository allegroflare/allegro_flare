#pragma once


#include <AllegroFlare/Bone3D.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   class Bone3DGraphRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::Bone3D* root_bone;

   protected:


   public:
      Bone3DGraphRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Bone3D* root_bone={});
      ~Bone3DGraphRenderer();

      void render();
      void render_recursive(AllegroFlare::Bone3D* bone=nullptr);
   };
}



