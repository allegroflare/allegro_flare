
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Client.hpp>

#include <thread>

#include <atomic>
void emit_abort_signal_after_1_sec(std::atomic<bool>* global_abort=nullptr)
{
   sleep(1);
   *global_abort = true;
}

void run_client(std::atomic<bool>* global_abort=nullptr)
{
   AllegroFlare::Network2::Client client(global_abort);
   client.run_blocking_while_awaiting_abort();
}



TEST(AllegroFlare_Network2_ClientTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Client client;
}


TEST(AllegroFlare_Network2_ClientTest, run_blocking__will_run_the_client_program_while_blocking_the_current_thread)
{
   AllegroFlare::Network2::Client client;
   //client.run_blocking();
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_abort_the_blocking_function_if_the_abort_signal_is_set)
{
   std::atomic<bool> global_abort = false;

   std::thread client(run_client, &global_abort);
   std::thread exit_signal_emitter(emit_abort_signal_after_1_sec, &global_abort);

   client.join();
   exit_signal_emitter.join();
}


