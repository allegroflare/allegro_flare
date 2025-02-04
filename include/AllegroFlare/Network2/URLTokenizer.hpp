#pragma once


#include <cstddef>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace Network2
   {
      class URLTokenizer
      {
      private:
         std::string full_url;
         static bool has_min_length(std::string string="", std::size_t min=0);
         static bool fits_max_length(std::string string="", std::size_t max=0);
         static bool only_numerical_characters(std::string string="");
         static std::string trim(std::string s="");

      protected:


      public:
         URLTokenizer(std::string full_url="[unset-full_url]");
         ~URLTokenizer();

         void set_full_url(std::string full_url);
         std::string get_full_url() const;
         std::string extract_port();
         std::string extract_host();
         std::pair<std::string, std::string> split_tokens();
      };
   }
}



