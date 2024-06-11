#pragma once


#include <AllegroFlare/StringTransformer.hpp>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class StringTransformer
   {
   private:
      std::string text;

   protected:


   public:
      StringTransformer(std::string text="[unset-text]");
      ~StringTransformer();

      std::string get_text() const;
      AllegroFlare::StringTransformer& upcase();
      AllegroFlare::StringTransformer& expand(int num_spaces=3);
      static std::string join_with_commas(std::set<std::string>* elements=nullptr);
      static std::string join(std::vector<std::string>* elements=nullptr, std::string interpolation_string=", ");
      static std::string remove_non_alphanumeric(std::string input="[unset-input]");
   };
}



