#pragma once



#include <allegro5/allegro_audio.h>
#include <string>




namespace AllegroFlare
{
   // TODO: Look into using al_play_sample (while returning a ALLEGRO_SAMPLE_ID) in place of al_play_sample_instance.
   // To do this, you would have to more accurately manage the mixer and voice.
   class Sound
   {
   private:
      ALLEGRO_SAMPLE *sample;
      ALLEGRO_SAMPLE_INSTANCE *sample_instance;
      ALLEGRO_MIXER *mixer;
      //ALLEGRO_VOICE *voice;
      float _position;
      float _paused;
      bool initialized;

      void validate_initialized(std::string function_name);

   public:
      Sound(ALLEGRO_SAMPLE *sample=nullptr);
      //Sound(ALLEGRO_SAMPLE *sample, ALLEGRO_VOICE *voice);

      void initialize();

      Sound &play();
      Sound &stop();
      Sound &toggle_playback();
      Sound &rewind();
      Sound &pause();
      Sound &unpause();
      Sound &toggle_pause();
      bool is_playing();
      bool is_paused();

      double get_length_sec();
      float volume();
      Sound &volume(float vol);
      double position();
      Sound &position(double time);
      float pan();
      Sound &pan(float pan);
      float speed();
      Sound &speed(float speed);
      Sound &loop(bool yes=true);
      Sound &bidir();
   };
}




