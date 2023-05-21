#pragma once


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
            std::string description;
            int scoring;
            int scoring_max;
            std::string scoring_descriptor;

         protected:


         public:
            PersonalityProfileDimension(std::string title="[unset-title]", std::string description="[unset-description]", int scoring=0, int scoring_max=0, std::string scoring_descriptor="[unset-scoring_descriptor]");
            ~PersonalityProfileDimension();

            void set_title(std::string title);
            void set_description(std::string description);
            void set_scoring(int scoring);
            void set_scoring_max(int scoring_max);
            void set_scoring_descriptor(std::string scoring_descriptor);
            std::string get_title() const;
            std::string get_description() const;
            int get_scoring() const;
            int get_scoring_max() const;
            std::string get_scoring_descriptor() const;
            float get_scoring_normalized();
         };
      }
   }
}



