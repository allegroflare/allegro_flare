
#include <gtest/gtest.h>

#include <AllegroFlare/SHA2.hpp>


#define TEST_FILENAME "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/pun_dog.jpg"



#include <fstream>

TEST(AllegroFlare_SHA2Test, necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   ASSERT_EQ(true, (bool)ifile);
   ifile.close();
}



TEST(AllegroFlare_SHA2Test, can_be_created_without_blowing_up)
{
   AllegroFlare::SHA2 sha2;
}



TEST(AllegroFlare_SHA2Test, generate_sha224_hash__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string input = "grape";
   std::string expected_hash = "571f3896fb694dc268b032d7940dabbfbcd7ee64c07f45c01c9e64db";

   std::string hash = sha2.generate_sha224_hash(input);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha256_hash__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string input = "grape";
   std::string expected_hash = "0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496";

   std::string hash = sha2.generate_sha256_hash(input);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha384_hash__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string input = "grape";
   std::string expected_hash = "c2dafc387656342580027e2dbbbc2afcc77df4294b2542a983cf225735b888213" \
                          "02b9fa3c5948ba48b8dacd43da156d9";

   std::string hash = sha2.generate_sha384_hash(input);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha512_hash__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string input = "grape";
   std::string expected_hash = "9375d1abdb644a01955bccad12e2f5c2bd8a3e226187e548d99c559a99461453b" \
                          "980123746753d07c169c22a5d9cc75cb158f0e8d8c0e713559775b5e1391fc4";

   std::string hash = sha2.generate_sha512_hash(input);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha224_hash_from_file__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string expected_hash = "7444158c86c29b8819210568ce2f57c626300a41d8518a8e9768b812";
   std::string hash = sha2.generate_sha224_hash_from_file(TEST_FILENAME);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha256_hash_from_file__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string expected_hash = "73ea633f59d6d2c715361d1404f9abefb342c1acc1f871e887227bba9500191b";
   std::string hash = sha2.generate_sha256_hash_from_file(TEST_FILENAME);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha384_hash_from_file__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string expected_hash = "eb2d32a9284d63f3f614540a693de87bcba94d014e99f626a64772e307610b49" \
                               "8e3c796da839c8b453bbc5aa23a01148";
   std::string hash = sha2.generate_sha384_hash_from_file(TEST_FILENAME);

   EXPECT_EQ(expected_hash, hash);
}


TEST(AllegroFlare_SHA2Test, generate_sha512_hash_from_file__returns_the_expected_hash)
{
   AllegroFlare::SHA2 sha2;

   std::string expected_hash = "fb959abd4ddbc5a890b5837171bbcaaa2ef7ffd1601a97a528832a44995a9336" \
                               "1402b87223187eb462c986cbfd79e74f767abd8af8d46165dbe387f5e8115cdf";
   std::string hash = sha2.generate_sha512_hash_from_file(TEST_FILENAME);

   EXPECT_EQ(expected_hash, hash);
}


