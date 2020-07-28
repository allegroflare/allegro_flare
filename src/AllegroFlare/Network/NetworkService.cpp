#include <AllegroFlare/Network/NetworkService.hpp>

#include <AllegroFlare/Network/NetworkClient.hpp>
#include <AllegroFlare/Network/globals.hpp>

#include <asio.hpp>
#include <iostream>


static asio::io_service GLOBAL__io_service;


static void send_network_message(NetworkClient &c, char* line)
{
   NetworkMessage message;
   message.set_body_length(std::strlen(line));
   std::memcpy(message.body(), line, message.get_body_length());
   message.encode_header();

   c.write(message);
}




class __NetworkServiceINTERNAL
{
private:
   asio::io_service &io_service_loc;
   NetworkClient *client;
   std::thread *thread;
   bool connected;

public:
   __NetworkServiceINTERNAL()
      : io_service_loc(GLOBAL__io_service)
      , client(0)
      , thread(0)
      , connected(false)
   {
   }
   bool is_connected()
   {
      return connected;
   }
   bool send_message(char* line)
   {
      if (!connected) return false;
      send_network_message(*client, line);
      return true;
   }
   bool connect(std::string url_or_ip, std::string port_num)
   {
      if (connected) return false;

      char *argv1 = new char[url_or_ip.length() + 1];
      strcpy(argv1, url_or_ip.c_str());

      char *argv2 = new char[port_num.length() + 1];
      strcpy(argv2, port_num.c_str());

      asio::ip::tcp::resolver resolver(io_service_loc);
       auto endpoint_iterator = resolver.resolve({ argv1, argv2 });

      client = new NetworkClient(io_service_loc, endpoint_iterator);
       //thread = new std::thread([&io_service_loc](){ io_service_loc.run(); });
       thread = new std::thread([this](){
         if (io_service_loc.stopped()) io_service_loc.reset(); // reset is required if the io_service has stopped
         io_service_loc.run();
         std::cout << "disconnection event occured" << std::endl;

         //disconnect(); // this function call is a little sloppy here.  It's purpose is to call disconnect() if the
                    // disconnection was initiated from the server
      });

      connected = true;

      delete[] argv1;
      delete[] argv2;

      return true;
   }
   bool disconnect()
   {
      if (!connected) return false;

      std::cout << "Disconnecting...";
      client->close();
      thread->join();
      std::cout << "done." << std::endl;

      connected = false;
      delete thread;
      delete client;
      client = 0; // < ?? should client be deleted?
      thread = 0; // < ?? should thread be deleted?

      return true;
   }
};





NetworkService::NetworkService()
   : _service(0)
{
   _service = new __NetworkServiceINTERNAL();
   //_on_recieve_message_callback_func = callback_func_ex;
   _on_recieve_message_callback_func = std::bind(&NetworkService::on_message_receive, this, std::placeholders::_1);
}


NetworkService::~NetworkService()
{
   delete _service;
}


bool NetworkService::connect(std::string url_or_ip, std::string port_num)
{
   return _service->connect(url_or_ip, port_num);
}


bool NetworkService::disconnect()
{
   return _service->disconnect();
}


bool NetworkService::is_connected()
{
   return _service->is_connected();
}


bool NetworkService::send_message(std::string message)
{
   if (message.length() < NetworkMessage::max_body_length)
      message.resize(NetworkMessage::max_body_length);
   char *argv1 = new char[message.length() + 1];
   strcpy(argv1, message.c_str());

   bool ret_val = _service->send_message(argv1);

   delete[] argv1;

   return ret_val;
}


void NetworkService::on_message_receive(std::string message)
{
   std::cout << "BOUND>" << message << std::endl;
}





