
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/Base.hpp>


class BaseTestClass : public AllegroFlare::MotionComposer::Messages::Base
{
public:
   BaseTestClass()
      : AllegroFlare::MotionComposer::Messages::Base("BaseTestClass")
   {}
};


TEST(AllegroFlare_MotionComposer_Messages_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::Base base;
}


TEST(AllegroFlare_MotionComposer_Messages_BaseTest, has_the_expected_type)
{
   AllegroFlare::MotionComposer::Messages::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(AllegroFlare_MotionComposer_Messages_BaseTest, derived_classes_will_have_the_expected_type)
{
   BaseTestClass test_class;
   EXPECT_EQ("BaseTestClass", test_class.get_type());
}


