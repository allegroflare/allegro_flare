
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>


class MyTestDialogBox : public AllegroFlare::Elements::DialogBoxes::Base
{
public:
   MyTestDialogBox() : AllegroFlare::Elements::DialogBoxes::Base("MyTestDialogBox") {}
};


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, type__when_not_from_a_derived_class__is_the_expected_default)
{
   std::string expected_type = "Base";
   AllegroFlare::Elements::DialogBoxes::Base base_dialog_box;
   ASSERT_EQ(expected_type, base_dialog_box.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Base base;
}


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, type__is_set_when_the_derived_class_injects_it_through_the_constructor)
{
   std::string expected_type = "MyTestDialogBox";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(expected_type, dialog_box.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, is_type__returns_true_if_the_type_matches_the_current_type)
{
   std::string the_type_that_it_is = "MyTestDialogBox";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(true, dialog_box.is_type(the_type_that_it_is));
}


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, is_type__returns_false_if_the_type_does_not_matches_the_current_type)
{
   std::string some_type_that_it_is_not = "SomeTypeThatItIsNot";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(false, dialog_box.is_type(some_type_that_it_is_not));
}


