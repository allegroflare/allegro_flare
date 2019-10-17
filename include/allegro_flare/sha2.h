#ifndef __AF_SHA2_HEADER
#define __AF_SHA2_HEADER




// There is a copyright notice for this implementation contained in the .cpp file

#include <string>




namespace allegro_flare
{
   std::string get_sha224_hash(std::string input);
   std::string get_sha256_hash(std::string input);
   std::string get_sha384_hash(std::string input);
   std::string get_sha512_hash(std::string input);

   std::string get_sha224_hash_of_file(std::string filename);
   std::string get_sha256_hash_of_file(std::string filename);
   std::string get_sha384_hash_of_file(std::string filename);
   std::string get_sha512_hash_of_file(std::string filename);
}




#endif
