
#include <gtest/gtest.h>

#include <AllegroFlare/MD5.hpp>


#define TEST_FILENAME "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/pun_dog.jpg"
#include <fstream>


TEST(AllegroFlare_MD5Test, DISABLED__can_be_created_without_blowing_up)
{
   // MD5 is a namespace, can not be tested
   //AllegroFlare::MD5 md5;
}


TEST(AllegroFlare_MD5Test, necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   ASSERT_EQ(true, (bool)ifile);
}


TEST(AllegroFlare_MD5Test, get_md5_has_from_file__produces_the_expected_hash)
{
   std::string expected = "f1c73dc3227a2a558cebb00716cb8fdc";
   EXPECT_EQ(expected, AllegroFlare::MD5::get_md5_hash_from_file(TEST_FILENAME));
}


TEST(AllegroFlare_MD5Test, md5_produces_correct_hash_from_file)
{
   std::string source_string = "This is the source string!";
   std::string expected = "d76c41b0b9df7f52fb6dab8607a3ad70";

   EXPECT_EQ(expected, AllegroFlare::MD5::get_md5_hash(source_string));
}



