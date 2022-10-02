#pragma once


#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class Hypersync
         {
         private:
            ALLEGRO_EVENT_QUEUE* event_queue;
            AllegroFlare::Timer timer;
            ALLEGRO_AUDIO_STREAM* audio_stream;
            ALLEGRO_VOICE* audio_voice;
            ALLEGRO_MIXER* audio_mixer;
            bool initialized;

         protected:


         public:
            Hypersync(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            ~Hypersync();

            ALLEGRO_EVENT_QUEUE* get_event_queue() const;
            void set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            int get_timer_milliseconds();
            void start();
            void initialize();
            void destruct();
         };
      }
   }
}



