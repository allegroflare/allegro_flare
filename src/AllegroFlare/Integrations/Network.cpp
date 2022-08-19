

#include <AllegroFlare/Integrations/Network.hpp>
#include <AllegroFlare/Network2/Server.hpp>
#include <AllegroFlare/Network2/Client.hpp>


namespace AllegroFlare
{
namespace Integrations
{


std::vector<std::string> Network::captured_callback_messages = {};


Network::Network()
   : ::testing::Test()
   , global_abort(false)
{
}


Network::~Network()
{
}


std::vector<std::string> Network::get_captured_callback_messages()
{
   return captured_callback_messages;
}


std::atomic<bool>* Network::get_global_abort_ptr()
{
   return &global_abort;
}

void Network::SetUp()
{
   captured_callback_messages.clear();
   return;
}

void Network::TearDown()
{
   return;
}

void Network::run_server_blocking(std::atomic<bool>* global_abort)
{
   // TODO: bind this testing server to a proper testing port
   //https://stackoverflow.com/questions/18183174/how-do-i-correctly-randomly-assign-a-port-to-a-test-http-server-using-boost-asio

   AllegroFlare::Network2::Server server(global_abort);
   server.run_blocking_while_awaiting_abort();
   return;
}

void Network::run_client_blocking(std::atomic<bool>* global_abort, std::vector<std::string>* messages_queue, std::mutex* messages_queue_mutex, void (*callback)(std::string))
{
   // TODO: bind this testing client to a proper testing port
   //https://stackoverflow.com/questions/18183174/how-do-i-correctly-randomly-assign-a-port-to-a-test-http-server-using-boost-asio

   AllegroFlare::Network2::Client client(global_abort, messages_queue, messages_queue_mutex, callback);
   client.run_blocking_while_awaiting_abort();
   return;
}

void Network::simple_capture_callback(std::string message)
{
   captured_callback_messages.push_back(message);
   return;
}
} // namespace Integrations
} // namespace AllegroFlare


