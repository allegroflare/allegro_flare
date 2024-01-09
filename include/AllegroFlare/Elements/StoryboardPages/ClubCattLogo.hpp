#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/ClubCatt/Logo.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/RenderSurfaces/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class ClubCattLogo : public AllegroFlare::Elements::StoryboardPages::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/StoryboardPages/ClubCattLogo";

         private:
            AllegroFlare::RenderSurfaces::Base* render_surface;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::ClubCatt::Logo clubcatt_logo;
            bool initialized;

         protected:


         public:
            ClubCattLogo(AllegroFlare::RenderSurfaces::Base* render_surface=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
            virtual ~ClubCattLogo();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            AllegroFlare::RenderSurfaces::Base* get_render_surface() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::ModelBin* get_model_bin() const;
            void set_render_surface(AllegroFlare::RenderSurfaces::Base* render_surface=nullptr);
            void initialize();
            void disable_clearing_background_color();
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
         };
      }
   }
}



