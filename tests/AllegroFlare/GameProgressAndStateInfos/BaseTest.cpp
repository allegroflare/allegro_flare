
#include <gtest/gtest.h>

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>
#include <AllegroFlare/UsefulPHP.hpp>


class GameProgressAndStateInfosBaseTestClass : public AllegroFlare::GameProgressAndStateInfos::Base
{
public:
   std::vector<std::string> items;

   GameProgressAndStateInfosBaseTestClass()
      : AllegroFlare::GameProgressAndStateInfos::Base("GameProgressAndStateInfosBaseTestClass")
      , items()
   {}
   virtual std::string export_to_string() override
   {
      return AllegroFlare::StringTransformer::join(&items, ",");
   }
   virtual void import_from_string(std::string input) override
   {
      items.clear();
      items = AllegroFlare::StringTransformer::tokenize(input, ',');
   }
};


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameProgressAndStateInfos::Base base;
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameProgressAndStateInfos/Base",
     AllegroFlare::GameProgressAndStateInfos::Base::TYPE
   );
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameProgressAndStateInfos::Base base;
   EXPECT_EQ(AllegroFlare::GameProgressAndStateInfos::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, derived_classes_will_have_the_expected_type)
{
   GameProgressAndStateInfosBaseTestClass test_class;
   EXPECT_EQ("GameProgressAndStateInfosBaseTestClass", test_class.get_type());
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, save__will_save_the_contents_to_the_file)
{
   AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator;
   std::string created_directory = temporary_directory_creator.create().string();
   std::string save_file_filename = created_directory + "/" + "my_output_save_file.txt";

   GameProgressAndStateInfosBaseTestClass test_class;
   test_class.set_save_file_filename(save_file_filename);

   // Set the items in our test class
   test_class.items = { "ring", "diamond", "diamond", "knife", "coin" };

   EXPECT_EQ(false, std::filesystem::exists(save_file_filename));
   test_class.save();
   EXPECT_EQ(true, std::filesystem::exists(save_file_filename));

   // Check the contents of the file
   std::string expected_file_content = "ring,diamond,diamond,knife,coin";
   std::string actual_save_file_content = AllegroFlare::php::file_get_contents(save_file_filename);
   EXPECT_EQ(expected_file_content, actual_save_file_content);
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest,
   load__will_call_import_to_string_with_the_file_contents_for_loading)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string save_file_filename = 
      deployment_environment.get_data_folder_path() +
      "saves/test_save_file-01.txt";

   // Validate the test file has the expected data (it has accidentally been overwritten in the past)
   std::string expected_file_content = "apple, apple, cherry, orange\n";
   std::string actual_save_file_content = AllegroFlare::php::file_get_contents(save_file_filename);
   ASSERT_EQ(expected_file_content, actual_save_file_content);

   GameProgressAndStateInfosBaseTestClass test_class;
   test_class.set_save_file_filename(save_file_filename);

   test_class.load();

   std::vector<std::string> expected_items = { "apple", "apple", "cherry", "orange" };
   std::vector<std::string> actual_items = test_class.items;
   EXPECT_EQ(expected_items, actual_items);
}


