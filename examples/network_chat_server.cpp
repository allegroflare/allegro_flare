#include <allegro5/allegro.h> // for compatibility with union/Makefile


#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <asio.hpp>
#include "AllegroFlare/Network/NetworkMessage.hpp"


//----------------------------------------------------------------------

class NetworkUser
{
public:
	static int last_id;
	int id;
	NetworkUser()
		: id(++last_id)
	{}
	int get_user_id() { return id; }
	virtual ~NetworkUser() {}
	virtual void deliver(const NetworkMessage& msg) = 0;
};

int NetworkUser::last_id = 0;

//----------------------------------------------------------------------

class NetworkRoom
{
private:
   typedef std::shared_ptr<NetworkUser> NetworkUser_ptr;

	std::set<NetworkUser_ptr> users;
	int max_recent_msgs;
	std::deque<NetworkMessage> recent_msgs_;

public:
	NetworkRoom()
		: max_recent_msgs(100)
	{}
	void join(NetworkUser_ptr user)
	{
		users.insert(user);
		/*
		// this line dumps recent messages when a new user joins.
		// not a useful thing, nobody does this.
	    for (auto msg: recent_msgs_)
	      participant->deliver(msg);
		*/
		std::cout << "Participant (" << user << ") joined!" << std::endl;
	}

	void leave(NetworkUser_ptr user)
	{
		users.erase(user);
		std::cout << "Participant (" << user << ") left" << std::endl;
	}

	void deliver(const NetworkMessage& msg)
	{
		recent_msgs_.push_back(msg);

		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();

		for (auto user : users)
		{
			// only deliver the message if the recipient id matches
			if ((msg.get_recipient_id() == 0) || user->get_user_id() == msg.get_recipient_id())
			{
				user->deliver(msg);
			}
		}
	}
};

//---------------------------------------------------------------------

class NetworkUserSession : public NetworkUser, public std::enable_shared_from_this<NetworkUserSession>
{
private:
	asio::ip::tcp::socket socket_;
	NetworkRoom& room_;
	NetworkMessage read_msg_;
	std::deque<NetworkMessage> write_msgs_;

public:
	NetworkUserSession(asio::ip::tcp::socket socket, NetworkRoom& room)
		: NetworkUser()
		, socket_(std::move(socket))
		, room_(room)
	{
		std::cout << "starting session" << std::endl;
	}

	void start()
	{
		room_.join(shared_from_this());
		do_read_header();
	}

	void deliver(const NetworkMessage& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			do_write();
		}
	}

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    asio::async_read(socket_, asio::buffer(read_msg_.data(), NetworkMessage::header_length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_read_body()
  {
    auto self(shared_from_this());
    asio::async_read(socket_,
        asio::buffer(read_msg_.body(), read_msg_.get_body_length()),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
			  // here, I believe, is where a message would be intercepted and parsed
			  // this is a message that has been sent BY the client TO the server, and
			  // this app is then responding HERE by delivering the mssage to all the
			  // users in the room.
			  read_msg_.set_sender_id(self->get_user_id()); // ?? should this be self->get_user_id() or this->get_user_id()?
            room_.deliver(read_msg_);
			  // and then here, initiating the task to read the header
			  // the reason this do_read_header and do_read_body is seperated
			  // is because the header is fixed length, and the body length is not known
			  // until it has been extracted from the header
            do_read_header();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_write()
  {
    auto self(shared_from_this());
    asio::async_write(socket_,
        asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](std::error_code ec, std::size_t /*length*/)
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
            room_.leave(shared_from_this());
          }
        });
  }
};



//----------------------------------------------------------------------

class NetworkServer
{
private:
	asio::ip::tcp::acceptor acceptor_;
	asio::ip::tcp::socket socket_;
	NetworkRoom room_;

public:
	NetworkServer(asio::io_service& io_service, const asio::ip::tcp::endpoint& endpoint)
		: acceptor_(io_service, endpoint)
		, socket_(io_service)
	{
		do_accept();
	}

private:
	void do_accept()
	{
		// do_accept opens up a socket so a new client can connect in.  Once
		// a user connects, the server opens up another socket for the next user.  
		// When a user plugs in, a NetworkUserSession is created and launched (with start())

		acceptor_.async_accept(socket_, [this](std::error_code ec)
		{
		  if (!ec)
		  {
		    std::make_shared<NetworkUserSession>(std::move(socket_), room_)->start();
		  }

		  do_accept();
		});
	}
};

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: NetworkServer <port1> [<port2> ...]\n";
      return 1;
    }

    asio::io_service io_service;

    std::list<NetworkServer> servers;
    for (int i = 1; i < argc; ++i)
    {
      asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), std::atoi(argv[i]));
      servers.emplace_back(io_service, endpoint);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

