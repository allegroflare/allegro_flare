#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>



namespace AllegroFlare
{
   class AudioWaveformRenderer
   {
   private:
      ALLEGRO_SAMPLE *sample;
      bool split_stereo_render;

   public:
      AudioWaveformRenderer(ALLEGRO_SAMPLE *sample=nullptr);
      ~AudioWaveformRenderer();

      void set_split_stereo_render(bool split_stereo_render=false);
      bool get_split_stereo_render() const;

      void draw_waveform(ALLEGRO_BITMAP *dest);
      void draw_waveform(ALLEGRO_BITMAP *dest, float samp_start, float samp_end);
      void draw_waveform(float x, float y, float width, float height, float samp_start, float samp_end);

   private:
      float get_max_f_sample_within(float pos_begin, float pos_end, int channel_num=0);
   };
} // AllegroFlare




