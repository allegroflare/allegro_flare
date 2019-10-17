



#include <allegro_flare/sound_object.h>

#include <AllegroFlare/SampleBin.hpp>
#include <allegro_flare/sample_renderer.h>


	

Sound::Sound(ALLEGRO_SAMPLE *sample)
   : sample_instance(al_create_sample_instance(sample))
   , mixer(al_create_mixer(41000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2))
   , voice(al_create_voice(41000, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2))
   , _position(0)
   , _paused(false)
{
   al_attach_sample_instance_to_mixer(sample_instance, mixer);
   al_attach_mixer_to_voice(mixer, voice);
}




Sound::Sound(ALLEGRO_SAMPLE *sample, ALLEGRO_VOICE *voice)
   : sample_instance(al_create_sample_instance(sample))
   , mixer(al_create_mixer(41000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2))
   , voice(voice)
   , _position(0)
   , _paused(false)
{
   al_attach_sample_instance_to_mixer(sample_instance, mixer);
   al_attach_mixer_to_voice(mixer, voice);
}




Sound &Sound::play()
{
   if (!al_play_sample_instance(sample_instance)) std::cout << "[" << __FUNCTION__ << "] could not al_play_sample_instance" << std::endl;
   else _paused = false;
   return *this;
}




Sound &Sound::toggle_playback()
{
   if (is_playing()) stop();
   else play();
   return *this;
}




Sound &Sound::toggle_pause()
{
   if (is_playing()) pause();
   else unpause();
   return *this;
}




Sound &Sound::pause()
{
   _position = position();
   al_stop_sample_instance(sample_instance);
   _paused = true;
   return *this;
}




Sound &Sound::unpause()
{
   if (is_paused())
   {
      play();
      position(_position);
      _paused = false;
   }
   return *this;
}




bool Sound::is_paused()
{
   return _paused;
}




Sound &Sound::stop()
{
   al_stop_sample_instance(sample_instance);
   position(0);
   return *this;
}




Sound &Sound::rewind()
{
   position(0);
   return *this;
}




float Sound::volume()
{
   return al_get_sample_instance_gain(sample_instance);
}




Sound &Sound::volume(float vol)
{
   al_set_sample_instance_gain(sample_instance, vol);
   return *this;
}




double Sound::get_length_sec()
{
   return al_get_sample_instance_time(sample_instance);
}




double Sound::position()
{
   if (is_paused()) return _position;

   _position = (float)al_get_sample_instance_position(sample_instance)
      / al_get_sample_instance_length(sample_instance)
      * al_get_sample_instance_time(sample_instance);

   return _position;
}




Sound &Sound::position(double time)
{
   unsigned int pos = (unsigned int)(al_get_sample_instance_length(sample_instance)
         * (time / al_get_sample_instance_time(sample_instance)));
   al_set_sample_instance_position(sample_instance, pos);
   return *this;
}




bool Sound::is_playing()
{
   return al_get_sample_instance_playing(sample_instance);
}




Sound &Sound::pan(float pan)
{
   al_set_sample_instance_pan(sample_instance, pan);
   return *this;
}




float Sound::pan()
{
   return al_get_sample_instance_pan(sample_instance);
}




Sound &Sound::loop(bool yes)
{
   if (yes) al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
   else al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_ONCE);
   return *this;
}




Sound &Sound::bidir()
{
   al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_BIDIR);
   return *this;
}




Sound &Sound::speed(float speed)
{
   al_set_sample_instance_speed(sample_instance, speed);
   return *this;
}




float Sound::speed()
{
   return al_get_sample_instance_speed(sample_instance);
}




ALLEGRO_BITMAP *Sound::create_render(int w, int h)
{
   ALLEGRO_BITMAP *render = al_create_bitmap(w, h);
   SampleRenderer sample_renderer(al_get_sample(sample_instance));
   sample_renderer.draw_wav_sample(render);
   return render;
}




/*

static Sound *_current_soundbuilder = new Sound();

Sound &sound(const char *identifier) { _current_soundbuilder->reset().sample(identifier); return *_current_soundbuilder; }
Sound &sound(ALLEGRO_SAMPLE *sample) { _current_soundbuilder->reset().sample(sample); return *_current_soundbuilder; }

float Sound::master_volume = 0.3;




static SampleBin *master_sample_bin = NULL;

ALLEGRO_SAMPLE *get_sample(std::string filename)
{
   // create the bin if it doesn't exist
   if (master_sample_bin==NULL) { master_sample_bin = new SampleBin; }

   // find it
   SampleBin::Record *record = master_sample_bin->get_record(filename);
   if (record) return record->data;

   // if it wasn't found, load it
   master_sample_bin->load(filename, filename);
   std::cout << "(!) " << filename << " was loaded real-time.  Be sure to load it manually first." << std::endl;
   record = master_sample_bin->get_record(filename);
   return record->data;
}

*/




