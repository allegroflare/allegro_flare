
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Network2/URLTokenizer.hpp>


TEST(AllegroFlare_Network2_URLTokenizerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::URLTokenizer urltokenizer;
}


TEST(AllegroFlare_Network2_URLTokenizerTest, extract_host__will_return_the_host)
{
   AllegroFlare::Network2::URLTokenizer urltokenizer("tcp://8.tcp.ngrok.io:12345");
   EXPECT_EQ("8.tcp.ngrok.io", urltokenizer.extract_host());
}


TEST(AllegroFlare_Network2_URLTokenizerTest, extract_port__will_return_the_port_number)
{
   AllegroFlare::Network2::URLTokenizer urltokenizer("tcp://8.tcp.ngrok.io:12345");
   EXPECT_EQ("12345", urltokenizer.extract_port());
}


TEST(AllegroFlare_Network2_URLTokenizerTest, extract_tokens__will_throw_an_error_on_invalid_or_unsupported_urls)
{
   std::vector<std::pair<int, std::string>> invalid_url_test_datas = {
      { 1, "foobar" },                 // no port, no "tcp://" prefix
      { 2, "tcp://8.tcp.ngrok.io" },   // missing port ":" prefix
      { 3, "tcp://x:54321" },          // invalid host (fewer than 4 characters)
      { 4, "tcp://8.tcp.ngrok.io:" },  // not enough port numbers (fewer than 4 characters)
      { 1, "http://www.url.com" },     // not a "tcp://" prefix
      { 5, "tcp://xyz.io:9999999" },   // invalid port (more than 6 characters)
      { 6, "tcp://xyz.io:9ixy7" },     // invalid port (non-numerical characters)
   };

   for (auto &invalid_url_test_data : invalid_url_test_datas)
   {
      AllegroFlare::Network2::URLTokenizer urltokenizer(invalid_url_test_data.second);
      std::string expected_error_message =
         "Network2::URLTokenizer: invalid url format (error " + std::to_string(invalid_url_test_data.first) + ")";
      EXPECT_THROW_WITH_MESSAGE(urltokenizer.split_tokens(), std::invalid_argument, expected_error_message);
   }
}


