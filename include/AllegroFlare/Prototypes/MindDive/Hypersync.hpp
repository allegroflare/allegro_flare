#pragma once


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
            ALLEGRO_AUDIO_STREAM* audio_stream;
            bool initialized;

         protected:


         public:
            Hypersync(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            ~Hypersync();

            ALLEGRO_EVENT_QUEUE* get_event_queue() const;
            void set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
            void initialize();
            void destruct();
         };
      }
   }
}



