

#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>

#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>
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
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::initialize]: error: guard \"(!initialized)\" not met");
   }
   personality_profile_matrix =
      AllegroFlare::Story::Characters::PersonalityProfileMatrixFactory::build_standard_matrix();

   initialized = true;

   return;
}

AllegroFlare::Story::Characters::PersonalityProfile PersonalityProfileFactory::build_random_personality_profile(std::string character_name, std::size_t num_traits, unsigned int seed)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"initialized\" not met");
   }
   if (!((num_traits > 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"(num_traits > 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"(num_traits > 1)\" not met");
   }
   if (!((num_traits <= personality_profile_matrix.num_dimensions())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"(num_traits <= personality_profile_matrix.num_dimensions())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_random_personality_profile]: error: guard \"(num_traits <= personality_profile_matrix.num_dimensions())\" not met");
   }
   // Select the random seed mechanism we'll use (typically either knowable or unpredictable)
   static AllegroFlare::Random static_random; // NOTE: if seed is 0, then an unpredictable random will be used
   AllegroFlare::Random seeded_random(seed);  // NOTE: if seed is non-zero, then a freshly seeded randomizer is used
   AllegroFlare::Random &random = (seed == 0) ? static_random : seeded_random;

   // Capture the available dimensions
   std::vector<AllegroFlare::Story::Characters::PersonalityDimension> available_personality_dimensions =
      personality_profile_matrix.get_dimensions();
   random.shuffle_elements(available_personality_dimensions);

   // Cap the available traits to the "num_traits" that were asked for
   if (available_personality_dimensions.size() > num_traits) available_personality_dimensions.resize(num_traits);

   // Create our profile
   AllegroFlare::Story::Characters::PersonalityProfile result_profile;
   result_profile.set_character_name(character_name);

   // Assemble our writeup text
   std::stringstream writeup;
   for (auto &dimension : available_personality_dimensions)
   {
      std::string dimension_name = dimension.get_name();
      std::string dimension_description = dimension.get_description();
      int dimension_ranking_size = 5;
      int dimension_ranking_level = random.get_random_int(0, dimension_ranking_size-1);
      std::string dimension_descriptor_for_level = dimension.get_descriptor_for_level(dimension_ranking_level);

      result_profile.add_personality_dimension(
            AllegroFlare::Story::Characters::PersonalityProfileDimension(
               dimension_name,
               dimension_description,
               dimension_ranking_level,
               (dimension_ranking_size-1),
               dimension_descriptor_for_level 
            )
         );
   }

   return result_profile; //.build_personality_dimensions_writeup();

   //return writeup.str();
}

std::string PersonalityProfileFactory::build_writeup_for_dimension(std::string character_name, std::string dimension_name, std::string dimension_description, uint32_t dimension_ranking_level, std::string dimension_descriptor_for_level)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_writeup_for_dimension]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::build_writeup_for_dimension]: error: guard \"initialized\" not met");
   }
   std::stringstream writeup;

   writeup << "In the personality category of \"" << dimension_name << "\" (" << dimension_description
           << "), " << character_name << " ranks " << ranking_level_to_text(dimension_ranking_level) << ", meaning "
           << character_name << " " << dimension_descriptor_for_level << ".";

   return writeup.str();
}

std::string PersonalityProfileFactory::ranking_level_to_text(uint32_t ranking_level)
{
   if (!((ranking_level >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met");
   }
   if (!((ranking_level < 5)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfileFactory::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met");
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


