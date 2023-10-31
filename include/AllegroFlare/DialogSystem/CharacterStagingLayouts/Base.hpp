#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace CharacterStagingLayouts
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/CharacterStagingLayouts/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogSystem::CharacterStagingLayouts::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            virtual void set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap=nullptr, float time_now=0.0f);
            virtual void update(float time_now=0.0f);
            virtual void show(float time_now=0.0f);
            virtual void hide(float time_now=0.0f);
            virtual void clear();
            virtual void render();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



