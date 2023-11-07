
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/TextMessages.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_TextMessagesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::TextMessages text_messages;
}


TEST(AllegroFlare_Elements_DialogBoxes_TextMessagesTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/TextMessages",
     AllegroFlare::Elements::DialogBoxes::TextMessages::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_TextMessagesTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::TextMessages text_messages;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::TextMessages::TYPE, text_messages.get_type());
}


