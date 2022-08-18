
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Client.hpp>


TEST(AllegroFlare_Network2_ClientTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Client client;
}


TEST(AllegroFlare_Network2_ClientTest, run_blocking__will_run_the_client_program_while_blocking_the_current_thread)
{
   AllegroFlare::Network2::Client client;
   //client.run_blocking();
}


