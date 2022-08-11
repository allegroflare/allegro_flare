
#include <gtest/gtest.h>

#include <AllegroFlare/MD5.hpp>


#ifdef _WIN32
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#define TEST_FILENAME (TEST_FIXTURE_BITMAP_FOLDER "pun_dog.jpg")

#include <fstream>


TEST(AllegroFlare_MD5Test, can_be_created_without_blowing_up)
{
   AllegroFlare::MD5 md5;
}


TEST(AllegroFlare_MD5Test, necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   ASSERT_EQ(true, (bool)ifile);
}


TEST(AllegroFlare_MD5Test, generate_hash__produces_correct_hash)
{
   std::string source_string = "This is the source string!";
   std::string expected = "d76c41b0b9df7f52fb6dab8607a3ad70";

   EXPECT_EQ(expected, AllegroFlare::MD5::generate_hash(source_string));
}


TEST(AllegroFlare_MD5Test, generate_hash_from_file__produces_the_expected_hash)
{
   std::string expected = "f1c73dc3227a2a558cebb00716cb8fdc";
   EXPECT_EQ(expected, AllegroFlare::MD5::generate_hash_from_file(TEST_FILENAME));
}


