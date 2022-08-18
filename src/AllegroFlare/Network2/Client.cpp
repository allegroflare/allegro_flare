

#include <AllegroFlare/Network2/Client.hpp>
//#include <AllegroFlare/Network2/inc/chat_client.hpp>



#include <AllegroFlare/Network2/inc/chat_message.hpp>



//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#include <allegro5/allegro.h>

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <asio.hpp>
//#include "chat_message.hpp"

using asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
  chat_client(asio::io_context& io_context,
      const tcp::resolver::results_type& endpoints)
    : io_context_(io_context),
      socket_(io_context)
  {
    do_connect(endpoints);
  }

  void write(const chat_message& msg)
  {
    asio::post(io_context_,
        [this, msg]()
        {
          bool write_in_progress = !write_msgs_.empty();
          write_msgs_.push_back(msg);
          if (!write_in_progress)
          {
            do_write();
          }
        });
  }

  void close()
  {
    asio::post(io_context_, [this]() { socket_.close(); });
  }

private:
  void do_connect(const tcp::resolver::results_type& endpoints)
  {
    asio::async_connect(socket_, endpoints,
        [this](std::error_code ec, tcp::endpoint)
        {
          if (!ec)
          {
            do_read_header();
          }
        });
  }

  void do_read_header()
  {
    asio::async_read(socket_,
        asio::buffer(read_msg_.data(), chat_message::header_length),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_read_body()
  {
    asio::async_read(socket_,
        asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            do_read_header();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_write()
  {
    asio::async_write(socket_,
        asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            socket_.close();
          }
        });
  }

private:
  asio::io_context& io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};




static void client_runner(
      std::atomic<bool> *global_abort=nullptr,
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr,
      std::string host="localhost",
      std::string port="5432"
   )
{
  try
  {
    //if (argc != 3)
    //{
      //std::cerr << "Usage: chat_client <host> <port>\n";
      //return 1;
    //}

    bool abort = false;

    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);
    chat_client c(io_context, endpoints);

    std::thread t([&io_context, abort](){
       int counts = 0;
       bool local_abort = abort;
       while(!local_abort)
       {
          io_context.run_for(std::chrono::milliseconds(100)); // 1000 milliseconds = 1 second
          counts++;
          if (counts > 30) local_abort = true;
       };
    });

    char line[chat_message::max_body_length + 1];

    std::vector<std::string> messages_to_post; 

    //while (std::cin.getline(line, chat_message::max_body_length + 1))
    std::string message_to_post = "";
    while (!abort)
    {
      message_to_post = "";

      if (!messages_to_post.empty())
      {
         message_to_post = messages_to_post.back();
         messages_to_post.pop_back();
      //}

      //if (!message_to_post.empty())
      //{
         chat_message msg;
         //msg.body_length(std::strlen(line));
         //std::memcpy(msg.body(), line, msg.body_length());
         msg.body_length(message_to_post.size());
         std::memcpy(msg.body(), message_to_post.c_str(), msg.body_length());
         msg.encode_header();
         c.write(msg);

         std::cout << "--client_runner() processed message: \"" << message_to_post << "\"" << std::endl;
       }
       else
       {
          messages_queue_mutex->lock();
          if (!messages_queue->empty())
          {
             messages_to_post = *messages_queue;
             messages_queue->clear();
          }
          messages_queue_mutex->unlock();
       }

       //messages_queue_mutex->lock();
       //messages_queue
       //messages_queue_mutex->unlock();

       if (*global_abort) abort = true;
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}






















namespace AllegroFlare
{
namespace Network2
{


Client::Client(
      std::atomic<bool> *global_abort,
      std::vector<std::string> *messages_queue,
      std::mutex *messages_queue_mutex
)
   : global_abort(global_abort)
   , messages_queue(messages_queue)
   , messages_queue_mutex(messages_queue_mutex)
{
}


Client::~Client()
{
}


void Client::run_blocking_while_awaiting_abort()
{
   if (!global_abort)
   {
      throw std::runtime_error("AllegroFlare/Network2/Client::run_blocking_while_awaiting_abort: error "
                               "global_abort cannot be nullptr.");
   }
   if (!messages_queue)
   {
      throw std::runtime_error("AllegroFlare/Network2/Client::run_blocking_while_awaiting_abort: error "
                               "messages_queue cannot be nullptr.");
   }
   if (!messages_queue_mutex)
   {
      throw std::runtime_error("AllegroFlare/Network2/Client::run_blocking_while_awaiting_abort: error "
                               "messages_queue_mutex cannot be nullptr.");
   }

   client_runner(global_abort, messages_queue, messages_queue_mutex);
   return;
}
} // namespace Network2
} // namespace AllegroFlare


