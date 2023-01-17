

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MD5
#include <boost/test/unit_test.hpp>




#include <allegro_flare/md5.h>

#include <fstream>




using namespace allegro_flare;




#define TEST_FILENAME "data/bitmaps/pun_dog.jpg"




BOOST_AUTO_TEST_CASE(necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   BOOST_CHECK_EQUAL(true, (bool)ifile);
}




BOOST_AUTO_TEST_CASE(md5_produces_correct_hash_from_file)
{
   std::string expected = "f1c73dc3227a2a558cebb00716cb8fdc";
   BOOST_CHECK_EQUAL(expected, get_md5_hash_from_file(TEST_FILENAME));
}




