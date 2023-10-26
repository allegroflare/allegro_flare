#pragma once


#include <AllegroFlare/DialogSystem/Scenes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace Scenes
      {
         class Basic : public AllegroFlare::DialogSystem::Scenes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/Scenes/Basic";

         private:
            std::string location_name;
            std::string background_image_identifier;
            std::string ambience_sound_effect_identifier;

         protected:


         public:
            Basic(std::string location_name="[unset-property]", std::string background_image_identifier="[unset-property]", std::string ambience_sound_effect_identifier="[unset-ambience_sound_effect_identifier]");
            ~Basic();

            void set_location_name(std::string location_name);
            void set_background_image_identifier(std::string background_image_identifier);
            void set_ambience_sound_effect_identifier(std::string ambience_sound_effect_identifier);
            std::string get_location_name() const;
            std::string get_background_image_identifier() const;
            std::string get_ambience_sound_effect_identifier() const;
         };
      }
   }
}



