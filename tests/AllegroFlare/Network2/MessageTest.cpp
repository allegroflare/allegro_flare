
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Message.hpp>


TEST(AllegroFlare_Network2_MessageTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Message message;
}


TEST(AllegroFlare_Network2_MessageTest,
   data___has_the_expected_size_which_is_the_sum_of_HEADER_LENGTH_and_MAX_BODY_LENGTH)
{
   AllegroFlare::Network2::Message message;
   int expected_data_size = AllegroFlare::Network2::Message::get_HEADER_LENGTH()
                          + AllegroFlare::Network2::Message::get_MAX_BODY_LENGTH();
   EXPECT_EQ(expected_data_size, message.get_data().size());
}


