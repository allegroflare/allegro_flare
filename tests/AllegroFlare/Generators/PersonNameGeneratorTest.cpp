
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define ERROR_MESSAGE_FOR(klass, method, guard) klass ## "::" ## method ## ": error \"" ## guard ## "\" not met"


#include <AllegroFlare/Generators/PersonNameGenerator.hpp>


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_boy_name__without_initialization__will_throw_an_error)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::string expected_error_message =
      "PersonNameGenerator::generate_boy_name: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(person_name_generator.generate_boy_name(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_girl_name__without_initialization__will_throw_an_error)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   std::string expected_error_message =
      "PersonNameGenerator::generate_girl_name: error: guard \"initialized\" not met";
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
   person_name_generator.set_seed_and_randomize(927492);
   EXPECT_EQ("Thomas", person_name_generator.generate_boy_name());
}


TEST(AllegroFlare_Generators_PersonNameGeneratorTest, generate_girl_name__will_return_a_random_boy_name)
{
   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   person_name_generator.initialize();
   person_name_generator.set_seed_and_randomize(927492);
   EXPECT_EQ("Stacy", person_name_generator.generate_girl_name());
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


