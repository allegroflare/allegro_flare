#ifndef SHA2_H
#define SHA2_H



// There is a copyright notice for this implementation contained in the .cpp file

#include <string>


std::string get_sha224_hash(std::string input);
std::string get_sha256_hash(std::string input);
std::string get_sha384_hash(std::string input);
std::string get_sha512_hash(std::string input);

std::string get_sha256_hash_of_file(std::string filename);



#endif

