
#include <gtest/gtest.h>

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


