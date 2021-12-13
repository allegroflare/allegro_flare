

#include <AllegroFlare/AudioRepositoryElement.hpp>



namespace AllegroFlare
{


AudioRepositoryElement::AudioRepositoryElement(std::string filename, bool loop)
   : filename(filename)
   , loop(loop)
{
}


AudioRepositoryElement::~AudioRepositoryElement()
{
}


std::string AudioRepositoryElement::get_filename()
{
   return filename;
}


bool AudioRepositoryElement::get_loop()
{
   return loop;
}


} // namespace AllegroFlare


