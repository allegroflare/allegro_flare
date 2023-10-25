#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class CharacterFeature : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr float DEFAULT_DURATION = 6.0;
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/CharacterFeature";

         private:
            std::string character_name;
            std::string description;
            std::string character_image_identifier;
            float duration;

         protected:


         public:
            CharacterFeature(std::string character_name="[unset-character_name]", std::string description="[unset-description]", std::string character_image_identifier="[unset-character_image_identifier]", float duration=DEFAULT_DURATION);
            ~CharacterFeature();

            void set_character_name(std::string character_name);
            void set_description(std::string description);
            void set_character_image_identifier(std::string character_image_identifier);
            void set_duration(float duration);
            std::string get_character_name() const;
            std::string get_description() const;
            std::string get_character_image_identifier() const;
            float get_duration() const;
         };
      }
   }
}



