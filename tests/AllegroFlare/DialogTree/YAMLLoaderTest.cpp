
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
}


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, run__returns_the_expected_response)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, yamlloader.run());
}


