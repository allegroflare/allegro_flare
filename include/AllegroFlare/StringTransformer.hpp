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
      static std::string quote_and_escape_inner_quotes(std::string subject="[unset-subject]");
      static std::string replace(std::string subject="[unset-subject]", std::string search="[unset-search]", std::string replace="[unset-replace]");

   protected:


   public:
      StringTransformer(std::string text="[unset-text]");
      ~StringTransformer();

      std::string get_text() const;
      AllegroFlare::StringTransformer& upcase();
      AllegroFlare::StringTransformer& expand(int num_spaces=3);
      static std::string join_quoted_with_commas(std::set<std::string>* elements=nullptr);
      static std::string join_with_commas(std::set<std::string>* elements=nullptr);
      static std::string join(std::vector<std::string>* elements=nullptr, std::string interpolation_string=", ");
      static std::string remove_non_alphanumeric(std::string input="[unset-input]");
      static std::vector<std::string> split(std::string string="", char delimiter=' ');
      static std::vector<std::string> tokenize(std::string str="", char delim='|');
      static std::string trim(std::string s="");
   };
}



