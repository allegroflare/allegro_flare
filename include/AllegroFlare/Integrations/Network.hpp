#pragma once


#include <atomic>
#include <gtest/gtest.h>
#include <mutex>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Integrations
   {
      class Network : public ::testing::Test
      {
      private:
         std::atomic<bool> global_abort;
         static std::vector<std::string> captured_callback_messages;

      public:
         Network();
         virtual ~Network();

         static std::vector<std::string> get_captured_callback_messages();
         std::atomic<bool>* get_global_abort_ptr();
         virtual void SetUp() override;
         virtual void TearDown() override;
         static void run_server_blocking(std::atomic<bool>* global_abort=nullptr);
         static void run_client_blocking(std::atomic<bool>* global_abort=nullptr, std::vector<std::string>* messages_queue=nullptr, std::mutex* messages_queue_mutex=nullptr, void (*callback)(std::string, void*)=nullptr, void* callback_data=nullptr);
         static void simple_capture_callback(std::string message="[unset-message]", void* data=nullptr);
      };
   }
}



