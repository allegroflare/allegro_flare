#pragma once


#include <string>
#include <vector>
#include <AllegroFlare/Useful.hpp>


namespace AllegroFlare
{
   namespace php
   {
      std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
      std::string implode(const std::string &delimiter, const std::vector<std::string> &parts);
      std::string strtoupper(std::string input);
      std::string str_replace(const std::string &search, const std::string &replace, std::string &subject);
      size_t strpos(const std::string &haystack, const std::string &needle, int offset=0);
      bool file_exists(std::string filename);
      std::string file_get_contents(std::string filename);
      bool file_put_contents(std::string filename, std::string contents);
      std::string ltrim(std::string &s);
      std::string rtrim(std::string &s);
      std::string trim(std::string &s);
      char *url_encode(char *str);
      char *url_decode(char *str);
      std::string number_format(double number, int precision);
   }
}


