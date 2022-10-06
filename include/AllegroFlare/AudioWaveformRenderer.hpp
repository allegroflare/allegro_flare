#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>



namespace AllegroFlare
{
   class AudioWaveformRenderer
   {
   private:
      ALLEGRO_SAMPLE *sample;
      bool composite_stereo_render;

   public:
      AudioWaveformRenderer(ALLEGRO_SAMPLE *sample=nullptr);
      ~AudioWaveformRenderer();

      void draw_wav_sample(ALLEGRO_BITMAP *dest);
      void draw_wav_sample(ALLEGRO_BITMAP *dest, float samp_start, float samp_end);
      void draw_wav_sample(float x, float y, float width, float height, float samp_start, float samp_end);

   private:
      float get_max_f_sample_within(float pos_begin, float pos_end, int channel_num=0);
   };
} // AllegroFlare




