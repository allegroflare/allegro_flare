
#include <gtest/gtest.h>

#include <AllegroFlare/Obfuscators/Rotate.hpp>


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


TEST(AllegroFlare_Obfuscators_RotateTest, encode_and_decode_are_symmetrical)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   std::string initial_string = "Hello World!";
   EXPECT_EQ(initial_string, obfuscator.decode(obfuscator.encode(initial_string)));
}


TEST(AllegroFlare_Obfuscators_RotateTest, encode_and_decode_will_work_on_large_tests)
{
   AllegroFlare::Obfuscators::Rotate obfuscator;
   std::string subject;
   subject.resize(1024);
   for (auto &c : subject)
   {
      c = rand()%92 + 32;
   }
   EXPECT_EQ(subject, obfuscator.decode(obfuscator.encode(subject)));
}


