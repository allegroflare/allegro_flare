
#include <gtest/gtest.h>

#include <AllegroFlare/EncoderDecoders/Base62.hpp>


TEST(AllegroFlare_EncoderDecoders_Base62Test, can_be_created_without_blowing_up)
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
}


static std::vector<std::pair<int, std::string>> test_data = {
   { 0,   "0" },
   { 1,   "1" },
   { 10,  "a" },
   { 36,  "A" },
   { 61,  "Z" },
   { 62, "10" },
   { 63, "11" },

   { 2147483647, "2lkCB1" }, // int32 max
   { 65535,      "h31" },         // uint16 max
   { 14776335,   "ZZZZ" },     // max for 4 characters of base62

   // cases from https://github.com/abhishekjhaji/go-base62/blob/master/base62/intconverter_test.go
   { 30410,      "7Uu" },
   { 859715137,  "Wbhbb" },

   // this case from this jsfiddle http://jsfiddle.net/kf0828kt/
   // via this tutorial https://lowrey.me/encoding-decoding-base-62-in-es6-javascript/
   { 883314, "3HN0" },

   // from this article https://medium.com/@anabhishek.jha/base-62-text-encoding-decoding-b43921c7a954
   { 65535, "h31" },
};


TEST(AllegroFlare_EncoderDecoders_Base62Test, encode__will_encode_an_integer_number_to_a_base62_representation)
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   for (auto &test_datum : test_data)
   {
      int int_value = std::get<0>(test_datum);
      std::string expected_base62_encoding = std::get<1>(test_datum);
      EXPECT_EQ(expected_base62_encoding, base62_encoder.encode(int_value));
   }
}


TEST(AllegroFlare_EncoderDecoders_Base62Test, decode__will_decode_an_base62_representation_of_a_number_into_an_int)
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   for (auto &test_datum : test_data)
   {
      int expected_int_value = std::get<0>(test_datum);
      std::string base62_encoding = std::get<1>(test_datum);
      EXPECT_EQ(expected_int_value, base62_encoder.decode(base62_encoding));
   }
}


TEST(AllegroFlare_EncoderDecoders_Base62Test, decode__will_properly_handle_zero_fills)
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   static std::vector<std::pair<int, std::string>> test_data = {
      { 0,     "0000" },
      { 1,     "0001" },
      { 62,    "0010" },
      { 3844,  "0100" },

      { 65535, "0h31" },
   };
   for (auto &test_datum : test_data)
   {
      int expected_int_value = std::get<0>(test_datum);
      std::string base62_encoding = std::get<1>(test_datum);
      EXPECT_EQ(expected_int_value, base62_encoder.decode(base62_encoding));
   }
}


