

#include <AllegroFlare/Network/NetworkClient.hpp>


#include <AllegroFlare/Network/globals.hpp>



static std::vector<std::string> message_log;
//static boost::mutex message_log_mutex;
static std::mutex message_log_mutex;
static int num_new_messages = 0;
//boost::function<void(std::string)> _on_recieve_message_callback_func;
//static std::function<void(std::string)> _on_recieve_message_callback_func;
//static void (*_on_recieve_message_callback_func)(std::string) = 0; 

static void write_log_message(std::string message)
{
	message_log.push_back(message);
	num_new_messages++;
	//if (_on_recieve_message_callback_func)
	//	_on_recieve_message_callback_func(message);
	_on_recieve_message_callback_func(message);
}




NetworkClient::NetworkClient(asio::io_service& io_service, asio::ip::tcp::resolver::iterator endpoint_iterator)
   : io_service_(io_service)
   , socket_(io_service)
{
   do_connect(endpoint_iterator);
}

void NetworkClient::write(const NetworkMessage& msg)
{
 io_service_.post(
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

void NetworkClient::close()
{
   io_service_.post([this]() { socket_.close(); });
}

void NetworkClient::do_connect(asio::ip::tcp::resolver::iterator endpoint_iterator)
{
 asio::async_connect(socket_, endpoint_iterator,
     [this](std::error_code ec, asio::ip::tcp::resolver::iterator)
     {
       if (!ec)
       {
         do_read_header();
       }
     });
}

void NetworkClient::do_read_header()
{
 asio::async_read(socket_,
     asio::buffer(read_msg_.data(), NetworkMessage::header_length),
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

void NetworkClient::do_read_body()
{
 asio::async_read(socket_,
     asio::buffer(read_msg_.body(), read_msg_.get_body_length()),
     [this](std::error_code ec, std::size_t /*length*/)
     {
       if (!ec)
       {
   message_log_mutex.lock();
   //message_log_mutex.lock();
   std::string message_text(read_msg_.body(), read_msg_.get_body_length());
   write_log_message(message_text);
   message_log_mutex.unlock();
   //message_log_mutex.unlock();
   //std::cout.write(read_msg_.body(), read_msg_.get_body_length());
   //std::cout << "\n";

   do_read_header();
       }
       else
       {
         socket_.close();
       }
     });
}

void NetworkClient::do_write()
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




