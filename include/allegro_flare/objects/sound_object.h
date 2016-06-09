#ifndef ___AF_SOUND_OBJECT_HEADER
#define ___AF_SOUND_OBJECT_HEADER




#include <allegro5/allegro_audio.h>




class Sound
{
private:
   ALLEGRO_SAMPLE_INSTANCE *sample_instance;
   ALLEGRO_MIXER *mixer;
   ALLEGRO_VOICE *voice;
   float _position;
   float _paused;

public:
   Sound(ALLEGRO_SAMPLE *sample);
   Sound(ALLEGRO_SAMPLE *sample, ALLEGRO_VOICE *voice);

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

   ALLEGRO_BITMAP *create_render(int w, int h);
};




/*
ALLEGRO_SAMPLE *get_sample(std::string identifier);


class Sound
{
private:
   ALLEGRO_SAMPLE *smpl;
   ALLEGRO_SAMPLE_ID *sid;
   ALLEGRO_SAMPLE_INSTANCE *instance;
   float _vol, _pan, _speed;
   ALLEGRO_PLAYMODE _playmode;
   static float master_volume;

public:
   Sound()
      : smpl(NULL)
      , _vol(1.0)
      , _pan(ALLEGRO_AUDIO_PAN_NONE)
      , _speed(1.0)
      , _playmode(ALLEGRO_PLAYMODE_ONCE)
      , sid(NULL)
   { }
   inline Sound &reset()
   {
      smpl=NULL;
      _vol = 1.0;
      _pan = ALLEGRO_AUDIO_PAN_NONE;
      _speed = 1.0;
      _playmode = ALLEGRO_PLAYMODE_ONCE;
      sid = NULL;
      return *this;
   }
   inline Sound &sample(ALLEGRO_SAMPLE *s) { smpl = s; return *this; }
   inline Sound &sample(const char *identifier) { smpl = get_sample(identifier); return *this; }
   inline Sound &volume(float val) { _vol = val; return *this; }
   inline Sound &pan(float val) { _pan = val; return *this; }
   inline Sound &playmode(float val) { _pan = val; return *this; }
   inline Sound &speed(float val) { _speed = val; return *this; }
   //inline void play() { al_play_sample(smpl, _vol*master_volume, _pan, _speed, ALLEGRO_PLAYMODE_ONCE, NULL); }
   inline void play() { al_play_sample(smpl, _vol*master_volume, _pan, _speed, ALLEGRO_PLAYMODE_ONCE, sid); }
   inline void stop() { if (sid) al_stop_sample(sid); }
   //inline void is_playing() { if
};


Sound &sound(const char *identifier);
Sound &sound(ALLEGRO_SAMPLE *sample);
*/




#endif
