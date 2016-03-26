#include <allegro_flare/render_sample.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
using namespace std;


bool do_cout = false;


/*
// this function returns a value between -1 and 1 of the sample located at pos
static float inline get_f_sample_at(ALLEGRO_SAMPLE *sample, float pos, int channel_num=0)
{
	if (!sample || (pos<0)) return 0;
	if (pos >= al_get_sample_length(sample)) return 0;

	//int *int16 = NULL;
	short *short_pointer = NULL;

	int sample_pos = pos;

	switch(al_get_sample_depth(sample))
	{
	case ALLEGRO_AUDIO_DEPTH_INT16:
		short_pointer = (short *)al_get_sample_data(sample);
		return short_pointer[sample_pos*2+channel_num] / (float)-32768 * 2;
		break;
	default:
		break;
	}

	return 0;
}
*/


// This function returns a positive value between 0 and 1 of the maximum value between the given ranges.
// Note that samples are normally in positive and negative values, this will return the max abs value.
// This function is not sample-acurate, but will return usable approximate results.
static float inline get_max_f_sample_within(ALLEGRO_SAMPLE *sample, float pos_begin, float pos_end, int channel_num=0)
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




// if true, will split stereo channels on a single line.
// if false, will split stereo channels into seperate lines.
static bool composite_stereo_render = true;


void draw_wav_sample(ALLEGRO_BITMAP *dest, ALLEGRO_SAMPLE *sample)
{
	if (!sample) return;
	draw_wav_sample(dest, sample, 0, al_get_sample_length(sample));
}


void draw_wav_sample(ALLEGRO_BITMAP *dest, ALLEGRO_SAMPLE *sample, float samp_start, float samp_end)
{
	if (!dest) { cout << "(!) Could not render sample: destination bitmap is invalid." << endl; return; }
	ALLEGRO_BITMAP *prev = al_get_target_bitmap();
	al_set_target_bitmap(dest);
	al_clear_to_color(al_color_name("black"));

	draw_wav_sample(1, 1, al_get_bitmap_width(dest)-1, al_get_bitmap_height(dest)-2, samp_start, samp_end, sample);

	al_set_target_bitmap(prev);
}


void draw_wav_sample(float x, float y, float width, float height, float samp_start, float samp_end, ALLEGRO_SAMPLE *sample)
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
		left_sample_y = get_max_f_sample_within(sample, target_sample_start, target_sample_end, 0) * signal_half_scale;
		al_draw_line(x+x_pos, center_y-left_sample_y+left_center_y, x+x_pos, center_y+left_sample_y+left_center_y, left_channel, 0.5f);

		//right_sample_y = get_f_sample_at(sample, target_sample, 1) * signal_half_scale;
		right_sample_y = get_max_f_sample_within(sample, target_sample_start, target_sample_end, 1) * signal_half_scale;
		al_draw_line(x+x_pos, center_y-right_sample_y+right_center_y, x+x_pos, center_y+right_sample_y+right_center_y, right_channel, 0.5f);
	}

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
