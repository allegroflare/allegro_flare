

#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>

#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Story/Characters/PersonalityProfileMatrixFactory.hpp>
#include <iostream>
#include <map>
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

std::string PersonalityProfileFactory::build_random_personality_profile(std::string character_name, uint32_t num_traits, unsigned int seed)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::build_random_personality_profile]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::build_random_personality_profile: error: guard \"initialized\" not met");
   }
   static AllegroFlare::Random static_random; // NOTE: if seed is 0, then the static_random will be used
   AllegroFlare::Random seeded_random(seed);  // NOTE: if seed is non-zero, then a fresh Random will use the seed

   AllegroFlare::Random &random = (seed == 0) ? static_random : seeded_random;

   // Assemble a dimension.
   AllegroFlare::Story::Characters::PersonalityDimension selected_dimension =
      personality_profile_matrix.get_personality_dimension_by_index(1); // TODO: Select this randomly

   std::string dimension_name = selected_dimension.get_name();
   std::string dimension_description = selected_dimension.get_description();
   uint32_t dimension_ranking_level = 4; // TODO: Select this randomly
   std::string dimension_descriptor_for_level = selected_dimension.get_descriptor_for_level(dimension_ranking_level);

   std::stringstream writeup;
   writeup << build_writeup_for_dimension(
      character_name,
      dimension_name,
      dimension_description,
      dimension_ranking_level,
      dimension_descriptor_for_level
   );

   //AllegroFlare::Story::Characters::PersonalityProfile profile;
   //return profile;
   return writeup.str();
}

std::string PersonalityProfileFactory::build_writeup_for_dimension(std::string character_name, std::string dimension_name, std::string dimension_description, uint32_t dimension_ranking_level, std::string dimension_descriptor_for_level)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::build_writeup_for_dimension]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::build_writeup_for_dimension: error: guard \"initialized\" not met");
   }
   std::stringstream writeup;

   writeup << "In the personality category of \"" << dimension_name << "\" (" << dimension_description
           << "), " << character_name << " ranks " << ranking_level_to_text(dimension_ranking_level) << ", meaning "
           << character_name << " is " << dimension_descriptor_for_level << ".";

   return writeup.str();
}

std::string PersonalityProfileFactory::ranking_level_to_text(uint32_t ranking_level)
{
   if (!((ranking_level >= 0)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::ranking_level_to_text: error: guard \"(ranking_level >= 0)\" not met");
   }
   if (!((ranking_level < 5)))
   {
      std::stringstream error_message;
      error_message << "[PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonalityProfileFactory::ranking_level_to_text: error: guard \"(ranking_level < 5)\" not met");
   }
   std::map<uint32_t, std::string> dictionary = {
      { 0, "VERY_LOW" },
      { 1, "LOW" },
      { 2, "BALANCED" },
      { 3, "HIGH" },
      { 4, "VERY_HIGH" },
   };
   return dictionary[ranking_level];
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


