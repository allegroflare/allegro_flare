
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   PrintTo__with_an_AllegroFlare_MotionComposer_Messages_AddActor2D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::MotionComposer::Messages::AddActor2D object("identifier", "script");

   PrintTo(object, &ss);

   std::string expected_output = "AddActor2D(\"identifier\", \"script\")";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   equality_operator__works_with_google_test_EXPECT_EQ_statement)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D object("identifier", "script");
   AllegroFlare::MotionComposer::Messages::AddActor2D other_object("identifier", "script");

   EXPECT_EQ(object, other_object);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   equality_operator__works_with_google_test_EXPECT_NE_statement)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D object("identifier", "script");
   AllegroFlare::MotionComposer::Messages::AddActor2D other_object("other-identifier", "script");

   EXPECT_NE(object, other_object);
}


