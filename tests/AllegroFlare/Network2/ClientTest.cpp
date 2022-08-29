
#include <gtest/gtest.h>

#include <AllegroFlare/Network2/Client.hpp>



#define TEST_HOST_NAME "localhost"
#define TEST_PORT_NUM "5433"


#include <chrono>
#include <thread>
static void sleep_for(float length_in_seconds)
{
   int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
   std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
}



#include <thread>

#include <atomic>
static void emit_abort_signal_after_n_sec(std::atomic<bool>* global_abort=nullptr, float sec=1.0f)
{
   sleep_for(sec);
   *global_abort = true;
}


void yay_callback(std::string message, void *data)
{
   std::cout << "HOLLY BONKERS:" << std::endl;
   std::cout << message.length() << std::endl;
   std::cout << "\"" << message << "\"" << std::endl;
}


static void run_client(
      std::atomic<bool>* global_abort=nullptr,
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr,
      void (*callback)(std::string, void*)=nullptr,
      void *callback_passed_data=nullptr
   )
{
   AllegroFlare::Network2::Client client(
         global_abort,
         messages_queue,
         messages_queue_mutex,
         callback,
         callback_passed_data
   );
   client.set_host(TEST_HOST_NAME);
   client.set_port(TEST_PORT_NUM);
   client.run_blocking_while_awaiting_abort();
}


#include <atomic>
static void publish_messages_every_second_for_6_seconds(
      std::vector<std::string> *message_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr
   )
{
   int count = 20;
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

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex, yay_callback, nullptr);
   std::thread exit_signal_emitter(emit_abort_signal_after_n_sec, &global_abort, 1);

   client.join();
   exit_signal_emitter.join();
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_post_message_sizes_up_to_MESSAGE_BODY_LENGTH_MAX)
{
   // TODO
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__with_a_posted_message_that_is_too_large__will_cout_an_error_message__and__will_not_send_the_message)
{
   std::string message_that_is_too_big = std::string(AllegroFlare::Network2::Client::MESSAGE_BODY_LENGTH_MAX+1, 'x');

   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = { message_that_is_too_big };
   std::mutex messages_queue_mutex;

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex, yay_callback, nullptr);
   std::thread exit_signal_emitter(emit_abort_signal_after_n_sec, &global_abort, 0.2);

   client.join();
   exit_signal_emitter.join();
}


TEST(AllegroFlare_Network2_ClientTest,
   run_blocking__will_detect_changes_to_the_messages_queue_and_post_them_to_the_network)
{
   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = {};
   std::mutex messages_queue_mutex;

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex, yay_callback, nullptr);
   std::thread exit_signal_emitter(emit_abort_signal_after_n_sec, &global_abort, 1);
   std::thread message_emitter(publish_messages_every_second_for_6_seconds, &messages_queue, &messages_queue_mutex);

   client.join();
   exit_signal_emitter.join();
   message_emitter.join();
}


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

   std::thread client(run_client, &global_abort, &messages_queue, &messages_queue_mutex, yay_callback, nullptr);
   std::thread exit_signal_emitter(emit_abort_signal_after_n_sec, &global_abort, 1);

   client.join();
   exit_signal_emitter.join();
}


