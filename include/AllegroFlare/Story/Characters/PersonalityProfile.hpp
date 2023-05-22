#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfileDimension.hpp>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfile
         {
         private:
            std::string character_name;
            std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions;
            std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");

         protected:


         public:
            PersonalityProfile(std::string character_name="[unset-character_name]", std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions={});
            ~PersonalityProfile();

            void set_character_name(std::string character_name);
            void set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions);
            std::string get_character_name() const;
            std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> get_personality_dimensions() const;
            std::size_t num_personality_dimensions();
            void add_personality_dimension(AllegroFlare::Story::Characters::PersonalityProfileDimension personality_dimension={});
            bool personality_dimension_with_title_exists(std::string title="[unset-title]");
            AllegroFlare::Story::Characters::PersonalityProfileDimension get_personality_dimension_by_index(std::size_t index=0);
            std::string build_personality_dimensions_writeup();
            static std::string build_writeup_for_dimension(std::string character_name="this character", std::string dimension_name="[unset-dimension_name]", std::string dimension_description="[unset-dimension_description]", uint32_t dimension_ranking_level=0, std::string dimension_descriptor_for_level="[unset-dimension_descriptor_for_level]");
            std::string build_brief_writeup_for_dimension();
            static std::string ranking_level_to_text(uint32_t ranking_level=0);
            std::string join_with_and(std::vector<std::string> tokens={}, std::string delimiter=", ", bool use_and=false);
         };
      }
   }
}



