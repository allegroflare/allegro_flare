

#include <AllegroFlare/AudioWaveformRenderer.hpp>

#include <iostream>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>



namespace AllegroFlare
{



AudioWaveformRenderer::AudioWaveformRenderer(ALLEGRO_SAMPLE *sample)
   : sample(sample)
   , composite_stereo_render(true)
{
}



AudioWaveformRenderer::~AudioWaveformRenderer()
{
}



// This function returns a positive value between 0 and 1 of the maximum value between the given ranges.
// Note that samples are normally in positive and negative values, this will return the max abs value.
// This function is not sample-acurate, but will return usable approximate results.
float AudioWaveformRenderer::get_max_f_sample_within(float pos_begin, float pos_end, int channel_num)
{
   if (!sample || (pos_end<0) || (pos_begin >= al_get_sample_length(sample))) return 0;

   short *short_pointer = NULL;
   char *char_pointer = NULL;

   int sample_val = 0;
   int val;

   switch(al_get_sample_depth(sample))
   {
   case ALLEGRO_AUDIO_DEPTH_INT16:
      short_pointer = (short *)al_get_sample_data(sample);
      for (int i=pos_begin; i<pos_end; i++)
      {
         val = abs(short_pointer[i*2+channel_num]);
         if (val > sample_val) sample_val = val;
      }
      return sample_val / (float)32768 * 2;
      break;
   case ALLEGRO_AUDIO_DEPTH_INT8:
      char_pointer = (char *)al_get_sample_data(sample);
      for (int i=pos_begin; i<pos_end; i++)
      {
         val = abs(char_pointer[i*2+channel_num]);
         if (val > sample_val) sample_val = val;
      }
      return sample_val / (float)128 * 2;
      break;
   default:
      break;
   }

   return 0;
}




void AudioWaveformRenderer::draw_waveform(ALLEGRO_BITMAP *dest)
{
   if (!sample) return;
   draw_waveform(dest, 0, al_get_sample_length(sample));
}




void AudioWaveformRenderer::draw_waveform(ALLEGRO_BITMAP *dest, float samp_start, float samp_end)
{
   if (!dest) { std::cout << "(!) Could not render sample: destination bitmap is invalid." << std::endl; return; }
   ALLEGRO_BITMAP *prev = al_get_target_bitmap();
   al_set_target_bitmap(dest);
   al_clear_to_color(al_color_name("black"));

   draw_waveform(1, 1, al_get_bitmap_width(dest)-1, al_get_bitmap_height(dest)-2, samp_start, samp_end);

   al_set_target_bitmap(prev);
}




void AudioWaveformRenderer::draw_waveform(float x, float y, float width, float height, float samp_start, float samp_end)
{
   if (!sample) return;

   float center_y = y+height*0.5f;
   float half_h = height*0.5f;

   //al_draw_rectangle(x, y, x+width, y+height, al_color_name("orange"), 1.0f);
   if (composite_stereo_render)
   {
      al_draw_line(x, center_y, x+width, center_y, al_color_name("lightgreen"), 1.0f);
   }
   else
   {
      al_draw_line(x, center_y-half_h/2, x+width, center_y-half_h/2, al_color_name("lightgreen"), 1.0f);
      al_draw_line(x, center_y+half_h/2, x+width, center_y+half_h/2, al_color_name("lightgreen"), 1.0f);
   }

   //float scale = 0.05f;

   float num_samples_in_range = (samp_end - samp_start);

   al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
   //al_set_blender();

   ALLEGRO_COLOR color = al_color_name("lightblue");
   float alpha = 0.04;
   if (composite_stereo_render) alpha = 0.02;
   color.r *= alpha;
   color.g *= alpha;
   color.b *= alpha;
   color.a *= alpha;

   ALLEGRO_COLOR left_channel = color;
   ALLEGRO_COLOR right_channel = color;

   float x_pos=0;
   float left_sample_y = 0;
   float left_center_y = -half_h/2;
   float right_sample_y = 0;
   float right_center_y = half_h/2;
   float signal_half_scale = half_h*0.25f;

   if (composite_stereo_render)
   {
      left_center_y = right_center_y = 0;
      signal_half_scale *= 2;
   }

   x+=0.5f;
   float x_pos_increment = 0.01;
   // if this function strangely crashes, change the x_pos_increment to 1.0;
   //x_pos_increment = 1.0;
   for (; x_pos<=width; x_pos+=x_pos_increment)
   {
      //float target_sample = x_pos / width * num_samples_in_range + samp_start;
      float target_sample_start = x_pos / width * num_samples_in_range + samp_start;
      float target_sample_end = (x_pos+x_pos_increment) / width * num_samples_in_range + samp_start;

      //left_sample_y = get_f_sample_at(sample, target_sample, 0) * signal_half_scale;
      left_sample_y = get_max_f_sample_within(target_sample_start, target_sample_end, 0) * signal_half_scale;
      al_draw_line(x+x_pos, center_y-left_sample_y+left_center_y, x+x_pos, center_y+left_sample_y+left_center_y, left_channel, 0.5f);

      //right_sample_y = get_f_sample_at(sample, target_sample, 1) * signal_half_scale;
      right_sample_y = get_max_f_sample_within(target_sample_start, target_sample_end, 1) * signal_half_scale;
      al_draw_line(x+x_pos, center_y-right_sample_y+right_center_y, x+x_pos, center_y+right_sample_y+right_center_y, right_channel, 0.5f);
   }

   al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}




} // namespace AllegroFlare



