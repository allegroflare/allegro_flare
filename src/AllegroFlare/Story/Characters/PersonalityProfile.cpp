

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>

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


PersonalityProfile::PersonalityProfile(std::string character_name, std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions)
   : character_name(character_name)
   , personality_dimensions(personality_dimensions)
{
}


PersonalityProfile::~PersonalityProfile()
{
}


void PersonalityProfile::set_character_name(std::string character_name)
{
   this->character_name = character_name;
}


void PersonalityProfile::set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions)
{
   this->personality_dimensions = personality_dimensions;
}


std::string PersonalityProfile::get_character_name() const
{
   return character_name;
}


std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> PersonalityProfile::get_personality_dimensions() const
{
   return personality_dimensions;
}


std::size_t PersonalityProfile::num_personality_dimensions()
{
   return personality_dimensions.size();
}

void PersonalityProfile::add_personality_dimension(AllegroFlare::Story::Characters::PersonalityProfileDimension personality_dimension)
{
   if (!((!personality_dimension_with_title_exists(personality_dimension.get_title()))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfile::add_personality_dimension]: error: guard \"(!personality_dimension_with_title_exists(personality_dimension.get_title()))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfile::add_personality_dimension]: error: guard \"(!personality_dimension_with_title_exists(personality_dimension.get_title()))\" not met");
   }
   // TODO: Add tests for this functionality
   personality_dimensions.push_back(personality_dimension);
   return;
}

bool PersonalityProfile::personality_dimension_with_title_exists(std::string title)
{
   // TODO: Add tests for this functionality
   for (auto &personality_dimension : personality_dimensions)
   {
      if (personality_dimension.get_title() == title) return true;
   }
   return false;
}

AllegroFlare::Story::Characters::PersonalityProfileDimension PersonalityProfile::get_personality_dimension_by_index(std::size_t index)
{
   if (!((index >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index >= 0)\" not met");
   }
   if (!((index < personality_dimensions.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index < personality_dimensions.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfile::get_personality_dimension_by_index]: error: guard \"(index < personality_dimensions.size())\" not met");
   }
   return personality_dimensions[index];
}

std::string PersonalityProfile::build_personality_dimensions_writeup()
{
   std::stringstream writeup;
   for (auto &dimension : personality_dimensions)
   {
      std::string dimension_name = dimension.get_title();
      std::string dimension_description = dimension.get_description();
      int dimension_ranking_size = dimension.get_scoring_max();
      int dimension_ranking_level = dimension.get_scoring();
      std::string dimension_descriptor_for_level = dimension.get_scoring_descriptor();

      writeup << build_writeup_for_dimension(
         character_name,
         dimension_name,
         dimension_description,
         dimension_ranking_level,
         dimension_descriptor_for_level
      );
      writeup << std::endl;
   }

   return writeup.str();
}

std::string PersonalityProfile::build_writeup_for_dimension(std::string character_name, std::string dimension_name, std::string dimension_description, uint32_t dimension_ranking_level, std::string dimension_descriptor_for_level)
{
   std::stringstream writeup;

   writeup << "In the personality category of \"" << dimension_name << "\" (" << dimension_description
           << "), " << character_name << " ranks " << ranking_level_to_text(dimension_ranking_level) << ", meaning "
           << character_name << " " << dimension_descriptor_for_level << ".";

   return writeup.str();
}

std::string PersonalityProfile::build_brief_personality_dimensions_writeup()
{
   std::stringstream writeup;
   std::vector<std::string> personality_descriptors;

   for (auto &dimension : personality_dimensions)
   {
      std::string dimension_descriptor_for_level = dimension.get_scoring_descriptor();
      personality_descriptors.push_back(dimension_descriptor_for_level);
   }

   std::string joined_descriptors = join_with_and(personality_descriptors, ", ");

   writeup << character_name << " " << joined_descriptors << ".";

   return writeup.str();
}

std::string PersonalityProfile::ranking_level_to_text(uint32_t ranking_level)
{
   if (!((ranking_level >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level >= 0)\" not met");
   }
   if (!((ranking_level < 5)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Story::Characters::PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Story::Characters::PersonalityProfile::ranking_level_to_text]: error: guard \"(ranking_level < 5)\" not met");
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

std::string PersonalityProfile::join(std::vector<std::string> tokens, std::string delimiter)
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i == tokens.size()-1) last = true;
      if (!last) result << delimiter;
   }

   return result.str();
}

std::string PersonalityProfile::join_with_and(std::vector<std::string> tokens, std::string delimiter, bool use_and)
{
   std::stringstream result;
   int size = tokens.size();

   for (int i = 0; i < size; ++i)
   {
      if (i > 0)
      {
         result << delimiter;
         if (use_and && i == size - 1)
         {
            result << "and ";
         }
      }
      result << tokens[i];
   }

   return result.str();
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


