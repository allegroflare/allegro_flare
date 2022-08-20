
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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


TEST(AllegroFlare_Network2_MessageTest, body_length__has_the_expected_default_value)
{
   AllegroFlare::Network2::Message message;
   EXPECT_EQ(0, message.get_body_length());
}


TEST(AllegroFlare_Network2_MessageTest, set_body_length__will_set_the_body_length_to_the_value)
{
   AllegroFlare::Network2::Message message;

   message.set_body_length(256);
   EXPECT_EQ(256, message.get_body_length());

   message.set_body_length(1);
   EXPECT_EQ(1, message.get_body_length());

   message.set_body_length(AllegroFlare::Network2::Message::get_MAX_BODY_LENGTH());
   EXPECT_EQ(AllegroFlare::Network2::Message::get_MAX_BODY_LENGTH(), message.get_body_length());

   message.set_body_length(0);
   EXPECT_EQ(0, message.get_body_length());
}


TEST(AllegroFlare_Network2_MessageTest,
   set_body_length__will_raise_an_error_if_asked_to_set_the_length_larger_than_MAX_BODY_LENGTH)
{
   AllegroFlare::Network2::Message message;

   std::size_t size_too_big = AllegroFlare::Network2::Message::get_MAX_BODY_LENGTH() + 1;

   std::string expected_error_message = "Message::set_body_length: error: "
                                        "guard \"(!(new_length > MAX_BODY_LENGTH))\" not met";
   EXPECT_THROW_WITH_MESSAGE(message.set_body_length(size_too_big), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Network2_MessageTest,
   encode_header__will_set_the_header_to_the_proper_format)
{
   AllegroFlare::Network2::Message message;
   message.encode_header();
   std::string expected_data = "AFNM   0TODOTODO";
   EXPECT_EQ(expected_data, message.get_header());
}


