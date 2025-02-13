
#include <gtest/gtest.h>

#include <AllegroFlare/ClassAndMethodNameInference.hpp>


class ClassAndMethodNameInferenceTestClass
{
public:
   std::string this_class_name()
   {
      return THIS_CLASS_NAME;
   }
   std::string this_method_name()
   {
      return THIS_METHOD_NAME;
   }
   std::string this_class_and_method_name()
   {
      return THIS_CLASS_AND_METHOD_NAME;
   }
};


TEST(AllegroFlare_ClassAndMethodNameInferenceTest, THIS_CLASS_NAME__will_produce_the_class_name_in_which_it_is_called)
{
   std::string expected_class_name = "AllegroFlare_ClassAndMethodNameInferenceTest_THIS_CLASS_NAME__will_produce_the_"
                                     "class_name_in_which_it_is_called_Test";
   EXPECT_EQ(expected_class_name, THIS_CLASS_NAME);
}


TEST(AllegroFlare_ClassAndMethodNameInferenceTest,
   THIS_CLASS_NAME__when_inside_a_class__will_return_the_name_of_the_class)
{
   ClassAndMethodNameInferenceTestClass reflection_test_class;
   std::string expected_class_name = "ClassAndMethodNameInferenceTestClass";
   EXPECT_EQ(expected_class_name, reflection_test_class.this_class_name());
}


TEST(AllegroFlare_ClassAndMethodNameInferenceTest,
   THIS_METHOD_NAME__when_inside_a_class__will_return_the_name_of_the_method)
{
   ClassAndMethodNameInferenceTestClass reflection_test_class;
   std::string expected_method_name = "this_method_name";
   EXPECT_EQ(expected_method_name, reflection_test_class.this_method_name());
}


TEST(AllegroFlare_ClassAndMethodNameInferenceTest,
   THIS_CLASS_AND_METHOD_NAME__when_inside_a_class__will_return_the_name_of_the_class_and_method)
{
   ClassAndMethodNameInferenceTestClass reflection_test_class;
   std::string expected_method_name = "ClassAndMethodNameInferenceTestClass::this_class_and_method_name";
   EXPECT_EQ(expected_method_name, reflection_test_class.this_class_and_method_name());
}


