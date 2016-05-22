

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SHA2
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <allegro_flare/sha2.h>


#define TEST_FILENAME "data/bitmaps/pun_dog.jpg"


BOOST_AUTO_TEST_CASE(necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   BOOST_CHECK_EQUAL(true, (bool)ifile);
}

BOOST_AUTO_TEST_CASE(sha224_produces_correct_hash_from_file)
{
   std::string expected = "7444158c86c29b8819210568ce2f57c626300a41d8518a8e9768b812";
   BOOST_CHECK_EQUAL(expected, get_sha224_hash_of_file(TEST_FILENAME));
}

BOOST_AUTO_TEST_CASE(sha256_produces_correct_hash_from_file)
{
   std::string expected = "73ea633f59d6d2c715361d1404f9abefb342c1acc1f871e887227bba9500191b";
   BOOST_CHECK_EQUAL(expected, get_sha256_hash_of_file(TEST_FILENAME));
}

BOOST_AUTO_TEST_CASE(sha384_produces_correct_hash_from_file)
{
   std::string expected = "eb2d32a9284d63f3f614540a693de87bcba94d014e99f626a64772e307610b498e3c796da839c8b453bbc5aa23a01148";
   BOOST_CHECK_EQUAL(expected, get_sha384_hash_of_file(TEST_FILENAME));
}

BOOST_AUTO_TEST_CASE(sha512_produces_correct_hash_from_file)
{
   std::string expected = "fb959abd4ddbc5a890b5837171bbcaaa2ef7ffd1601a97a528832a44995a93361402b87223187eb462c986cbfd79e74f767abd8af8d46165dbe387f5e8115cdf";
   BOOST_CHECK_EQUAL(expected, get_sha512_hash_of_file(TEST_FILENAME));
}


