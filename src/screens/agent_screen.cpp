#include <allegro_flare/screens/agent_screen.h>


#include <allegro_flare/allegro_flare.h>



SpeakingAgent::SpeakingAgent(Display *display)
	: Speaker()
	, Screen(display)
	, placement2d()
	, motion()
	, fonts()
	, mouse_over(false)
	, blink_counter(5)
{
	position.x = 200;
	position.y = 300;
	size.x = 115;
	size.y = 115;
}





void SpeakingAgent::primary_timer_func()
{
	draw();
	//draw_box(color::yellow, true);
}





ALLEGRO_BITMAP *SpeakingAgent::_get_phoneme_image(Speaker::phoneme_t phoneme)
{
	switch(phoneme)
	{
	case Speaker::PHONEME_L:
		return bitmaps["mouth_shapes/L.png"];
		break;

	case Speaker::PHONEME_AA:
	case Speaker::PHONEME_AE:
	case Speaker::PHONEME_AH:
	case Speaker::PHONEME_EY:
		return bitmaps["mouth_shapes/ah.png"];
		break;

	case Speaker::PHONEME_B:
	case Speaker::PHONEME_P:
	case Speaker::PHONEME_M:
		return bitmaps["mouth_shapes/b_m_p.png"];
		break;

	case Speaker::PHONEME_D:
	case Speaker::PHONEME_Y:
	case Speaker::PHONEME_Z:
	case Speaker::PHONEME_T:
	case Speaker::PHONEME_S:
	case Speaker::PHONEME_NG:
	case Speaker::PHONEME_N:
	case Speaker::PHONEME_K:
	case Speaker::PHONEME_G:
		return bitmaps["mouth_shapes/c_d_g_k_n_s_t_x_y_z.png"];
		break;

	case Speaker::PHONEME_CH:
	case Speaker::PHONEME_JH:
	case Speaker::PHONEME_ZH:
	case Speaker::PHONEME_SH:
		return bitmaps["mouth_shapes/ch_j_sh.png"];
		break;

	case Speaker::PHONEME_AY:
	case Speaker::PHONEME_IY:
	case Speaker::PHONEME_IH:
	case Speaker::PHONEME_H:
	case Speaker::PHONEME_EH:
		return bitmaps["mouth_shapes/ee.png"];
		break;

	case Speaker::PHONEME_F:
	case Speaker::PHONEME_V:
		return bitmaps["mouth_shapes/f_v.png"];
		break;
		 
	case Speaker::PHONEME_AO:
	case Speaker::PHONEME_AW:
	case Speaker::PHONEME_AX:
	case Speaker::PHONEME_OY:
	case Speaker::PHONEME_OW:
		return bitmaps["mouth_shapes/o.png"];
		break;

	case Speaker::PHONEME_UW:
	case Speaker::PHONEME_UH:
		return bitmaps["mouth_shapes/oo.png"];
		break;

	case Speaker::PHONEME_R:
	case Speaker::PHONEME_ER:
		return bitmaps["mouth_shapes/r.png"];
		break;

	case Speaker::PHONEME_TH:
	case Speaker::PHONEME_DH:
		return bitmaps["mouth_shapes/th.png"];
		break;

	case Speaker::PHONEME_W:
		return bitmaps["mouth_shapes/w_q.png"];
		break;

	case Speaker::PHONEME_NONE:
	case Speaker::PHONEME_DASH:
	case Speaker::PHONEME_EXCLAMATION_POINT:
	case Speaker::PHONEME_AMPERSAND:
	case Speaker::PHONEME_COMMA:
	case Speaker::PHONEME_PERIOD:
	case Speaker::PHONEME_QUESTION_MARK:
	case Speaker::PHONEME_UNDERSCORE:
	case Speaker::PHONEME_1:
	case Speaker::PHONEME_2:
	default:
		return bitmaps["mouth_shapes/none.png"];
		break;
	}
}





void SpeakingAgent::draw()
{
	// store state
	placement2d::start_transform();


	// background
	al_draw_filled_rectangle(0, 0, size.x, size.y, color::hex("319cff"));


	// mouth
	ALLEGRO_BITMAP *mouth_shape = _get_phoneme_image(Speaker::get_current_phoneme());
	if (mouth_shape) al_draw_bitmap(mouth_shape, 0, 10, NULL);


	// eyes
	float eye_y = size.y/4;
	float eye_r = 2.3;
	float eye_1x = size.x/4;
	float eye_2x = size.x/4 * 3;
	if (blink_counter < 0.1)
	{
		al_draw_line(eye_1x-eye_r*2, eye_y, eye_1x+eye_r*2, eye_y, color::black, eye_r);
		al_draw_line(eye_2x-eye_r*2, eye_y, eye_2x+eye_r*2, eye_y, color::black, eye_r);
		if (blink_counter < 0.0) blink_counter = random_double(2.0, 6.0);
	}
	else
	{
		al_draw_filled_circle(eye_1x, eye_y, eye_r, color::black);
		al_draw_filled_circle(eye_2x, eye_y, eye_r, color::black);
	}
	blink_counter -= 1.0/60;


	// words
	float bx = size.x+size.x/4;
	float by = -size.y/3;
	float bw = size.x*2.5;
	float bh = size.y*0.8;
	float border_radius = 7;
	al_draw_filled_rounded_rectangle(bx, by, bx+bw, by+bh, border_radius, border_radius, color::white);
	float tx = bx+border_radius*4;
	float ty = by+bh-1;
	float ts = 20;
	al_draw_filled_triangle(tx, ty, tx+ts, ty, tx, ty+ts, color::white);
	std::string word = Speaker::get_current_word();
	ALLEGRO_FONT *font = fonts["lacuna.ttf 26"];
	if (is_paused()) word = "[PAUSED]";
	if (font) al_draw_text(font, color::black, bx+bw/2, by+bh/2-al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTRE, word.c_str());


	// show stream #
	//al_draw_text(font, color::white, 0, 0, NULL, tostring(voice->get_current_stream()).c_str());


	// restore state
	placement2d::restore_transform();

	//draw_crosshair(x, y, color::white);
}





void SpeakingAgent::mouse_axes_func()
{
	if (collide(af::current_event->mouse.x, af::current_event->mouse.y))
		mouse_over = true;
	else mouse_over = false;
}





void SpeakingAgent::on_click()
{
	toggle_pause();
}





void SpeakingAgent::mouse_down_func()
{
	if (mouse_over) on_click();
}





void SpeakingAgent::receive_signal(std::string const &message, void *data)
{
	if (message == "speak") speak(*static_cast<std::string *>(data));
}