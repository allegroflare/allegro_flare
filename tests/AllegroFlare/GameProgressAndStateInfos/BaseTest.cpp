
#include <gtest/gtest.h>

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/TemporaryFilenameCreator.hpp>


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
      std::cout << "INPUT: " << input << std::endl;
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
   GTEST_SKIP();
  //- name: create_filename_within_guaranteed_unique_directory
    //type: std::string
    //body: |
      //AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator;
      //std::string unique_directory = temporary_directory_creator.create().string();
      //std::string unique_filename = std::filesystem::path(std::tmpnam(nullptr)).filename().string();
      //return unique_directory + "/" + unique_filename;
    //body_dependency_symbols:
   //AllegroFlare::Testing::TemporaryFilenameCreator creator;
   //std::string save_file_filename = creator.create_filename_within_guaranteed_unique_directory();
   //std::filesystem::create_directory
      //AllegroFlare::Testing::TemporaryFilenameCreator::create_filename_within_guaranteed_unique_directory();

   //AllegroFlare::Testing::TemporarytoryCreator temporary_directory_creator;
   //std::string directory = temporary_directory_creator.create();
   //AllegroFlare::DeploymentEnvironment deployment_environment("test");
   //std::string save_file_filename = 
      //deployment_environment.get_data_folder_path() +
      //"saves/test_save_file-01.txt";

   //GameProgressAndStateInfosBaseTestClass test_class;
   //test_class.set_save_file_filename(save_file_filename);

   //test_class.save();
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest,
   load__will_call_import_to_string_with_the_file_contents_for_loading)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string save_file_filename = 
      deployment_environment.get_data_folder_path() +
      "saves/test_save_file-01.txt";

   GameProgressAndStateInfosBaseTestClass test_class;
   test_class.set_save_file_filename(save_file_filename);

   test_class.load();

   EXPECT_EQ(4, test_class.items.size());
}


