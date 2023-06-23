


#include <AllegroFlare/Sound.hpp>

#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Errors.hpp>
#include <sstream>



namespace AllegroFlare
{



Sound::Sound(ALLEGRO_SAMPLE *sample)
   : sample(sample)
   , sample_instance(nullptr)
   , mixer(nullptr)
   //, voice(nullptr)
   , _position(0)
   , _paused(false)
   , initialized(false)
{
   //initialize();
}



//Sound::Sound(ALLEGRO_SAMPLE *sample, ALLEGRO_VOICE *voice)
   //: sample_instance(nullptr)
   //, mixer(al_create_mixer(41000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2))
   //, voice(voice)
   //, _position(0)
   //, _paused(false)
//{
   //initialize();
//}



void Sound::validate_initialized(std::string function_name)
{
   if (!initialized)
   {
      std::stringstream error_message;
      error_message << "Sound::" << function_name << ": error: you must initialize Sound before calling this function.";
      throw std::runtime_error(error_message.str());
   }
}



void Sound::initialize()
{
   if (initialized) throw std::runtime_error("Sound::initialize: error: cannot call initialize more than once");

   //mixer = al_create_mixer(41000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
   //voice = al_create_voice(41000, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
   mixer = al_get_default_mixer();
   //voice = al_get_default_voice();

   if (!sample)
   {
      AllegroFlare::Errors::throw_error("AllegroFlare::Sound::initialize",
                                        "Could not create sample instance because ALLEGRO_SAMPLE is nullptr.");
      //std::cout << "[AllegroFlare::Sound::Sound] error: could not create sample instance because sample "
                //<< "is a nullptr." << std::endl;
   }

   if (!mixer)
   {
      // TODO: improve this error message. Something like "mixer needed. Typically, a mixer would be auto-created 
      // when a call to al_reserve_samples(...), occurs."
      AllegroFlare::Errors::throw_error("AllegroFlare::Sound::initialize",
                                        "Was not able to successfully obtain a mixer. AllegroFlare/Sound is "
                                        "currently implemented to rely on the presence of Allegro's auto-created "
                                        "mixer (a result of a call to al_reserve_samples()). "
                                        "AllegroFlare/Sound obtains this mixer via al_get_default_mixer(), but it is "
                                        "not present."
                                        );
   }

   //if (!voice)
   //{
      //AllegroFlare::Errors::throw_error("AllegroFlare::Sound::initialize",
                                        //"Was not able to successfully obtain a voice.");
   //}

   sample_instance = al_create_sample_instance(sample);
   al_attach_sample_instance_to_mixer(sample_instance, mixer);
   //al_attach_mixer_to_voice(mixer, voice);
   
   initialized = true;
}



Sound &Sound::play()
{
   validate_initialized("play");
   if (!al_play_sample_instance(sample_instance))
   {
      std::cout << "[AllegroFlare::Sound::" << __FUNCTION__ << "] could not al_play_sample_instance" << std::endl;
   }
   else _paused = false;
   return *this;
}



Sound &Sound::toggle_playback()
{
   validate_initialized("toggle_playback");
   if (is_playing()) stop();
   else play();
   return *this;
}



Sound &Sound::toggle_pause()
{
   validate_initialized("toggle_pause");
   if (is_playing()) pause();
   else unpause();
   return *this;
}



Sound &Sound::pause()
{
   validate_initialized("pause");
   _position = position();
   al_stop_sample_instance(sample_instance);
   _paused = true;
   return *this;
}



Sound &Sound::unpause()
{
   validate_initialized("unpause");
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
   validate_initialized("stop");
   al_stop_sample_instance(sample_instance);
   position(0);
   return *this;
}



Sound &Sound::rewind()
{
   validate_initialized("rewind");
   position(0);
   return *this;
}



float Sound::volume()
{
   validate_initialized("volume");
   return al_get_sample_instance_gain(sample_instance);
}



Sound &Sound::volume(float vol)
{
   validate_initialized("volume");
   al_set_sample_instance_gain(sample_instance, vol);
   return *this;
}



double Sound::get_length_sec()
{
   validate_initialized("get_length_sec");
   return al_get_sample_instance_time(sample_instance);
}



double Sound::position()
{
   validate_initialized("position");
   if (is_paused()) return _position;

   _position = (float)al_get_sample_instance_position(sample_instance)
      / al_get_sample_instance_length(sample_instance)
      * al_get_sample_instance_time(sample_instance);

   return _position;
}



Sound &Sound::position(double time)
{
   validate_initialized("position");
   unsigned int pos = (unsigned int)(al_get_sample_instance_length(sample_instance)
         * (time / al_get_sample_instance_time(sample_instance)));
   al_set_sample_instance_position(sample_instance, pos);
   return *this;
}



bool Sound::is_playing()
{
   validate_initialized("is_playing");
   return al_get_sample_instance_playing(sample_instance);
}



Sound &Sound::pan(float pan)
{
   validate_initialized("pan");
   al_set_sample_instance_pan(sample_instance, pan);
   return *this;
}



float Sound::pan()
{
   validate_initialized("pan");
   return al_get_sample_instance_pan(sample_instance);
}



Sound &Sound::loop(bool yes)
{
   validate_initialized("loop");
   if (yes) al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
   else al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_ONCE);
   return *this;
}



Sound &Sound::bidir()
{
   validate_initialized("bidir");
   al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_BIDIR);
   return *this;
}



Sound &Sound::speed(float speed)
{
   validate_initialized("speed");
   al_set_sample_instance_speed(sample_instance, speed);
   return *this;
}



float Sound::speed()
{
   validate_initialized("speed");
   return al_get_sample_instance_speed(sample_instance);
}



} // AllegroFlare



