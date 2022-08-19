#include <allegro5/allegro.h>
#include <AllegroFlare/Network2/Client.hpp>



#include <atomic>
static void emit_abort_signal_after_1_sec(std::atomic<bool>* global_abort=nullptr)
{
   sleep(5);
   std::cout << "EMITTING GLOBAL ABORT" << std::endl;
   *global_abort = true;
}


int main(int argc, char **argv)
{
   std::atomic<bool> global_abort = false;
   std::vector<std::string> messages_queue = { "This is test message A", };
   std::mutex messages_queue_mutex;

   AllegroFlare::Network2::Client client(&global_abort, &messages_queue, &messages_queue_mutex);
   client.run_blocking_while_awaiting_abort();

   return 0;
}


