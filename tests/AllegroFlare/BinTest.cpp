#include <gtest/gtest.h>

#include <AllegroFlare/Bin.hpp>

class TestBin : public AllegroFlare::Bin<std::string, int *>
{
public:
   TestBin() : Bin("TestBin") {}

   virtual int *load_data(std::string identifier) override { return new int(3); }
   virtual void destroy_data(int *data) override { delete data; }
   virtual bool validate() override { return true; }
};

TEST(AllegroFlare_BinTest, derived_class_can_be_created_without_blowing_up)
{
   TestBin test_bin;
}

TEST(AllegroFlare_BinTest, clear__will_output_a_list_of_the_destroyed_records_flushing_cout_as_each_are_deleted)
{
   TestBin test_bin;
   test_bin.set_full_path("this/part/is/actually/not/necessary/and/should/eventually/be/removed");
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
