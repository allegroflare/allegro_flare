#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Scene.hpp>
#include <AllegroFlare/ModelBin.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Basic3D : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/Basic3D";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
            bool initialized;

         protected:


         public:
            Basic3D();
            ~Basic3D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::ModelBin* get_model_bin() const;
            void initialize();
            void render() override;
         };
      }
   }
}



