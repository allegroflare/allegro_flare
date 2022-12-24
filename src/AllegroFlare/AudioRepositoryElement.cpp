

#include <AllegroFlare/AudioRepositoryElement.hpp>




namespace AllegroFlare
{


AudioRepositoryElement::AudioRepositoryElement(std::string filename, bool loop, std::string overplay_strategy, float volume)
   : filename(filename)
   , loop(loop)
   , overplay_strategy(overplay_strategy)
   , volume(volume)
{
}


AudioRepositoryElement::~AudioRepositoryElement()
{
}


std::string AudioRepositoryElement::get_filename() const
{
   return filename;
}


bool AudioRepositoryElement::get_loop() const
{
   return loop;
}


std::string AudioRepositoryElement::get_overplay_strategy() const
{
   return overplay_strategy;
}


float AudioRepositoryElement::get_volume() const
{
   return volume;
}


bool AudioRepositoryElement::overplay_strategy_is_ignore()
{
   return overplay_strategy == "ignore";
}

bool AudioRepositoryElement::overplay_strategy_is_restart()
{
   return overplay_strategy == "restart";
}


} // namespace AllegroFlare


