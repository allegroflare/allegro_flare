
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Server.hpp>
#include <thread>


#include <atomic>
static void emit_abort_signal_after_1_sec(std::atomic<bool>* global_abort=nullptr)
{
   sleep(1);
   *global_abort = true;
}

static void run_server(std::atomic<bool>* global_abort=nullptr)
{
   AllegroFlare::Network2::Server server(global_abort);
   server.run_blocking_while_awaiting_abort();
}


TEST(AllegroFlare_Network2_ServerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Server server;
}


TEST(AllegroFlare_Network2_ServerTest,
   run_blocking__without_a_global_abort__will_raise_an_error)
{
   // TODO
}


TEST(AllegroFlare_Network2_ServerTest,
   run_blocking__when_a_port_is_already_running_at_that_address__will_raise_an_error)
{
   // TODO
}


TEST(AllegroFlare_Network2_ServerTest,
   run_blocking__can_be_aborted_by_setting_the_global_abort_to_true)
{
   std::atomic<bool> global_abort = false;

   std::thread server(run_server, &global_abort);
   std::thread exit_signal_emitter(emit_abort_signal_after_1_sec, &global_abort);

   server.join();
   exit_signal_emitter.join();
}


