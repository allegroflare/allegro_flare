
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/Network.hpp>

#include <AllegroFlare/Network2/Client.hpp>
#include <AllegroFlare/Network2/Server.hpp>


#include <thread>

#include <atomic>
void emit_abort_signal_after_1_sec(std::atomic<bool>* global_abort=nullptr)
{
   sleep(1);
   *global_abort = true;
}


class AllegroFlare_Integrations_NetworkTest : public AllegroFlare::Integrations::Network {};


TEST_F(AllegroFlare_Integrations_NetworkTest, can_be_created_without_blowing_up)
{
   std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread client(run_client_blocking, get_global_abort_ptr());
   std::thread aborter(emit_abort_signal_after_1_sec, get_global_abort_ptr());

   server.join();
   client.join();
   aborter.join();

   SUCCEED();
}


TEST_F(AllegroFlare_Integrations_NetworkTest, will_send_messages_between_clients)
{
   std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread client_a(run_client_blocking, get_global_abort_ptr());
   std::thread client_b(run_client_blocking, get_global_abort_ptr());
   std::thread aborter(emit_abort_signal_after_1_sec, get_global_abort_ptr());

   server.join();
   client_a.join();
   client_b.join();
   aborter.join();

   SUCCEED();
}


