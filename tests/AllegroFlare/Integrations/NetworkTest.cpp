
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
   std::vector<std::string> messages_queue;
   std::mutex messages_queue_mutex;

   std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread client(run_client_blocking, get_global_abort_ptr(), &messages_queue, &messages_queue_mutex);
   std::thread aborter(emit_abort_signal_after_1_sec, get_global_abort_ptr());

   server.join();
   client.join();
   aborter.join();

   SUCCEED();
}


