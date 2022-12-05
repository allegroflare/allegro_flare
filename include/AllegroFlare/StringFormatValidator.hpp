#pragma once


#include <string>


namespace AllegroFlare
{
   class StringFormatValidator
   {
   private:
      std::string string;

   protected:


   public:
      StringFormatValidator(std::string string="[unset-string]");
      ~StringFormatValidator();

      void set_string(std::string string);
      std::string get_string() const;
      bool fits_max_length(std::size_t max=0);
      bool only_numerical_characters();
   };
}



