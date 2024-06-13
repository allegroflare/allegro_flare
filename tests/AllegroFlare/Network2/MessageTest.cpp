
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Network2/Message.hpp>


TEST(AllegroFlare_Network2_MessageTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Message message;
}


TEST(AllegroFlare_Network2_MessageTest, MAGIC_HEADER_CHUNK___has_the_expected_value_of_AFNM)
{
   AllegroFlare::Network2::Message message;
   EXPECT_EQ("AFNM", AllegroFlare::Network2::Message::MAGIC_HEADER_CHUNK);
}


TEST(AllegroFlare_Network2_MessageTest,
   data___has_the_expected_size_which_is_the_sum_of_HEADER_LENGTH_and_MAX_BODY_LENGTH)
{
   AllegroFlare::Network2::Message message;
   std::size_t expected_data_size = AllegroFlare::Network2::Message::HEADER_LENGTH
                                  + AllegroFlare::Network2::Message::MAX_BODY_LENGTH;
   EXPECT_EQ(expected_data_size, message.get_data().size());
}


TEST(AllegroFlare_Network2_MessageTest, body_length__has_the_expected_default_value)
{
   AllegroFlare::Network2::Message message;
   EXPECT_EQ(0UL, message.get_body_length());
}


TEST(AllegroFlare_Network2_MessageTest, set_body_length__will_set_the_body_length_to_the_value)
{
   AllegroFlare::Network2::Message message;

   message.set_body_length(256);
   EXPECT_EQ(256UL, message.get_body_length());

   message.set_body_length(1);
   EXPECT_EQ(1UL, message.get_body_length());

   message.set_body_length(AllegroFlare::Network2::Message::MAX_BODY_LENGTH);
   EXPECT_EQ(AllegroFlare::Network2::Message::MAX_BODY_LENGTH, message.get_body_length());

   message.set_body_length(0);
   EXPECT_EQ(0UL, message.get_body_length());
}


