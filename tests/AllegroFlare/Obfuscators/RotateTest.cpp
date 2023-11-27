
#include <gtest/gtest.h>

#include <AllegroFlare/Obfuscators/Rotate.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_Obfuscators_RotateTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Obfuscators::Rotate rotate;
}


TEST(AllegroFlare_Obfuscators_RotateTest, run__returns_the_expected_response)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   std::string initial_string = "Hello World!";
   std::string expected_string = "Lippsa[svph%";
   EXPECT_EQ(expected_string, obfuscator.encode(initial_string));
}


TEST(AllegroFlare_Obfuscators_RotateTest, encode__when_the_rotation_set_contains_duplicate_character__throws_an_error)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   obfuscator.set_rotation_set("aa");
   EXPECT_THROW_WITH_MESSAGE(
      obfuscator.encode("some irrelevant text"),
      std::runtime_error,
      "Rotate::encode: error: guard \"rotation_set_contains_unique_characters()\" not met"
   );
}


TEST(AllegroFlare_Obfuscators_RotateTest, decode__when_the_rotation_set_contains_duplicate_character__throws_an_error)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   obfuscator.set_rotation_set("aa");
   EXPECT_THROW_WITH_MESSAGE(
      obfuscator.decode("some irrelevant text"),
      std::runtime_error,
      "Rotate::decode: error: guard \"rotation_set_contains_unique_characters()\" not met"
   );
}


TEST(AllegroFlare_Obfuscators_RotateTest, encode_and_decode_are_symmetrical)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   std::string initial_string = "Hello World!";
   EXPECT_EQ(initial_string, obfuscator.decode(obfuscator.encode(initial_string)));
}


TEST(AllegroFlare_Obfuscators_RotateTest, encode_and_decode_will_work_on_large_texts)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   std::string subject;
   // TODO: Use a seed for the random() so not to have a flakey test
   // Alternatively, rely on a random seed for each test, and feed the seed value of the EXPECT_EQ in case of failure
   subject.resize(14000); // Approximately 10 pages of text
   for (auto &c : subject)
   {
      c = rand()%256;
   }
   EXPECT_EQ(subject, obfuscator.decode(obfuscator.encode(subject)));
}


