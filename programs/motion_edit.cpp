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


#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>

#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


std::vector<std::string> message_queue = {};
//std::mutex current_message_mutex;

//bool global_shutdown = false;
//std::mutex global_shutdown_mutex;




class MotionEdit : public AllegroFlare::Screens::Base
{
private:
   float playhead_position;
   std::vector<AllegroFlare::Timeline::Actor*> actors;
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
   AllegroFlare::FontBin *font_bin;

public:
   MotionEdit(AllegroFlare::FontBin *font_bin)
      : AllegroFlare::Screens::Base()
      , actors()
      , message_processor()
      , font_bin(font_bin)
   {}
   ~MotionEdit() {}

   void process_message()
   {
      // grab a message from the message queue
      if (message_queue.empty()) return;

      //std::cout << "Processing 1 message" << std::endl;

      // grab a raw message off our local queue, put it into the processor
      message_processor.push_one(message_queue.back());
      message_queue.erase(message_queue.begin()); // (equivelent to .pop_front())

      // convert the message
      message_processor.convert_one();

      // extract the processed the message
      AllegroFlare::MotionComposer::Messages::Base* message_to_execute = message_processor.get_one_message_and_pop();

      // execute the message
      if (message_to_execute != nullptr)
      {
         // TODO
         if (message_to_execute->is_type("SetPlayheadPosition"))
         {
            AllegroFlare::MotionComposer::Messages::SetPlayheadPosition *typed_message = 
               static_cast<AllegroFlare::MotionComposer::Messages::SetPlayheadPosition*>(message_to_execute);
            set_playhead_position(typed_message->get_position());
         }
      }
   }

   void update()
   {
      process_message();
   }

   void set_playhead_position(float position=0.0)
   {
      playhead_position = position;
   }

   void draw()
   {
      // draw
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

      draw_playhead_position();
   }

   void draw_playhead_position()
   {
      ALLEGRO_FONT *font = font_bin->auto_get("Inter-Medium.ttf -42");
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 100, 20, 0, "position %f", playhead_position);
   }

   virtual void primary_timer_func() override
   {
      update();
      draw();
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
   //std::cout << std::endl;
   //message_queue.push_back(message);
   message_queue.push_back(
std::string(R"({
  "message": {
    "type": "SetPlayheadPosition",
    "position": 8.0
  }
})")
);

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

   std::cout << "✅ All threads executed expectedly. Shutting down \"motion_edit\"." << std::endl;
   return 0;
}



