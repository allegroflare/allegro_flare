

#include <gtest/gtest.h>

#include <AllegroFlare/UsefulPHP.hpp>


#ifdef _WIN32
#define TEST_FIXTURE_FILENAME "/msys64/home/Mark/Repos/allegro_flare/tests/test_fixtures/php_file_get_contents.txt"
#else
#define TEST_FIXTURE_FILENAME "/Users/markoates/Repos/allegro_flare/tests/test_fixtures/php_file_get_contents.txt"
#endif


TEST(UsefulTest,
   php_file_get_contents_split__with_vector_string_return_value__returns_the_contents_of_the_file_split_into_lines)
{
   std::string filename = TEST_FIXTURE_FILENAME;
   std::vector<std::string> expected_lines = {
      "These are the lines",
      "that are expected to come out of this file.",
      "Note that there are 4 lines,",
      "and this is the last line.",
   };

   std::vector<std::string> lines = AllegroFlare::php::file_get_contents_split(filename);

   ASSERT_EQ(expected_lines, lines);
}


