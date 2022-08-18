#include <thread>
//#include <mutext>

#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Timeline/Actor.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <AllegroFlare/Color.hpp>

#include <AllegroFlare/Network/NetworkService.hpp>
#include <string>
#include <iostream>




class MotionEdit : public AllegroFlare::Screens::Base
{
private:
   std::vector<AllegroFlare::Timeline::Actor*> actors;
public:
   MotionEdit()
      : AllegroFlare::Screens::Base()
   {}
   ~MotionEdit() {}

   virtual void primary_timer_func() override
   {
      for (auto &actor : actors)
      {
         //TrackView track_view(actor);
      }
   }
};



void framework_main()
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   MotionEdit motion_edit;
   framework.register_screen("motion_edit", &motion_edit);
   framework.activate_screen("motion_edit");

   framework.run_loop();
}



class MyNetworkService : public NetworkService
{
public:
   virtual void on_message_receive(std::string message) override
   {
      std::cout << "MyNetworkService::on_message_receive: \"" << message << "\"" << std::endl;
   }
};


void network_main()
{
   std::string ip_or_url = "localhost";
   std::string port_num = "54321";

   MyNetworkService *network_service = new MyNetworkService();
   network_service->initialize();
   network_service->connect(ip_or_url, port_num);

   //char line[NetworkService::max_message_length + 1];
   for (unsigned i=0; i<5; i++)
   {
      std::cout << "NETWORK_MAIN() count: " << i << std::endl;
      network_service->send_message("foobar_message");
      //sleep(1);
   }
   //bool abort = false;
   //while (!abort)
   //{
      //std::cin.getline(line, NetworkService::max_message_length + 1);
      //if (line[0] == 'q') abort = true;
      //else network_service->send_message(line);
   //}

   // after it's over, disconnect from the service

   network_service->disconnect();
}






int main(int argc, char **argv)
{
   std::thread first(framework_main);
   std::thread second(network_main);

   first.join();
   second.join();

   std::cout << "executed_expectedly." << std::endl;
   return 0;
}




