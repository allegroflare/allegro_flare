#pragma once


#include <AllegroFlare/StringTransformer.hpp>
#include <set>
#include <string>


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
   };
}


