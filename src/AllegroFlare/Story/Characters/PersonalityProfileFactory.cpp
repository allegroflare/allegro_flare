

#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>

#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Story/Characters/PersonalityProfileMatrixFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfileFactory::PersonalityProfileFactory()
   : personality_profile_matrix()
   , initialized(false)
{
}


PersonalityProfileFactory::~PersonalityProfileFactory()
{
}


void PersonalityProfileFactory::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::initialize: error: guard \"(!initialized)\" not met");
   }
   personality_profile_matrix =
      AllegroFlare::Story::Characters::PersonalityProfileMatrixFactory::build_standard_matrix();

   initialized = true;

   return;
}

AllegroFlare::Story::Characters::PersonalityProfile PersonalityProfileFactory::build_random_personality_profile()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::build_random_personality_profile]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::build_random_personality_profile: error: guard \"initialized\" not met");
   }
   //static AllegroFlare::Random random;
   //int num_traits = 5;
   AllegroFlare::Story::Characters::PersonalityProfile profile;
   return profile;
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


