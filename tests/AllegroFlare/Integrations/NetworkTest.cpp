
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/Network.hpp>

#include <thread>



#include <atomic>
void ender(std::atomic<bool>* global_abort = nullptr)
{
   sleep(1);
   *global_abort = true;
}

void ended(std::atomic<bool>* global_abort = nullptr)
{
   while(!global_abort)
   {
   }
}


class AllegroFlare_Integrations_NetworkTest : public AllegroFlare::Integrations::Network
{};


TEST_F(AllegroFlare_Integrations_NetworkTest, can_be_created_without_blowing_up)
{
   //std::thread server(run_server_blocking, get_global_abort_ptr());
   //std::thread client(run_client_blocking);
   std::thread aborter(ender, get_global_abort_ptr());
   std::thread observer(ended, get_global_abort_ptr());

   aborter.join();
   observer.join();
   //server.join();
   //client.join();
   //AllegroFlare::Integrations::Network network;
}


