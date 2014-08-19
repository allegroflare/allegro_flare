#ifndef __AF_AGENT_HEADER
#define __AF_AGENT_HEADER






#include <allegro_flare/text_to_speech_win.h>
#include <allegro_flare/screen.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/motion.h>

#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/bins/bitmap_bin.h>



/*

SpeakingAgent is dependent on some images, among other things

*/



class SpeakingAgent : public Speaker, public Screen, public placement2d
{
protected:
	Motion motion;
	BitmapBin bitmaps;
	FontBin fonts;
	bool mouse_over;
	double blink_counter;

	void primary_timer_func() override;

	ALLEGRO_BITMAP *_get_phoneme_image(Speaker::phoneme_t phoneme);

	void draw();

	void mouse_axes_func();

	void on_click();

	void mouse_down_func() override;

	virtual void receive_signal(std::string const &message, void *data);

public:
	SpeakingAgent(Display *display=NULL);
};





#endif