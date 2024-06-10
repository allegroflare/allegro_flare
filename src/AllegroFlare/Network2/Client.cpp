

#include <AllegroFlare/Network2/Client.hpp>
//#include <AllegroFlare/Network2/inc/chat_client.hpp>



//#include <AllegroFlare/Network2/inc/chat_message.hpp>
#include <AllegroFlare/Network2/Message.hpp>
#include <AllegroFlare/Logger.hpp>




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

typedef std::deque<AllegroFlare::Network2::Message> chat_message_queue;

class ChatClient
{
private:
  asio::io_context& io_context_;
  tcp::socket socket;
  AllegroFlare::Network2::Message message_being_read;
  chat_message_queue messages_to_write;
  void (*my_injected_callback)(std::string, void*);
  void *my_callback_passed_data;
  bool initialized;

public:
  ChatClient(
      asio::io_context& io_context,
      //const tcp::resolver::results_type& endpoints,
      void (*my_injected_callback)(std::string, void*)=nullptr,
      void *my_callback_passed_data=nullptr
   )
       : io_context_(io_context)
       , socket(io_context)
       , my_injected_callback(my_injected_callback)
       , my_callback_passed_data(my_callback_passed_data)
       , initialized(false)

  {}


  void initialize(const tcp::resolver::results_type& endpoints)
  {
    if (initialized) throw std::runtime_error("ChatClient already initialized; Cannot call more than once.");
    connect(endpoints);
    initialized = true;
  }

  void write(const AllegroFlare::Network2::Message& msg)
  {
    if (!initialized) throw std::runtime_error("ChatClient::write: error: must be initialized first.");

    asio::post(io_context_,
        [this, msg]()
        {
          bool write_in_progress = !messages_to_write.empty();
          messages_to_write.push_back(msg);
          if (!write_in_progress)
          {
            write();
          }
        });
  }

  void close()
  {
    if (!initialized) throw std::runtime_error("ChatClient::close: error: must be initialized first.");

    asio::post(io_context_, [this]() { socket.close(); });
  }

private:
  void connect(const tcp::resolver::results_type& endpoints)
  {
    asio::async_connect(socket, endpoints,
        [this](std::error_code ec, tcp::endpoint)
        {
          if (!ec)
          {
            read_header();
          }
          else
          {
            std::stringstream error_message;
            error_message << "AllegroFlare::Network2::Client error: connect() returned with an error. "
                          << "The error code was " << ec << ".";
            std::cout << error_message.str() << std::endl;
          }
        });
  }

  void read_header()
  {
     asio::async_read(socket,
        asio::buffer(message_being_read.data_ptr(), AllegroFlare::Network2::Message::HEADER_LENGTH),
        [this](std::error_code error_code, std::size_t /*length*/)
        {
           bool header_parsed_correctly = false;
           if (error_code)
           {
              std::stringstream error_message;
              error_message << "AllegroFlare::Network2::Client error: read_header() returned with an error. "
                            << "Closing the socket.";
              std::cout << error_message.str() << std::endl;

              socket.close();
           }
           else
           {
              std::vector<std::string> header_decoding_error_messages = message_being_read.decode_header_and_validate();

              if (!header_decoding_error_messages.empty())
              {
                 AllegroFlare::Logger::error_from(
                    "AllegroFlare::Network2::Client",
                    "When decoding the header, errors were returned. Closing the socket."
                 );

                 socket.close();
              }
              else
              {
                 header_parsed_correctly = true;
              }
           }

           if (header_parsed_correctly)
           {
              read_body();
           }
        });
  }

  void read_body()
  {
    asio::async_read(socket,
        asio::buffer(message_being_read.body_ptr(), message_being_read.get_body_length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            std::cout.write(message_being_read.body_ptr(), message_being_read.get_body_length());
            std::cout << "\n";

            std::string message_body(message_being_read.get_body_length(), 'x');
            memcpy(message_body.data(), message_being_read.body_ptr(), message_being_read.get_body_length());
            //message_body.resize = read_msg_.body();
            if (my_injected_callback) (*my_injected_callback)(message_body, my_callback_passed_data);
            read_header();
          }
          else
          {
            std::stringstream error_message;
            error_message << "AllegroFlare::Network2::Client error: read_body() returned with an error.";
            std::cout << error_message.str() << std::endl;
            //throw std::runtime_error(error_message.str());

            socket.close();
          }
        });
  }

  void write()
  {
    asio::async_write(socket,
        asio::buffer(messages_to_write.front().data_ptr(),
          messages_to_write.front().length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            messages_to_write.pop_front();
            if (!messages_to_write.empty())
            {
              write();
              // std::cout << "--chat_client : write\"" << std::endl; // I added this
            }
          }
          else
          {
            std::stringstream error_message;
            error_message << "AllegroFlare::Network2::Client error: write() returned with an error. "
                          << "The error code was " << ec << ".";
            std::cout << error_message.str() << std::endl;

            socket.close();
          }
        });
  }
};






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


   std::atomic<bool> *local_global_abort = global_abort;


  try
  {
    //asio::io_context io_context;

    //tcp::resolver resolver(io_context);
    //auto endpoints = resolver.resolve(host, port);
    //ChatClient c(io_context, endpoints);

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
    ChatClient chat_client(io_context, callback, callback_passed_data);
    chat_client.initialize(endpoints);

    std::thread t([&io_context, local_global_abort](){
       bool abort = false;
       while (!abort)
       {
          io_context.run_for(std::chrono::seconds(1));
          if (*local_global_abort) abort = true;
       }
    });

    // NOTE:
    // Messages are currently delivered 1 message at a time with a delay of 0.005 seconds between each.
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

      if (*local_global_abort) abort = true;
 
      for (auto &message_to_post : messages_to_post)
      {
         if (message_to_post.size() > MESSAGE_BODY_LENGTH_MAX)
         {
            std::stringstream error_message;
            std::cout << "AllegroFlare::Network2::Client: error: Cannot send message. The message body is too large ("
                      << message_to_post.size() << " bytes) which cannot be larger than MESSAGE_BODY_LENGTH_MAX ("
                      << MESSAGE_BODY_LENGTH_MAX << " bytes).";
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "======MESSAGE BEGIN======" << std::endl;
            std::cout << message_to_post << std::endl;
            std::cout << "======MESSAGE END======" << std::endl;
            std::cout << std::endl;
         }
         else
         {
            AllegroFlare::Network2::Message msg;
            msg.set_body_length(message_to_post.size());
            std::memcpy(msg.body_ptr(), message_to_post.c_str(), msg.get_body_length());
            msg.encode_header();
            chat_client.write(msg);
         }
      }
      messages_to_post.clear();
    }

    chat_client.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }


}
} // namespace Network2
} // namespace AllegroFlare


