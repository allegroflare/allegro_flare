#pragma once


#include <atomic>
#include <gtest/gtest.h>


namespace AllegroFlare
{
   namespace Integrations
   {
      class Network : public ::testing::Test
      {
      private:
         std::atomic<bool> global_abort;

      public:
         Network();
         virtual ~Network();

         std::atomic<bool>* get_global_abort_ptr();
         virtual void SetUp() override;
         virtual void TearDown() override;
         static void run_server_blocking(std::atomic<bool>* global_abort=nullptr);
         static void run_client_blocking(std::atomic<bool>* global_abort=nullptr);
      };
   }
}



