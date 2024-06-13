
#include <gtest/gtest.h>

#include <AllegroFlare/Generators/PersonNameGenerator.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Logger.hpp>


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_boy_name__without_initialization__will_throw_an_error)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::Generators::PersonNameGenerator::generate_boy_name",
      "initialized"
   );
   EXPECT_THROW_WITH_MESSAGE(person_name_generator.generate_boy_name(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_girl_name__without_initialization__will_throw_an_error)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::Generators::PersonNameGenerator::generate_girl_name",
      "initialized"
   );
   EXPECT_THROW_WITH_MESSAGE(person_name_generator.generate_girl_name(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, initialize__will_not_blow_up)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   person_name_generator.initialize();
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_boy_name__will_return_a_random_boy_name)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   person_name_generator.initialize();
   person_name_generator.randomize(927492);
   EXPECT_EQ("Bruce", person_name_generator.generate_boy_name());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_girl_name__will_return_a_random_boy_name)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   person_name_generator.initialize();
   person_name_generator.randomize(927492);
   EXPECT_EQ("Penelope", person_name_generator.generate_girl_name());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, the_source_of_victorian_boy_names_contains_40_names)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   EXPECT_EQ(40, person_name_generator.build_victorian_boy_name_list().size());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, the_source_of_victorian_girl_names_contains_40_names)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   EXPECT_EQ(40, person_name_generator.build_victorian_girl_name_list().size());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest,
   the_source_of_double_consecutive_t_names_contains_37_names)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   // TODO: Make this list 40 names long
   EXPECT_EQ(37, person_name_generator.build_double_consecutive_t_name_list().size());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, the_source_of_victorian_boy_names_contains_unique_elements)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::vector<std::string> provided_source_names = person_name_generator.build_victorian_boy_name_list();
   std::set<std::string> unique_names;
   for (auto &element : provided_source_names) unique_names.insert(element);
   
   EXPECT_EQ(unique_names.size(), provided_source_names.size());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, the_source_of_victorian_girl_names_contains_unique_elements)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::vector<std::string> provided_source_names = person_name_generator.build_victorian_girl_name_list();
   std::set<std::string> unique_names;
   for (auto &element : provided_source_names) unique_names.insert(element);
   
   EXPECT_EQ(unique_names.size(), provided_source_names.size());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest,
   the_source_of_double_consecutive_t_names_contains_unique_elements)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::vector<std::string> provided_source_names = person_name_generator.build_double_consecutive_t_name_list();
   std::set<std::string> unique_names;
   for (auto &element : provided_source_names) unique_names.insert(element);
   
   EXPECT_EQ(unique_names.size(), provided_source_names.size());
}


