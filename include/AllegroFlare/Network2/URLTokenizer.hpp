#pragma once


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
         std::pair<std::string, std::string> split_tokens();
         static std::string trim(std::string s="");

      protected:


      public:
         URLTokenizer(std::string full_url="[unset-full_url]");
         ~URLTokenizer();

         void set_full_url(std::string full_url);
         std::string get_full_url() const;
         std::string extract_port();
         std::string extract_host();
      };
   }
}



