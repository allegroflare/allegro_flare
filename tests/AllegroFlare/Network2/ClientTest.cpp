
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Client.hpp>

#include <thread>

#include <atomic>
static void emit_abort_signal_after_1_sec(std::atomic<bool>* global_abort=nullptr)
{
   sleep(1);
   *global_abort = true;
}

static void run_client(
      std::atomic<bool>* global_abort=nullptr,
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr
   )
{
   AllegroFlare::Network2::Client client(global_abort, messages_queue, messages_queue_mutex);
   client.run_blocking_while_awaiting_abort();
}

#include <atomic>
static void publish_messages_every_second_for_6_seconds(
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr
   )
{
   int count = 6;
   while (count>0)
   {
      std::stringstream ss;
         ss << "hey, this is message " << count << ".";
      messages_queue_mutex->lock();
      messages_queue->push_back(ss.str());
      //messages_to_post = *messages_queue;
      //messages_queue->clear();
      messages_queue_mutex->unlock();
      sleep(1);
      count--;
   }
   
   //*global_abort = true;
}


TEST(AllegroFlare_Network2_ClientTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Network2::Client client;
}


TEST(AllegroFlare_Network2_ClientTest, run_blocking__will_run_the_client_program_while_blocking_the_current_thread)
{
   AllegroFlare::Network2::Client client;
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_abort_the_blocking_function_if_the_abort_signal_is_set)
{
   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = {};
   std::mutex messages_queue_mutex;

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex);
   std::thread exit_signal_emitter(emit_abort_signal_after_1_sec, &global_abort);

   client.join();
   exit_signal_emitter.join();
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_detect_changes_to_the_messages_queue_and_post_them_to_the_network)
{
   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = {};
   std::mutex messages_queue_mutex;

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex);
   std::thread exit_signal_emitter(emit_abort_signal_after_1_sec, &global_abort);
   std::thread message_emitter(publish_messages_every_second_for_6_seconds, &messages_queue, &messages_queue_mutex);

   client.join();
   exit_signal_emitter.join();
   message_emitter.join();
}


/*
TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_process_messages_in_the_messages_queue)
{
   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = {
      "This is the first message.",
      "Another message is written here.",
      "I have a third and final message.",
   };
   std::mutex messages_queue_mutex;

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex);
   std::thread exit_signal_emitter(emit_abort_signal_after_1_sec, &global_abort);

   client.join();
   exit_signal_emitter.join();
}
*/


