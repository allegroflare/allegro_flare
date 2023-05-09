
#include <gtest/gtest.h>

#include <AllegroFlare/Bin.hpp>


class TestBin : public AllegroFlare::Bin<std::string, int *>
{
public:
   TestBin() : Bin("TestBin") {}

   virtual int *load_data(std::string identifier) override { return new int(54321); }
   virtual void destroy_data(int *data) override { delete data; }
   virtual bool validate() override { return true; }
};


class AllegroFlare_BinTest : public ::testing::Test {};



TEST_F(AllegroFlare_BinTest, derived_class_can_be_created_without_blowing_up)
{
   TestBin test_bin;
}


TEST_F(AllegroFlare_BinTest, destroy__will_remove_the_record)
{
   TestBin test_bin;
   test_bin.set_full_path("this/part/is/actually/not/necessary/and/should/eventually/be/removed");

   test_bin.preload("my_record_one");
   test_bin.preload("my_record_two");
   test_bin.preload("my_record_three");

   ASSERT_EQ(3, test_bin.size());

   test_bin.destroy("my_record_two");

   ASSERT_EQ(2, test_bin.size());

   test_bin.destroy("my_record_one");
   test_bin.destroy("my_record_three");

   EXPECT_EQ(0, test_bin.size());
}


TEST_F(AllegroFlare_BinTest,
   clear__when_cout_record_destruction_is_true__will_output_a_list_of_the_destroyed_records_flushing_to_cout_after_each)
{
   TestBin test_bin;
   test_bin.set_full_path("this/part/is/actually/not/necessary/and/should/eventually/be/removed");
   test_bin.set_cout_record_names_on_clear(true);

   test_bin.preload("data_record_one");
   test_bin.preload("data_record_two");
   test_bin.preload("data_record_three");

   testing::internal::CaptureStdout();
   test_bin.clear();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   std::string expected_stdout = "[TestBin::clear] Info: Destroying 3 records ("
                                 "\"data_record_one\", \"data_record_three\", \"data_record_two\", )\n";
   EXPECT_EQ(expected_stdout, actual_stdout);
}


TEST_F(AllegroFlare_BinTest,
   clear__when_cout_record_destruction_is_false__will_not_output_anything_to_cout)
{
   TestBin test_bin;
   test_bin.set_full_path("this/part/is/actually/not/necessary/and/should/eventually/be/removed");
   test_bin.preload("data_record_one");
   test_bin.preload("data_record_two");
   test_bin.preload("data_record_three");

   testing::internal::CaptureStdout();
   test_bin.clear();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, actual_stdout.empty());
}


TEST_F(AllegroFlare_BinTest, get_path__will_return_the_path)
{
   TestBin test_bin;
   test_bin.set_full_path("./foo/bar/baz/");
   std::string expected_path = "./foo/bar/baz/";
   EXPECT_EQ(expected_path, test_bin.get_path());
}


TEST_F(AllegroFlare_BinTest,
   set_full_path__when_setting_a_path_that_does_not_end_in_a_directory_separator__one_will_be_appended_automatically)
{
   TestBin test_bin;
   test_bin.set_full_path("./foo/bar/baz");
   std::string expected_path = "./foo/bar/baz/";
   EXPECT_EQ(expected_path, test_bin.get_path());
}


