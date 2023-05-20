#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityDimension
         {
         private:
            std::string name;
            std::string description;
            std::string descriptor_very_low;
            std::string descriptor_low;
            std::string descriptor_balanced;
            std::string descriptor_high;
            std::string descriptor_very_high;

         protected:


         public:
            PersonalityDimension(std::string name="[unset-name]", std::string description="[unset-description]", std::string descriptor_very_low="[unset-descriptor_very_low]", std::string descriptor_low="[unset-descriptor_low]", std::string descriptor_balanced="[unset-descriptor_balanced]", std::string descriptor_high="[unset-descriptor_high]", std::string descriptor_very_high="[unset-descriptor_very_high]");
            ~PersonalityDimension();

            void set_name(std::string name);
            void set_description(std::string description);
            void set_descriptor_very_low(std::string descriptor_very_low);
            void set_descriptor_low(std::string descriptor_low);
            void set_descriptor_balanced(std::string descriptor_balanced);
            void set_descriptor_high(std::string descriptor_high);
            void set_descriptor_very_high(std::string descriptor_very_high);
            std::string get_name() const;
            std::string get_description() const;
            std::string get_descriptor_very_low() const;
            std::string get_descriptor_low() const;
            std::string get_descriptor_balanced() const;
            std::string get_descriptor_high() const;
            std::string get_descriptor_very_high() const;
            std::string get_descriptor_for_level(uint32_t ranking_level=0);
         };
      }
   }
}



