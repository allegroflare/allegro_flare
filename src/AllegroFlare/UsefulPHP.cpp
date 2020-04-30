



#include <AllegroFlare/UsefulPHP.hpp>

#include <algorithm>
#include <fstream>
#include <iomanip>




namespace AllegroFlare
{
   std::vector<std::string> php::explode(const std::string &delimiter, const std::string &str)
   {
      // note: this function skips multiple delimiters, e.g. it will not return return empty tokens
      std::vector<std::string> arr;

      int strleng = str.length();
      int delleng = delimiter.length();
      if (delleng==0)
         return arr;//no change

      int i=0;
      int k=0;
      while(i<strleng)
      {
         int j=0;
         while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
         if (j==delleng)//found delimiter
         {
            arr.push_back(str.substr(k, i-k));
            i+=delleng;
            k=i;
         }
         else
         {
            i++;
         }
      }
      arr.push_back(str.substr(k, i-k));
      return arr;
   }




   // UNTESTED
   std::string php::implode(const std::string &delimiter, const std::vector<std::string> &parts)
   {
      std::stringstream ss;
      for (unsigned i=0; i<parts.size(); i++)
      {
         ss << parts[i];
         if (i < (parts.size()-1)) ss << delimiter;
      }
      return ss.str();
   }




   std::string php::strtoupper(std::string input)
   {
      for (unsigned i=0; i<input.size(); i++)
         if ((input.at(i) <= 122) && (input.at(i) >= 97)) input[i] = input[i] - 32;
      return input;
   }




   // UNTESTED
   std::string php::str_replace(const std::string &search, const std::string &replace, std::string &subject)
   {
      std::string buffer;

      int sealeng = search.length();
      int strleng = subject.length();

      if (sealeng==0)
         return subject;//no change

      for(int i=0, j=0; i<strleng; j=0 )
      {
         while (i+j<strleng && j<sealeng && subject[i+j]==search[j])
            j++;
         if (j==sealeng)//found 'search'
         {
            buffer.append(replace);
            i+=sealeng;
         }
         else
         {
            buffer.append( &subject[i++], 1);
         }
      }
      subject = buffer;
      return subject;
   }




   // not tested, but from: http://www.zedwood.com/article/116/cpp-strpos-function
   size_t php::strpos(const std::string &haystack, const std::string &needle, int offset)
   {
      int sleng = haystack.length();
      int nleng = needle.length();

      if (sleng==0 || nleng==0)
         return std::string::npos;

      //for(int i=0, j=0; i<sleng; j=0, i++ )
      for(int i=offset, j=0; i<sleng; j=0, i++ )
      {
         while (i+j<sleng && j<nleng && haystack[i+j]==needle[j])
            j++;
         if (j==nleng)
            return i;
      }
      return std::string::npos;
   }




   bool php::file_exists(std::string filename)
   {
      std::fstream file(filename.c_str());
      if (!file) return false;
      return true;
   }




   std::string php::file_get_contents(std::string filename)
   {
      std::ifstream file(filename.c_str());
      std::string input = "";
      if (!file) return "";
      char ch;
      while (file.get(ch)) input.append(1, ch);
      if (!file.eof()) return ""; // strange error
      file.close();
      return input;
   }




   bool php::file_put_contents(std::string filename, std::string contents)
   {
      std::ofstream file;
      file.open(filename.c_str());
      if (!file.is_open()) return false;
      file << contents.c_str();
      file.close();
      return true;
   }




   // trim from start
   std::string php::ltrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
      //s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
      return s;
   }




   // trim from end
   std::string php::rtrim(std::string &s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
      //s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
      return s;
   }




   // trim from both ends
   std::string php::trim(std::string &s)
   {
      //return ltrim(rtrim(s));
      //return ltrim(rtrim(s));
      std::string s1 = s;
      std::string s2 = rtrim(s1);
      std::string s3 = ltrim(s2);
      return s3;
   }




   // next 4 functions are from
   // http://www.geekhideout.com/urlcode.shtml




   // Converts a hex character to its integer value
   char __from_hex(char ch) {
      return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
   }




   // Converts an integer value to its hex character
   char __to_hex(char code) {
      static char hex[] = "0123456789abcdef";
      return hex[code & 15];
   }




   // Returns a url-encoded version of str
   // IMPORTANT: be sure to free() the returned string after use
   char *php::url_encode(char *str) {
      char *pstr = str, *buf = (char *)malloc(strlen(str) * 3 + 1), *pbuf = buf;
      while (*pstr) {
         if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
            *pbuf++ = *pstr;
         else if (*pstr == ' ')
            *pbuf++ = '+';
         else
            *pbuf++ = '%', *pbuf++ = __from_hex(*pstr >> 4), *pbuf++ = __to_hex(*pstr & 15);
         pstr++;
      }
      *pbuf = '\0';
      return buf;
   }




   // Returns a url-decoded version of str //
   // IMPORTANT: be sure to free() the returned string after use //
   char *php::url_decode(char *str)
   {
      char *pstr = str, *buf = (char *)malloc(strlen(str) + 1), *pbuf = buf;
      while (*pstr) {
         if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
               *pbuf++ = __to_hex(pstr[1]) << 4 | __from_hex(pstr[2]);
               pstr += 2;
            }
         } else if (*pstr == '+') {
            *pbuf++ = ' ';
         } else {
            *pbuf++ = *pstr;
         }
         pstr++;
      }
      *pbuf = '\0';
      return buf;
   }




   std::string php::number_format(double number, int precision)
   {
      std::stringstream ss;
      ss << std::setprecision(precision) << number;
      return ss.str();
   }
}





