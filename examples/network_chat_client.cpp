#include <allegro5/allegro.h> // for compatibility with union/Makefile


#include <AllegroFlare/Network/NetworkService.hpp>
#include <string>
#include <iostream>


#include <lib/fnv.h>



int main(int argc, char* argv[])
{
   try
   {
      std::string ip_or_url = "localhost";
      std::string port_num = "54321";

      if (argc != 3)
      {
         std::cout << "Usage: chat_client <host> <port>\n";
         std::cout << "no values provided, defaulting to:" << std::endl;
      }
      else
      {
         ip_or_url = argv[1];
         port_num = argv[2];
      }

      std::cout << "host: " << ip_or_url << std::endl;
      std::cout << "port: " << port_num << std::endl;

      // create the network service object

      NetworkService *network_service = new NetworkService();
      network_service->connect(ip_or_url, port_num);

      // for this example, we'll use the cin to get input from the user

      char line[NetworkService::max_message_length + 1];
      bool abort = false;
      while (!abort)
      {
         std::cin.getline(line, NetworkService::max_message_length + 1);
         if (line[0] == 'q') abort = true;
         else network_service->send_message(line);
      }

      // after it's over, disconnect from the service

      network_service->disconnect();
   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   return 0;
}
