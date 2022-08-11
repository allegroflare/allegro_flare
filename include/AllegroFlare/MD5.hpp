#pragma once


#include <string>


namespace AllegroFlare
{
   class MD5
   {
   public:
      MD5();
      ~MD5();

      // NOTE: copyright notice for the implementation code
      // is included in the .cpp file

      // converts a string to its corresponding md5 hash
      // assumes that char is 8 bit and int is 32 bit
      static std::string generate_hash(const std::string string);

      // takes a file and returns the corresponding md5 hash of the file
      static std::string generate_hash_from_file(std::string filename);
   };
}



