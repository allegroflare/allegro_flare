
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
}


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, load__will_not_blow_up)
{
   std::string yaml_string_content = "";
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   EXPECT_NE(nullptr, yaml_loader.load());
   // TODO: Free up the node recursively
}


