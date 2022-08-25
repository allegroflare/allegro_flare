

#include <AllegroFlare/Network2/Client.hpp>
//#include <AllegroFlare/Network2/inc/chat_client.hpp>



#include <AllegroFlare/Network2/inc/chat_message.hpp>




#include <chrono>
#include <thread>
static void sleep_for(float length_in_seconds)
{
   int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
   std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
}




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
  chat_client(
      asio::io_context& io_context,
      const tcp::resolver::results_type& endpoints,
      void (*my_injected_callback)(std::string, void*)=nullptr,
      void *my_callback_passed_data=nullptr
   )
       : io_context_(io_context)
       , socket_(io_context)
       , my_injected_callback(my_injected_callback)
       , my_callback_passed_data(my_callback_passed_data)

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

            std::string message_body(read_msg_.body_length(), 'x');
            memcpy(message_body.data(), read_msg_.body(), read_msg_.body_length());
            //message_body.resize = read_msg_.body();
            if (my_injected_callback) (*my_injected_callback)(message_body, my_callback_passed_data);
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
              // std::cout << "--chat_client : write\"" << std::endl; // I added this
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
  void (*my_injected_callback)(std::string, void*);
  void *my_callback_passed_data;
};




static void client_runner(
      std::atomic<bool> *global_abort=nullptr,
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr,
      void (*callback)(std::string, void*)=nullptr,
      void *callback_passed_data=nullptr,
      std::string host="localhost",
      std::string port="5432"
   )
{
  try
  {
    //asio::io_context io_context;

    //tcp::resolver resolver(io_context);
    //auto endpoints = resolver.resolve(host, port);
    //chat_client c(io_context, endpoints);

    //std::thread t([&io_context](){ io_context.run(); });

    //char line[chat_message::max_body_length + 1];
    //while (std::cin.getline(line, chat_message::max_body_length + 1))
    //{
      //chat_message msg;
      //msg.body_length(std::strlen(line));
      //std::memcpy(msg.body(), line, msg.body_length());
      //msg.encode_header();
      //c.write(msg);
    //}

    //c.close();
    //t.join();



    std::vector<std::string> messages_to_post = {
       //"This is the first placeholder message.",
       //"This is a second placeholder message.",
       //"This is a final message.",
    };

    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);
    chat_client c(io_context, endpoints, callback, callback_passed_data);

    std::thread t([&io_context, global_abort](){
       bool abort = false;
       while (!abort)
       {
          io_context.run_for(std::chrono::seconds(1));
          if (*global_abort) abort = true;
       }
    });

    char line[chat_message::max_body_length + 1];
    bool abort = false;
    int counts = 10;
    while (!abort)
    {
      if (messages_to_post.empty())
      {
         messages_queue_mutex->lock();
         if (!messages_queue->empty())
         {
            messages_to_post = *messages_queue;
            messages_queue->clear();
         }
         messages_queue_mutex->unlock();
      }

      sleep_for(0.005);

      if (*global_abort) abort = true;
 
      for (auto &message_to_post : messages_to_post)
      {
         chat_message msg;
         msg.body_length(message_to_post.size());
         std::memcpy(msg.body(), message_to_post.c_str(), msg.body_length());
         msg.encode_header();
         c.write(msg);
      }
      messages_to_post.clear();
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
      std::mutex *messages_queue_mutex,
      void (*callback)(std::string body, void*),
      void *callback_passed_data
)
   : global_abort(global_abort)
   , messages_queue(messages_queue)
   , messages_queue_mutex(messages_queue_mutex)
   , callback(callback)
   , callback_passed_data(callback_passed_data)
   , host("localhost")
   , port("5432")
{
}


Client::~Client()
{
}


void Client::set_port(std::string port)
{
   this->port = port;
}


void Client::set_host(std::string host)
{
   this->host = host;
}


void Client::run_blocking_while_awaiting_abort()
{
   // TODO: throw error when server is not running and cannot connect

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

   client_runner(global_abort, messages_queue, messages_queue_mutex, callback, callback_passed_data, host, port);
   return;
}
} // namespace Network2
} // namespace AllegroFlare


