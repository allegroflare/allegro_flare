
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Server.hpp>


#include <atomic>
void abort_after_1_sec(std::atomic<bool>* global_abort = nullptr)
{
   sleep(1);
   *global_abort = true;
}


TEST(AllegroFlare_Network2_ServerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Server server;
}


TEST(AllegroFlare_Network2_ServerTest,
   run_blocking__when_a_port_is_already_running_at_that_address__will_raise_an_error)
{
   // TODO
}


TEST(AllegroFlare_Network2_ServerTest, run_blocking__will_run_the_client_program_while_blocking_the_current_thread)
   // TODO
{
   AllegroFlare::Network2::Server server;
   server.run_blocking_while_awaiting_abort();
}


