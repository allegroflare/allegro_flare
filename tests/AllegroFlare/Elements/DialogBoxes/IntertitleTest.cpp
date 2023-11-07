
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Intertitle.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Intertitle intertitle;
}


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/Intertitle",
     AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::Intertitle intertitle;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE, intertitle.get_type());
}


// TODO: Add tests


