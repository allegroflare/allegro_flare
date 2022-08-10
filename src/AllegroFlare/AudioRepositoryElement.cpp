

#include <AllegroFlare/AudioRepositoryElement.hpp>



namespace AllegroFlare
{


AudioRepositoryElement::AudioRepositoryElement(std::string filename, bool loop, std::string overplay_strategy)
   : filename(filename)
   , loop(loop)
   , overplay_strategy(overplay_strategy)
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


std::string AudioRepositoryElement::get_overplay_strategy()
{
   return overplay_strategy;
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


