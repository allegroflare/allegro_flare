#pragma once


#include <string>
#include "AllegroFlare/Network/NetworkMessage.hpp"


#include <asio.hpp>
#include <deque>


class NetworkClient
{
   private:
      asio::io_service& io_service_;
      asio::ip::tcp::socket socket_;
      NetworkMessage read_msg_;
      std::deque<NetworkMessage> write_msgs_;

   public:
      NetworkClient(asio::io_service& io_service, asio::ip::tcp::resolver::iterator endpoint_iterator);

      void write(const NetworkMessage& msg);

      void close();

   private:
      void do_connect(asio::ip::tcp::resolver::iterator endpoint_iterator);

      void do_read_header();

      void do_read_body();

      void do_write();
};


