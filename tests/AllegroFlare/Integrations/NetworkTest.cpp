
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/Network.hpp>

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

void run_server(std::atomic<bool>* global_abort=nullptr)
{
   AllegroFlare::Network2::Server server(global_abort);
   server.run_blocking_while_awaiting_abort();
}



class AllegroFlare_Integrations_NetworkTest : public AllegroFlare::Integrations::Network
{};


TEST_F(AllegroFlare_Integrations_NetworkTest, can_be_created_without_blowing_up)
{
   std::thread server(run_server, get_global_abort_ptr());
   std::thread client(run_client, get_global_abort_ptr());
   std::thread aborter(emit_abort_signal_after_1_sec, get_global_abort_ptr());

   server.join();
   client.join();
   aborter.join();

   SUCCEED();
}


