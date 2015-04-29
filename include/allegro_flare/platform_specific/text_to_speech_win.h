#ifndef __AF_WINSPEECH_HEADER
#define __AF_WINSPEECH_HEADER




//#include <allegro5/allegro_windows.h>
#include <string>
#include <vector>


//#ifdef _MSC_VER
//
//#else
//#define NOMINMAX
//#include <sapi.h>
#include <windows.h>
//#endif
//


class Speaker
{
private:
	SPVOICESTATUS status;
	ISpVoice *pVoice;
	ISpStream *pStream;
	HRESULT hr;
	std::vector<std::string> text_being_spoken;

	bool paused;

	void _refresh_status();
	int get_current_stream();

public:

	enum phoneme_t
	{
		PHONEME_NONE = 0,
		PHONEME_DASH = 1,
		PHONEME_EXCLAMATION_POINT = 2,
		PHONEME_AMPERSAND = 3,
		PHONEME_COMMA = 4,
		PHONEME_PERIOD = 5,
		PHONEME_QUESTION_MARK = 6,
		PHONEME_UNDERSCORE = 7,
		PHONEME_1 = 8,
		PHONEME_2 = 9,
		PHONEME_AA = 10,
		PHONEME_AE = 11,
		PHONEME_AH = 12,
		PHONEME_AO = 13,
		PHONEME_AW = 14,
		PHONEME_AX = 15,
		PHONEME_AY = 16,
		PHONEME_B = 17,
		PHONEME_CH = 18,
		PHONEME_D = 19,
		PHONEME_DH = 20,
		PHONEME_EH = 21,
		PHONEME_ER = 22,
		PHONEME_EY = 23,
		PHONEME_F = 24,
		PHONEME_G = 25,
		PHONEME_H = 26,
		PHONEME_IH = 27,
		PHONEME_IY = 28,
		PHONEME_JH = 29,
		PHONEME_K = 30,
		PHONEME_L = 31,
		PHONEME_M = 32,
		PHONEME_N = 33,
		PHONEME_NG = 34,
		PHONEME_OW = 35,
		PHONEME_OY = 36,
		PHONEME_P = 37,
		PHONEME_R = 38,
		PHONEME_S = 39,
		PHONEME_SH = 40,
		PHONEME_T = 41,
		PHONEME_TH = 42,
		PHONEME_UH = 43,
		PHONEME_UW = 44,
		PHONEME_V = 45,
		PHONEME_W = 46,
		PHONEME_Y = 47,
		PHONEME_Z = 48,
		PHONEME_ZH = 49
	};

	Speaker();
	~Speaker();

	void speak(std::string text);
	void speak_file(std::string filename);
	void pause();
	void resume();
	void toggle_pause();
	void skip(int sentence_delta); //todo
	bool is_paused();
	
	bool is_reading(); // is reading, pause, and resume don't operate correctly yet.  The underlying api needs to be worked out

	std::string get_current_word(); //todo
	phoneme_t get_current_phoneme();

	static std::string get_symbol(phoneme_t phoneme);
	static std::string get_example(phoneme_t phoneme);
};







#endif