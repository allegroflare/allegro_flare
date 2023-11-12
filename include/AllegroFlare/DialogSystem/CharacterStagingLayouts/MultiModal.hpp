#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace CharacterStagingLayouts
      {
         class MultiModal : public AllegroFlare::DialogSystem::CharacterStagingLayouts::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            ALLEGRO_BITMAP* speaking_character_bitmap;
            float speaking_character_bitmap_changed_at;
            int surface_width;
            int surface_height;

         protected:


         public:
            MultiModal(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            virtual ~MultiModal();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            int get_surface_width() const;
            int get_surface_height() const;
            virtual void set_staged_character_expression(std::string staged_character_identifier="[unset-staged_character_identifier]", std::string expression="[unset-expression]", float time_now=0.0f) override;
            void __set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr, float time_now=0.0f);
            virtual void update(float time_now=0.0f) override;
            virtual void show(float time_now=0.0f) override;
            virtual void hide(float time_now=0.0f) override;
            virtual void clear() override;
            virtual void render() override;
         };
      }
   }
}



