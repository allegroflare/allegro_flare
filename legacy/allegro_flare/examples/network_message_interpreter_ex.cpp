#include <allegro5/allegro.h> // for compatibility with union/Makefile


#include <AllegroFlare/Network/NetworkService.hpp>
#include <string>
#include <iostream>


#include <lib/fnv.h>


bool shutdown_program = false;






//// custom allegro events: 


#define ALLEGRO_EVENT_NETWORK_RECEIVE_MESSAGE ALLEGRO_GET_EVENT_TYPE('N', 'T', 'W', 'K')

struct ALLEGRO_EVENT_NETWORK_SOURCE {
	ALLEGRO_EVENT_SOURCE event_source;
	int field1;
	int field2;
	// etc...
};

ALLEGRO_EVENT_NETWORK_SOURCE *al_create_network_event_source(void)
{
	ALLEGRO_EVENT_NETWORK_SOURCE *thing = (ALLEGRO_EVENT_NETWORK_SOURCE *)malloc(sizeof(ALLEGRO_EVENT_NETWORK_SOURCE)); 
	if (thing) {
		al_init_user_event_source(&thing->event_source);
		thing->field1 = 0;
		thing->field2 = 0;
	}

	return thing;
}

static void my_network_event_dtor(ALLEGRO_USER_EVENT *user_event)
{
	std::cout << "dtor" << std::endl;
	delete (std::string *)(user_event->data1);
}








class SpecialNetworkService : public NetworkService
{
private:
	ALLEGRO_EVENT_NETWORK_SOURCE *network_event_source;

public:
   SpecialNetworkService(ALLEGRO_EVENT_NETWORK_SOURCE *network_event_source=nullptr)
      : NetworkService()
      , network_event_source(network_event_source)
   {}

	virtual void on_message_receive(std::string message) override
   {
      if (!network_event_source)
      {
         throw std::runtime_error("Could not \"on_message_receive\" on a nullptr network_event_source");
      }
      //std::cout << "Boooond>" << message << std::endl;

      ALLEGRO_EVENT user_event;
      user_event.type = ALLEGRO_EVENT_NETWORK_RECEIVE_MESSAGE;
      std::string *msg = new std::string(message);
      user_event.user.data1 = (intptr_t)(msg);
      al_emit_user_event(&network_event_source->event_source, &user_event, my_network_event_dtor);
   }
};







class DaemusReciever
{
public:
   void process_message(std::string message)
   {
      std::cout << "message received: " << message << std::endl;
   }
};






int main(int argc, char* argv[])
{
   al_init();

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   //ALLEGRO_EVENT_QUEUE event_queue;


	ALLEGRO_EVENT_NETWORK_SOURCE *network_event_source;
   network_event_source = al_create_network_event_source();
   al_register_event_source(event_queue, &network_event_source->event_source);


   DaemusReciever dameus_receiver;


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

      SpecialNetworkService *network_service = new SpecialNetworkService(network_event_source);
      network_service->connect(ip_or_url, port_num);

      // for this example, we'll use the cin to get input from the user


      while (!shutdown_program)
      {
         ALLEGRO_EVENT current_event;
         al_wait_for_event(event_queue, &current_event);

         switch (current_event.type)
         {
         case ALLEGRO_EVENT_NETWORK_RECEIVE_MESSAGE:
            {
               //std::cout << "message received" << std::endl;
               std::string message = *(std::string *)(current_event.user.data1);
               //std::cout << "message received: " << message << std::endl;
               //main_project_screen->receive_signal("NETWORK_EVENT", (void *)(af::current_event->user.data1));
               al_unref_user_event(&current_event.user);
               dameus_receiver.process_message(message);
            }
            break;
         default:
            break;
         }
      }


      /*

      char line[SpecialNetworkService::max_message_length + 1];
      bool abort = false;
      while (!abort)
      {
         std::cin.getline(line, SpecialNetworkService::max_message_length + 1);
         if (line[0] == 'q') abort = true;
         else network_service->send_message(line);
      }

      */

      // after it's over, disconnect from the service

      network_service->disconnect();
   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << "\n";
   }

   al_uninstall_system();

   return 0;
}

