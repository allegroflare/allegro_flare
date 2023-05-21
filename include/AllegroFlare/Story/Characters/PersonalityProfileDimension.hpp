#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfileDimension
         {
         private:
            std::string title;
            uint32_t scoring;
            uint32_t scoring_max;
            std::string scoring_descriptor;

         protected:


         public:
            PersonalityProfileDimension(std::string title="[unset-title]", uint32_t scoring=0, uint32_t scoring_max=0, std::string scoring_descriptor="[unset-scoring_descriptor]");
            ~PersonalityProfileDimension();

            void set_title(std::string title);
            void set_scoring(uint32_t scoring);
            void set_scoring_max(uint32_t scoring_max);
            void set_scoring_descriptor(std::string scoring_descriptor);
            std::string get_title() const;
            uint32_t get_scoring() const;
            uint32_t get_scoring_max() const;
            std::string get_scoring_descriptor() const;
            float get_scoring_normalized();
         };
      }
   }
}



