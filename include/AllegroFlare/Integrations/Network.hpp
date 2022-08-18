#pragma once


#include <AllegroFlare/Network2/Server.hpp>
#include <atomic>
#include <gtest/gtest.h>


namespace AllegroFlare
{
   namespace Integrations
   {
      class Network : public ::testing::Test
      {
      private:
         AllegroFlare::Network2::Server server;
         std::atomic<bool> global_abort;

      public:
         Network(AllegroFlare::Network2::Server server={});
         virtual ~Network();

         void set_server(AllegroFlare::Network2::Server server);
         AllegroFlare::Network2::Server get_server();
         std::atomic<bool>* get_global_abort_ptr();
         virtual void SetUp() override;
         virtual void TearDown() override;
         static void run_server_blocking(std::atomic<bool>* global_abort=nullptr);
         static void run_client_blocking();
      };
   }
}



