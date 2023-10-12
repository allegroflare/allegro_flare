
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>


TEST(AllegroFlare_Testing_TemporaryDirectoryCreatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator;
}


TEST(AllegroFlare_Testing_TemporaryDirectoryCreatorTest, create__on_successive_instances__will_produce_unique_results)
{
   AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator1;
   AllegroFlare::Testing::TemporaryDirectoryCreator temporary_directory_creator2;

   std::string created_directory_1 = temporary_directory_creator1.create().string();
   std::string created_directory_2 = temporary_directory_creator2.create().string();

   EXPECT_NE(created_directory_1, created_directory_2);
}


