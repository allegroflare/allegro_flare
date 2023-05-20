#pragma once


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
            std::string descriptor_very_low;
            std::string descriptor_low;
            std::string descriptor_medium;
            std::string descriptor_high;
            std::string descriptor_very_high;

         protected:


         public:
            PersonalityDimension(std::string name="[unset-name]", std::string descriptor_very_low="[unset-descriptor_very_low]", std::string descriptor_low="[unset-descriptor_low]", std::string descriptor_medium="[unset-descriptor_medium]", std::string descriptor_high="[unset-descriptor_high]", std::string descriptor_very_high="[unset-descriptor_very_high]");
            ~PersonalityDimension();

            void set_name(std::string name);
            void set_descriptor_very_low(std::string descriptor_very_low);
            void set_descriptor_low(std::string descriptor_low);
            void set_descriptor_medium(std::string descriptor_medium);
            void set_descriptor_high(std::string descriptor_high);
            void set_descriptor_very_high(std::string descriptor_very_high);
            std::string get_name() const;
            std::string get_descriptor_very_low() const;
            std::string get_descriptor_low() const;
            std::string get_descriptor_medium() const;
            std::string get_descriptor_high() const;
            std::string get_descriptor_very_high() const;
         };
      }
   }
}



