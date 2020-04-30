#pragma once


#include <string>

class __NetworkServiceINTERNAL;



// Though not implemented, 
// only one instance of NetworkService should be used

class NetworkService
{
private:
	__NetworkServiceINTERNAL *_service;

public:
	enum { max_message_length = 512 };
	
	NetworkService();
	virtual ~NetworkService();

	bool connect(std::string domain_or_ip_address, std::string port_num);
	bool disconnect();
	bool is_connected();

	bool send_message(std::string message);
	virtual void on_message_receive(std::string message);
};


