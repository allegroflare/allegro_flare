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
            std::string song_filename;
            float song_bpm;
            AllegroFlare::Timer timer;
            ALLEGRO_AUDIO_STREAM* audio_stream;
            ALLEGRO_VOICE* audio_voice;
            ALLEGRO_MIXER* audio_mixer;
            bool initialized;
            bool stream_is_attached;
            float MIN_SONG_BPM;
            float latency_sec;

         protected:


         public:
            Hypersync(ALLEGRO_EVENT_QUEUE* event_queue=nullptr, std::string song_filename="/Users/markoates/Repos/allegro_flare/bin/data/samples/music_tracks/some-jamzz-04.ogg", float song_bpm=130.0f);
            ~Hypersync();

            ALLEGRO_EVENT_QUEUE* get_event_queue() const;
            std::string get_song_filename() const;
            float get_song_bpm() const;
            void TODO();
            void set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            void set_song_filename(std::string song_filename="[unset-song-filename.ogg]");
            void set_song_bpm(float song_bpm=0.0f);
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



