#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


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
            AllegroFlare::BitmapBin* bitmap_bin;
            std::vector<std::tuple<std::string, std::string, AllegroFlare::Placement3D>> staged_characters;
            std::map<std::pair<std::string, std::string>, std::string> staged_character_expression_db;
            int surface_width;
            int surface_height;
            bool hidden;

         protected:


         public:
            Dynamic(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            virtual ~Dynamic();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_staged_characters(std::vector<std::tuple<std::string, std::string, AllegroFlare::Placement3D>> staged_characters);
            void set_staged_character_expression_db(std::map<std::pair<std::string, std::string>, std::string> staged_character_expression_db);
            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::vector<std::tuple<std::string, std::string, AllegroFlare::Placement3D>> get_staged_characters() const;
            std::map<std::pair<std::string, std::string>, std::string> get_staged_character_expression_db() const;
            int get_surface_width() const;
            int get_surface_height() const;
            bool get_hidden() const;
            virtual void update(float time_now=0.0f) override;
            virtual void show(float time_now=0.0f) override;
            virtual void hide(float time_now=0.0f) override;
            virtual void clear() override;
            int num_staged_characters();
            bool staged_character_exists(std::string staged_character_identifier="[unset-staged_character_identifier]");
            std::tuple<std::string, std::string, AllegroFlare::Placement3D>* find_staged_character(std::string staged_character_identifier="[unset-staged_character_identifier]");
            bool staged_character_expression_exists(std::string staged_character_identifier="[unset-staged_character_identifier]", std::string expression="[unset-expression]");
            std::string find_staged_character_expression_bitmap_identifier(std::string staged_character_identifier="[unset-staged_character_identifier]", std::string expression="[unset-expression]");
            void add_staged_character(std::string staged_character_identifier="[unset-staged_character_identifier]", std::tuple<std::string, AllegroFlare::Placement3D> staging={});
            void set_staged_character_expression(std::string staged_character_identifier="[unset-staged_character_identifier]", std::string expression="[unset-expression]");
            AllegroFlare::Placement3D get_staged_character_placement(std::string staged_character_identifier="[unset-staged_character_identifier]");
            void set_staged_character_placement(std::string staged_character_identifier="[unset-staged_character_identifier]", AllegroFlare::Placement3D placement={});
            void move_staged_character_to_front(std::string staged_character_identifier="[unset-staged_character_identifier]");
            void move_staged_character_to_back(std::string staged_character_identifier="[unset-staged_character_identifier]");
            void move_staged_character_forward(std::string staged_character_identifier="[unset-staged_character_identifier]");
            void move_staged_character_backward(std::string staged_character_identifier="[unset-staged_character_identifier]");
            virtual void render() override;
            virtual void set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr, float time_now=0.0f) override;
         };
      }
   }
}



