#pragma once


#include <string>


namespace AllegroFlare
{
   class SHA2
   {
   public:
      SHA2();
      ~SHA2();

      std::string generate_sha224_hash(std::string input="");
      std::string generate_sha256_hash(std::string input="");
      std::string generate_sha384_hash(std::string input="");
      std::string generate_sha512_hash(std::string input="");

      std::string generate_sha224_hash_from_file(std::string filename="[filename-not-set]");
      std::string generate_sha256_hash_from_file(std::string filename="[filename-not-set]");
      std::string generate_sha384_hash_from_file(std::string filename="[filename-not-set]");
      std::string generate_sha512_hash_from_file(std::string filename="[filename-not-set]");
   };
}


