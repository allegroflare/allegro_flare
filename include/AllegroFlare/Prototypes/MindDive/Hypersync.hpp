#pragma once


#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <string>


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
            bool stream_is_attached;
            std::string song_filename;
            float song_bpm;
            float MIN_SONG_BPM;
            float latency_sec;

         protected:


         public:
            Hypersync(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            ~Hypersync();

            ALLEGRO_EVENT_QUEUE* get_event_queue() const;
            void TODO();
            void set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            float get_timer_seconds();
            float get_timer_milliseconds();
            float get_timer_microseconds();
            int get_beat_num(float seconds=0.0f);
            int get_measure_num(float seconds=0.0f);
            std::string build_beat_clock_str();
            void start();
            void initialize();
            void destruct();
         };
      }
   }
}



