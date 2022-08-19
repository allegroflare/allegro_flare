#include <thread>
//#include <mutext>

#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Timeline/Actor.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <AllegroFlare/Color.hpp>

#include <AllegroFlare/Network2/Client.hpp>
#include <string>
#include <iostream>




std::vector<std::string> message_queue = {};
//std::mutex current_message_mutex;

//bool global_shutdown = false;
//std::mutex global_shutdown_mutex;




class MotionEdit : public AllegroFlare::Screens::Base
{
private:
   std::vector<AllegroFlare::Timeline::Actor*> actors;
   AllegroFlare::FontBin *font_bin;

public:
   MotionEdit(AllegroFlare::FontBin *font_bin)
      : AllegroFlare::Screens::Base()
      , actors()
      , font_bin(font_bin)
   {}
   ~MotionEdit() {}

   virtual void primary_timer_func() override
   {
      ALLEGRO_FONT *font = font_bin->auto_get("Inter-Medium.ttf -42");
      float width = 1100;
      AllegroFlare::Placement2D place(1920/2, 1080/2, width, 600);
      float line_height= 30;

      place.start_transform();
      al_draw_multiline_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, width, line_height, 0, most_recent_message().c_str());

      float cursor_y = 100;
      for (auto &message : last_n_messages_excluding_first_message(5))
      {
         al_draw_multiline_text(font, ALLEGRO_COLOR{0.8, 0.805, 0.81, 1.0}, 0, cursor_y, width, line_height, 0, message.c_str());
         cursor_y += line_height+20;
      }

      place.restore_transform();

      for (auto &actor : actors)
      {
         //TrackView track_view(actor);
      }
   }

   std::string most_recent_message()
   {
      if (message_queue.empty()) return "[empty]";
      return message_queue.back();
   }

   std::vector<std::string> last_n_messages_excluding_first_message(int n)
   {
      std::vector<std::string> result;
      if (message_queue.empty()) return result;

      for (int i=1; i<message_queue.size() && i<n; i++)
      {
         result.push_back(message_queue[message_queue.size()-1 - i]);
      }

      return result;
   }
};

#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"


void framework_main(std::atomic<bool>* global_abort=nullptr)
{
   bool shutdown = false;

   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   MotionEdit motion_edit(&framework.get_font_bin_ref());
   framework.register_screen("motion_edit", &motion_edit);
   framework.activate_screen("motion_edit");

   framework.run_loop();

   (*global_abort) = true;
   //global_shutdown_mutex.lock();
   //global_shutdown = true;
   //global_shutdown_mutex.unlock();
}



static void receive_message_callback(std::string message, void *data)
{
   //std::cout << "MyNetworkService::on_message_receive: \"" << message << "\"" << std::endl;
   message_queue.push_back(message);
}



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
         &global_abort
   );
   std::thread second(
         run_client,
         &global_abort,
         &messages_queue,
         &messages_queue_mutex,
         receive_message_callback,
         nullptr
   );

   first.join();
   second.join();

   std::cout << "executed_expectedly." << std::endl;
   return 0;
}



