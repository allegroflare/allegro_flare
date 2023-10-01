#pragma once


#include <cstddef>
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
      bool fits_min_length(std::size_t min=0);
      bool has_only_numerical_characters();
      bool ends_with(std::string ending="");
   };
}



