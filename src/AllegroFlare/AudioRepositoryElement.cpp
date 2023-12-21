

#include <AllegroFlare/AudioRepositoryElement.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


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


void AudioRepositoryElement::set_overplay_strategy(std::string overplay_strategy)
{
   if (!(is_valid_overplay_strategy(overplay_strategy)))
   {
      std::stringstream error_message;
      error_message << "[AudioRepositoryElement::set_overplay_strategy]: error: guard \"is_valid_overplay_strategy(overplay_strategy)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioRepositoryElement::set_overplay_strategy: error: guard \"is_valid_overplay_strategy(overplay_strategy)\" not met");
   }
   this->overplay_strategy = overplay_strategy;
   return;
}

bool AudioRepositoryElement::is_valid_overplay_strategy(std::string possibly_valid_overplay_strategy)
{
   // TODO: Test this
   std::set<std::string> valid_overplay_strategies = {
      OVERPLAY_STRATEGY_IGNORE,
      OVERPLAY_STRATEGY_RESTART,
   };

   return valid_overplay_strategies.find(possibly_valid_overplay_strategy) != valid_overplay_strategies.end();
}

bool AudioRepositoryElement::overplay_strategy_is_ignore()
{
   return overplay_strategy == OVERPLAY_STRATEGY_IGNORE;
}

bool AudioRepositoryElement::overplay_strategy_is_restart()
{
   return overplay_strategy == OVERPLAY_STRATEGY_RESTART;
}


} // namespace AllegroFlare


