#include <thread>
//#include <mutext>

#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Timeline/Actors/Base.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <AllegroFlare/Color.hpp>

#include <AllegroFlare/Network2/Client.hpp>
//#include <AllegroFlare/Network/NetworkService.hpp>
#include <string>
#include <iostream>



#include <AllegroFlare/MotionComposer/MessageFactory.hpp>
//#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>



std::string current_message = "[message-unset]";
std::mutex current_message_mutex;

//bool global_shutdown = false;
//std::mutex global_shutdown_mutex;


static std::string join(std::vector<std::string> tokens, std::string delimiter)
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i == tokens.size()-1) last = true;
      if (!last) result << delimiter;
   }

   return result.str();
}


class MotionEditControl : public AllegroFlare::Screens::Base
{
private:
   std::vector<AllegroFlare::Timeline::Actors::Base *> actors;
   AllegroFlare::FontBin *font_bin;
   std::vector<std::string> *messages_queue;
   std::mutex *messages_queue_mutex;
   AllegroFlare::MotionComposer::MessageFactory message_factory;
   std::string instruction;

public:
   MotionEditControl(
         AllegroFlare::FontBin *font_bin, 
         std::vector<std::string> *messages_queue=nullptr,
         std::mutex *messages_queue_mutex=nullptr
   )
      : AllegroFlare::Screens::Base()
      , actors()
      , font_bin(font_bin)
      , messages_queue(messages_queue)
      , messages_queue_mutex(messages_queue_mutex)
      , instruction()
   {}
   ~MotionEditControl() {}

   virtual void primary_timer_func() override
   {
      ALLEGRO_FONT *font = font_bin->auto_get("Inter-Medium.ttf -42");
      AllegroFlare::Placement2D place(1920/2, 1080/2, 800, 600);

      al_clear_to_color(ALLEGRO_COLOR{0.2, 0.21, 0.205, 1.0});

      place.start_transform();
      al_draw_multiline_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, 300, 30, 0, instruction.c_str());
      place.restore_transform();

      for (auto &actor : actors)
      {
         //TrackView track_view(actor);
      }
   }

   void post_message(std::string message)
   {
      messages_queue_mutex->lock();
      messages_queue->push_back(message);
      messages_queue_mutex->unlock();
   }

   void send_set_playhead(float position=0.0)
   {
      std::string message = message_factory.build_set_playhead_position_message_json(position);
      post_message(message);
   }

   void send_toggle_playback()
   {
      std::string message = message_factory.build_toggle_playback_message_json();
      post_message(message);
   }

   void send_clear()
   {
      std::string message = message_factory.build_clear_message_json();
      post_message(message);
   }

   void send_create_test_actor()
   {
      std::vector<std::string> script_lines = {
         "0.0 x 960.0 linear",
         "0.0 y 540.0 linear",

         "0.0 rotation 4.0 linear",
         "2.0 rotation 0.0 tripple_fast_in",

         "0.0 opacity 0.0 linear",
         "0.4 opacity 1.0 linear",
         "1.9 opacity 1.0 linear",
         "2.2 opacity 0.0 fast_out",

         "0.0 scale_x 0 linear",
         "0.0 scale_y 0 linear",
         "0.1 scale_x 0 linear",
         "0.1 scale_y 0 linear",
         "0.7 scale_x 1.2 bounce_out",
         "0.7 scale_y 1.2 bounce_out",

         //"0 color_r 0. linear",
         //"0 color_g 0.84 linear",
         //"0 color_b 0.0 linear",

         "0 color_r 0.91 linear",
         "0 color_g 0.875 linear",
         "0 color_b 0.537 linear",
      };

      std::string script = join(script_lines, "\n");

      std::string message = message_factory.build_add_actor2d_with_script_message_json(
         "actor1",
         "star-b.png",
         script
      );
      post_message(message);
   }

   virtual void key_down_func(ALLEGRO_EVENT *ev) override
   {
      //std::cout << "Key down: " << std::endl;
      std::string instruction = "R: rewind playhead\nA: create actor\nC: clear\nSPACE: toggle playback";

      switch(ev->keyboard.keycode)
      {
      case ALLEGRO_KEY_R: 
         send_set_playhead(0.0);
         break;
      case ALLEGRO_KEY_A: 
         send_create_test_actor();
         break;
      case ALLEGRO_KEY_C: 
         send_clear();
         break;
      case ALLEGRO_KEY_SPACE: 
         send_toggle_playback();
         break;
      }
   }
};




#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"


void framework_main(
   std::atomic<bool>* global_abort=nullptr,
   std::vector<std::string> *messages_queue=nullptr,
   std::mutex *messages_queue_mutex=nullptr
)
{
   bool shutdown = false;

   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   MotionEditControl motion_edit_control(
         &framework.get_font_bin_ref(),
         messages_queue,
         messages_queue_mutex
         );
   framework.register_screen("motion_edit_control", &motion_edit_control);
   framework.activate_screen("motion_edit_control");

   framework.run_loop();

   (*global_abort) = true;
   //global_shutdown_mutex.lock();
   //global_shutdown = true;
   //global_shutdown_mutex.unlock();
}





//#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"


//void framework_main()
//{
   //bool shutdown = false;

   //AllegroFlare::Frameworks::Full framework;
   //framework.disable_fullscreen();
   //framework.initialize();

   //framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   //MotionEdit motion_edit(&framework.get_font_bin_ref());
   //framework.register_screen("motion_edit", &motion_edit);
   //framework.activate_screen("motion_edit");

   //framework.run_loop();

   //global_shutdown_mutex.lock();
   //global_shutdown = true;
   //global_shutdown_mutex.unlock();
//}




//class MyNetworkService : public NetworkService
//{
//public:
   //virtual void on_message_receive(std::string message) override
   //{
      //std::cout << "MyNetworkService::on_message_receive: \"" << message << "\"" << std::endl;
   //}
//};


//void network_main()
//{
   //bool shutdown = false;
   //std::string ip_or_url = "localhost";
   //std::string port_num = "54321";

   //MyNetworkService *network_service = new MyNetworkService();
   //network_service->initialize();
   //network_service->connect(ip_or_url, port_num);

   //network_service->send_message("sending message!");


   //while (!shutdown)
   //{
      //global_shutdown_mutex.lock();
      //if (global_shutdown) shutdown = true;
      //global_shutdown_mutex.unlock();
   //}

   //network_service->disconnect();
//}



static void run_client(
      std::atomic<bool>* global_abort=nullptr,
      std::vector<std::string> *messages_queue=nullptr,
      std::mutex *messages_queue_mutex=nullptr,
      void (*callback)(std::string, void*)=nullptr,
      void *callback_passed_data=nullptr
   )
{
   AllegroFlare::Network2::Client client(
         global_abort,
         messages_queue,
         messages_queue_mutex,
         callback,
         callback_passed_data
   );
   client.run_blocking_while_awaiting_abort();
}






int main(int argc, char **argv)
{
   std::atomic<bool> global_abort;
   std::vector<std::string> messages_queue;
   std::mutex messages_queue_mutex;
   //void (*callback)(std::string, void*)=nullptr,
   //void *callback_passed_data=nullptr


   std::thread first(
         framework_main,
         &global_abort,
         &messages_queue,
         &messages_queue_mutex
   );
   std::thread second(
         run_client,
         &global_abort,
         &messages_queue,
         &messages_queue_mutex,
         nullptr,
         nullptr
   );

   first.join();
   second.join();

   std::cout << "executed_expectedly." << std::endl;
   return 0;
}




