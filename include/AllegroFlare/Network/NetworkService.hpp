#pragma once


#include <string>

class __NetworkServiceINTERNAL;



// Though not implemented, only one instance of NetworkService should be used.  This is because
// the internal implementation currently uses a global static asio::io_service. This can be
// modified in the future, but for now this shortcut was put in place to move the development
// along more quickly.

class NetworkService
{
private:
   __NetworkServiceINTERNAL *_service;
   bool initialized;

public:
   enum { max_message_length = 512 };

   NetworkService();
   virtual ~NetworkService();

   void initialize();

   bool connect(std::string domain_or_ip_address, std::string port_num);
   bool disconnect();
   bool is_connected();

   bool send_message(std::string message);
   virtual void on_message_receive(std::string message);
};


