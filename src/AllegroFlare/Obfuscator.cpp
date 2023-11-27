

#include <AllegroFlare/Obfuscator.hpp>

#include <AllegroFlare/Obfuscators/Rotate.hpp>
#include <set>


namespace AllegroFlare
{


Obfuscator::Obfuscator()
   : rotator_engine()
{
}


Obfuscator::~Obfuscator()
{
}


std::string Obfuscator::encode(std::string text)
{
   return rotator_engine.encode(text);
}

std::string Obfuscator::decode(std::string text)
{
   return rotator_engine.decode(text);
}


} // namespace AllegroFlare


