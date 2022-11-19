
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>

#include <allegro5/allegro.h>


#include <chrono> // for std::chrono
#include <thread> // for std::this_thread::sleep_for

static void sleep_for(float length_in_seconds)
{
   int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
   std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
}


class MyTestDialogBox : public AllegroFlare::Elements::DialogBoxes::Base
{
public:
   MyTestDialogBox() : AllegroFlare::Elements::DialogBoxes::Base("MyTestDialogBox") {}
};


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, type__when_not_from_a_derived_class__is_the_expected_default)
{
   std::string expected_type = "DialogBoxes/Base";
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


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, infer_age__without_allegro_initialized__will_raise_an_error)
{
   MyTestDialogBox dialog_box;
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BaseTest, infer_age__will_return_the_age_of_the_dialog_box_in_seconds)
{
   al_init();
   MyTestDialogBox dialog_box;
   dialog_box.set_created_at(al_get_time());
   sleep_for(0.03);
   float inferred_age = dialog_box.infer_age();
   EXPECT_THAT(inferred_age, testing::Gt(0.02));
   EXPECT_THAT(inferred_age, testing::Lt(0.04));
   al_uninstall_system();
}