TEST(AllegroFlare_Network2_MessageTest,
   set_body_length__will_raise_an_error_if_asked_to_set_the_length_larger_than_MAX_BODY_LENGTH)
{
   AllegroFlare::Network2::Message message;

   std::size_t size_too_big = AllegroFlare::Network2::Message::MAX_BODY_LENGTH + 1;

   std::string expected_error_message = "[AllegroFlare::Network2::Message::set_body_length]: error: "
                                        "guard \"(!(new_length > MAX_BODY_LENGTH))\" not met";
   EXPECT_THROW_WITH_MESSAGE(message.set_body_length(size_too_big), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Network2_MessageTest,
   set_body__will_raise_an_error_if_asked_to_set_the_content_to_a_length_larger_than_MAX_BODY_LENGTH)
{
   AllegroFlare::Network2::Message message;

   std::size_t size_too_big = AllegroFlare::Network2::Message::MAX_BODY_LENGTH + 1;
   std::string content_too_big(size_too_big, 'x');

   std::string expected_error_message = "[AllegroFlare::Network2::Message::set_body]: error: "
                                        "guard \"(!(content.size() > MAX_BODY_LENGTH))\" not met";
   EXPECT_THROW_WITH_MESSAGE(message.set_body(content_too_big), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Network2_MessageTest, set_body__will_set_the_body_length_to_match_the_size)
{
   AllegroFlare::Network2::Message message;
   std::vector<std::size_t> sizes_to_test = { 0, 10, 256, 112, 11, AllegroFlare::Network2::Message::MAX_BODY_LENGTH };

   for (auto &size_to_test : sizes_to_test)
   {
      message.set_body(std::string(size_to_test, 'x'));
      EXPECT_EQ(size_to_test, message.get_body_length());
   }
}


TEST(AllegroFlare_Network2_MessageTest, set_body__will_set_the_body)
{
   AllegroFlare::Network2::Message message;
   std::string message_body_content = "My Foobar Message Body";
   message.set_body(message_body_content);
   EXPECT_EQ(message_body_content, message.get_body());
}


TEST(AllegroFlare_Network2_MessageTest, set_body__will_set_the_expected_body_data_chunk_to_the_content_of_the_body)
{
   AllegroFlare::Network2::Message message;
   std::string message_body_content = "My Foobar Message Body";

   message.set_body(message_body_content);

   std::string expected_data_chunk = message.get_data().substr(message.HEADER_LENGTH, message.get_body_length());
   EXPECT_EQ(message_body_content, expected_data_chunk);
}


TEST(AllegroFlare_Network2_MessageTest,
   encode_header__with_an_empty_body__will_set_the_header_with_the_expected_format)
{
   AllegroFlare::Network2::Message message;
   message.encode_header();
   std::string expected_data = "AFNM0000a93dd14a";
   EXPECT_EQ(expected_data, message.get_header());
}


TEST(AllegroFlare_Network2_MessageTest,
   encode_header__with_different_body_sizes__will_set_the_second_header_chunk_to_an_expected_value)
{
   AllegroFlare::Network2::Message message;

   std::vector<std::tuple<std::string, std::size_t>> size_datas_to_test = {
      { "0000", 0 },
      { "000a", 10 },
      { "0048", 256 },
      { "001O", 112 },
      { "000b", 11 },
      //{ "008g", AllegroFlare::Network2::Message::MAX_BODY_LENGTH }, // when MAX_BODY_LENGTH is 512
      { "00x2", AllegroFlare::Network2::Message::MAX_BODY_LENGTH },
   };

   for (auto &size_datum_to_test : size_datas_to_test)
   {
      std::size_t size_to_test = std::get<1>(size_datum_to_test);
      std::string expected_second_header_chunk = std::get<0>(size_datum_to_test);

      message.set_body_length(size_to_test);
      message.encode_header();

      std::string second_header_chunk = message.get_header().substr(4, 4);
      EXPECT_EQ(expected_second_header_chunk, second_header_chunk);
   }
}


TEST(AllegroFlare_Network2_MessageTest,
   encode_header__with_various_body_sizes__will_set_the_third_header_chunk_with_the_expected_value)
{
   AllegroFlare::Network2::Message message;

   std::vector<std::tuple<std::string, std::size_t>> size_datas_to_test = {
      { "a738", 256 },
      //{ "2d99", AllegroFlare::Network2::Message::MAX_BODY_LENGTH }, // when MAX_BODY_LENGTH is 512
      { "5129", AllegroFlare::Network2::Message::MAX_BODY_LENGTH },
   };

   for (auto &size_datum_to_test : size_datas_to_test)
   {
      std::size_t size_to_test = std::get<1>(size_datum_to_test);
      std::string expected_second_header_chunk = std::get<0>(size_datum_to_test);

      message.set_body_length(size_to_test);
      message.encode_header();

      std::string second_header_chunk = message.get_header().substr(8, 4);
      EXPECT_EQ(expected_second_header_chunk, second_header_chunk);
   }
}


TEST(AllegroFlare_Network2_MessageTest,
   encode_header__with_various_body_content__will_set_the_fouth_header_chunk_with_the_expected_value)
{
   AllegroFlare::Network2::Message message;

   std::vector<std::tuple<std::string, std::string>> expected_header_chunk_and_content_data = {
      { "d14a", "" },
      { "61c6", "This is the content that will be hashed." },
      { "ddd1", "Content can be short" },
      //{ "05d8", std::string(AllegroFlare::Network2::Message::MAX_BODY_LENGTH, 'x') }, // when MAX_BODY_LENGTH is 512
      { "f31a", std::string(AllegroFlare::Network2::Message::MAX_BODY_LENGTH, 'x') }, // when MAX_BODY_LENGTH is 512*4
   };

   for (auto &expected_header_chunk_and_content_datum : expected_header_chunk_and_content_data)
   {
      std::string content = std::get<1>(expected_header_chunk_and_content_datum);
      std::string expected_fourth_header_chunk = std::get<0>(expected_header_chunk_and_content_datum);

      message.set_body(content);
      message.encode_header();
      std::string actual_fourth_header_chunk = message.get_header().substr(12, 4);

      EXPECT_EQ(expected_fourth_header_chunk, actual_fourth_header_chunk);
   }
}


TEST(AllegroFlare_Network2_MessageTest,
   decode_header_and_validate__when_the_header_is_properly_formed__will_return_an_empty_set_of_error_messages)
{
   AllegroFlare::Network2::Message message;
   message.encode_header();
   std::vector<std::string> validate_response = message.decode_header_and_validate();
   EXPECT_EQ(true, validate_response.empty());
}


TEST(AllegroFlare_Network2_MessageTest,
   decode_header_and_validate__with_a_malformed_header__will_return_error_messages)
{
   AllegroFlare::Network2::Message message;
   std::vector<std::string> validate_response = message.decode_header_and_validate();
   EXPECT_THAT(validate_response, testing::Contains("Magic header chunk does not match."));
}


TEST(AllegroFlare_Network2_MessageTest,
   validate_body_hash__when_the_header_is_properly_formed__will_return_an_empty_set_of_error_messages)
{
   AllegroFlare::Network2::Message message;
   message.encode_header();
   std::vector<std::string> validate_response = message.validate_body_hash();
   EXPECT_EQ(true, validate_response.empty());
}


TEST(AllegroFlare_Network2_MessageTest,
   validate_body_hash__when_the_header_body_hash_does_not_match_the_body_hash__will_return_the_expected_error_messages)
{
   AllegroFlare::Network2::Message message;
   std::vector<std::string> validate_response = message.validate_body_hash();
   EXPECT_THAT(validate_response, testing::Contains("Fourth chunk does not match the expected hash of the body."));
}


// TODO: add "validate" message
   // when MAGIC_HEADER_CHUNK is not present
   // when second chunk does not decode
   // when second chunk value is larger than max_body_size
   // when second chunk does not match body_size
   // when third chunk does not match hash of first 4 characters
   // when length chunk exceeds the max-body-size
   // other stuff...


