#pragma once


#include <string>


namespace AllegroFlare
{
   namespace MD5
   {
      // NOTE: copyright notice for the implementation code
      // is included in the .cpp file

      // converts a string to its corresponding md5 hash
      // assumes that char is 8 bit and int is 32 bit
      std::string generate_hash(const std::string string);

      // takes a file and returns the corresponding md5 hash of the file
      std::string generate_hash_from_file(std::string filename);
   };
}



