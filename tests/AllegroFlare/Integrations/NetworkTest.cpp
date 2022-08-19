
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/Network.hpp>

#include <AllegroFlare/Network2/Client.hpp>
#include <AllegroFlare/Network2/Server.hpp>



#include <chrono>
#include <thread>
static void sleep_for(float length_in_seconds)
{
   int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
   std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
}


#include <thread>

#include <atomic>
void emit_abort_signal_after_n_sec(std::atomic<bool>* global_abort=nullptr, int num_seconds=1)
{
   sleep(num_seconds);
   *global_abort = true;
}


#include <atomic>
static void publish_n_messages_every_m_seconds_for_j_seconds(
      std::vector<std::string> *message_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr
   )
{
   int count = 6;
   while (count>0)
   {
      sleep_for(0.2);

      std::stringstream ss;
      ss << "hey, this is message " << count << ".";

      messages_queue_mutex->lock();
      message_queue->push_back(ss.str());
      messages_queue_mutex->unlock();
      count--;
   }
}



class AllegroFlare_Integrations_NetworkTest : public AllegroFlare::Integrations::Network {};


TEST_F(AllegroFlare_Integrations_NetworkTest, server__can_be_created_and_aborted_without_blowing_up)
{
   std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread aborter(emit_abort_signal_after_n_sec, get_global_abort_ptr(), 1);
   server.join();
   aborter.join();
}


TEST_F(AllegroFlare_Integrations_NetworkTest, client__can_be_created_and_aborted_without_blowing_up)
{
   std::vector<std::string> messages_queue;
   std::mutex messages_queue_mutex;
   //std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread client(run_client_blocking, get_global_abort_ptr(), &messages_queue, &messages_queue_mutex, nullptr, nullptr);
   std::thread aborter(emit_abort_signal_after_n_sec, get_global_abort_ptr(), 1);

   //server.join();
   client.join();
   aborter.join();
}


TEST_F(AllegroFlare_Integrations_NetworkTest,
   FLAKEY__client_will_receive_messages_sent_by_another_client)
{
   // TODO
   std::vector<std::string> sending_messages_queue;
   std::mutex sending_messages_queue_mutex;
   std::vector<std::string> receiving_messages_queue;
   std::mutex receiving_messages_queue_mutex;

   std::thread server(run_server_blocking, get_global_abort_ptr());
   std::thread client_that_will_send(
      run_client_blocking,
      get_global_abort_ptr(),
      &sending_messages_queue,
      &sending_messages_queue_mutex,
      nullptr,
      nullptr
   );
   std::thread client_that_will_receive(
      run_client_blocking,
      get_global_abort_ptr(),
      &receiving_messages_queue,
      &receiving_messages_queue_mutex,
      AllegroFlare::Integrations::Network::simple_capture_callback,
      nullptr
   );
   std::thread aborter(emit_abort_signal_after_n_sec, get_global_abort_ptr(), 1);
   std::thread publisher(
      publish_n_messages_every_m_seconds_for_j_seconds,
      &sending_messages_queue,
      &sending_messages_queue_mutex
   );

   server.join();
   client_that_will_send.join();
   client_that_will_receive.join();
   aborter.join();
   publisher.join();

   std::vector<std::string> expected_possible_captured_messages = {
      "hey, this is message 6.",
      "hey, this is message 5.",
      "hey, this is message 4.", // This test is flakey
      //"hey, this is message 3.",
      //"hey, this is message 2.",
   };

   std::vector<std::string> actual_captured_callback_messages = get_captured_callback_messages();

   EXPECT_GE(actual_captured_callback_messages.size(), 2);
   EXPECT_LE(actual_captured_callback_messages.size(), expected_possible_captured_messages.size());
   for (int i=0; i<actual_captured_callback_messages.size(); i++)
   {
      EXPECT_EQ(expected_possible_captured_messages[i], actual_captured_callback_messages[i]);
   }
}


