#pragma once


#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <allegro5/allegro.h>
#include <lib/tsl/ordered_map.h>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace CharacterStagingLayouts
      {
         class Dynamic : public AllegroFlare::DialogSystem::CharacterStagingLayouts::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic";

         private:
            tsl::ordered_map<std::string, std::tuple<ALLEGRO_BITMAP*, AllegroFlare::Placement3D>> staged_characters;
            int surface_width;
            int surface_height;
            bool hidden;

         protected:


         public:
            Dynamic();
            virtual ~Dynamic();

            void set_staged_characters(tsl::ordered_map<std::string, std::tuple<ALLEGRO_BITMAP*, AllegroFlare::Placement3D>> staged_characters);
            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            tsl::ordered_map<std::string, std::tuple<ALLEGRO_BITMAP*, AllegroFlare::Placement3D>> get_staged_characters() const;
            int get_surface_width() const;
            int get_surface_height() const;
            bool get_hidden() const;
            virtual void update(float time_now=0.0f) override;
            virtual void show(float time_now=0.0f) override;
            virtual void hide(float time_now=0.0f) override;
            virtual void clear() override;
            virtual void render() override;
            virtual void set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr, float time_now=0.0f) override;
         };
      }
   }
}



