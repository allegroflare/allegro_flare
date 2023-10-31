#pragma once


#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace CharacterStagingLayouts
      {
         class BasicCentered : public AllegroFlare::DialogSystem::CharacterStagingLayouts::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered";

         private:
            ALLEGRO_BITMAP* speaking_character_bitmap;
            float speaking_character_bitmap_changed_at;
            int surface_width;
            int surface_height;

         protected:


         public:
            BasicCentered();
            virtual ~BasicCentered();

            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            int get_surface_width() const;
            int get_surface_height() const;
            void clear_speaking_character_bitmap();
            void set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr, float time_now=0.0f);
            void swap_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr);
            virtual void show(float time_now=0.0f) override;
            virtual void hide(float time_now=0.0f) override;
            virtual void clear() override;
            virtual void update(float time_now=0.0f) override;
            virtual void render() override;
         };
      }
   }
}



