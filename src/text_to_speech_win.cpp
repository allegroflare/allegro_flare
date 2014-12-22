

#include <allegro_flare/text_to_speech_win.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_windows.h>

#include <allegro_flare/useful.h>
#include <allegro_flare/useful_php.h>








Speaker::Speaker()
	: pVoice(NULL)
	, pStream(NULL)
	, hr(0)
	, status()
	, paused(false)
{
	if (FAILED(::CoInitialize(NULL)))
	{
		std::cout << "coinitialization failed." << std::endl;
		return;
	}

	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
}




Speaker::~Speaker()
{
	pVoice->Release();
	pVoice = NULL;
	::CoUninitialize();
}




void Speaker::speak_file(std::string filename)
{
	if (!php::file_exists(filename)) speak("I was asked to read this file, but I can't find it.");
	else speak(php::file_get_contents(filename));
}




static std::wstring __s2ws(const std::string& s)
{
	// converts a std::string to a LPCWSTR
	// *** usage: ***
	// std::wstring stemp = s2ws(myString);
	// LPCWSTR result = stemp.c_str();

    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}



void Speaker::speak(std::string text)
{
	_refresh_status();

	if(!SUCCEEDED(hr)) { std::cout << "can not speak. !SUCCEEDED(hr)" << std::endl; return; }
		
	//php::file_put_contents("data/temp/speech.txt", text);
	text_being_spoken.push_back(text);

	std::cout << "[speak] " << text << std::endl;

	hr = pVoice->Speak(__s2ws(text).c_str(), SPF_ASYNC, NULL);
}




void Speaker::pause()
{
	if (is_reading() && !paused)
	{
		hr = pVoice->Pause();
		paused = true;
	}
}




void Speaker::resume()
{
	if (paused)
	{
		hr = pVoice->Resume();
		paused = false;
	}
}




void Speaker::toggle_pause()
{
	if (paused)
	{
		resume();
	}
	else
	{
		pause();
	}
}




void Speaker::_refresh_status()
{
	pVoice->GetStatus(&status, NULL);
	if (status.dwRunningState == SPRS_DONE) text_being_spoken.clear();
}




bool Speaker::is_reading()
{
	_refresh_status();
	return status.dwRunningState == SPRS_IS_SPEAKING;
}




int Speaker::get_current_stream()
{
	_refresh_status();
	return (status.ulCurrentStream);
}



std::string Speaker::get_current_word()
{
	//_refresh_status();
	int text_index = get_current_stream()-1;
	// dirty dirty dirty... just makin it work

	std::string result = tostring(status.ulInputWordPos);
	result += "-" + tostring(status.ulInputWordLen);



	if (status.ulInputWordLen==0 || text_being_spoken.size()==0)
	{
		result = "...";
	}
	else if (text_being_spoken[text_index].length() >= (status.ulInputWordPos + status.ulInputWordLen))
	{
		result = text_being_spoken[text_index].substr(status.ulInputWordPos, status.ulInputWordLen);
	}
	return result;
}




Speaker::phoneme_t Speaker::get_current_phoneme()
{
	_refresh_status();
	return (phoneme_t)status.PhonemeId;
}




void Speaker::skip(int sentence_delta) // todo
{

}



bool Speaker::is_paused()
{
	return paused;
}



std::string Speaker::get_symbol(phoneme_t phoneme)
{
	switch (phoneme)
	{
		case 1: return "-"; break;
		case 2: return "!"; break;
		case 3: return "&"; break;
		case 4: return ","; break;
		case 5: return "."; break;
		case 6: return "?"; break;
		case 7: return "_"; break;
		case 8: return "1"; break;
		case 9: return "2"; break;
		case 10: return "aa"; break;
		case 11: return "ae"; break;
		case 12: return "ah"; break;
		case 13: return "ao"; break;
		case 14: return "aw"; break;
		case 15: return "ax"; break;
		case 16: return "ay"; break;
		case 17: return "b"; break;
		case 18: return "ch"; break;
		case 19: return "d"; break;
		case 20: return "dh"; break;
		case 21: return "eh"; break;
		case 22: return "er"; break;
		case 23: return "ey"; break;
		case 24: return "f"; break;
		case 25: return "g"; break;
		case 26: return "h"; break;
		case 27: return "ih"; break;
		case 28: return "iy"; break;
		case 29: return "jh"; break;
		case 30: return "k"; break;
		case 31: return "l"; break;
		case 32: return "m"; break;
		case 33: return "n"; break;
		case 34: return "ng"; break;
		case 35: return "ow"; break;
		case 36: return "oy"; break;
		case 37: return "p"; break;
		case 38: return "r"; break;
		case 39: return "s"; break;
		case 40: return "sh"; break;
		case 41: return "t"; break;
		case 42: return "th"; break;
		case 43: return "uh"; break;
		case 44: return "uw"; break;
		case 45: return "v"; break;
		case 46: return "w"; break;
		case 47: return "y"; break;
		case 48: return "z"; break;
		case 49: return "zh"; break;
		default: return "undef"; break;
	}
}




std::string Speaker::get_example(phoneme_t phoneme)
{
	switch (phoneme)
	{
		case 1: return "\"-\" as in syllable boundary (hyphen)"; break;
		case 2: return "\"!\" as in Sentence terminator (exclamation mark)"; break;
		case 3: return "\"&\" as in word boundary"; break;
		case 4: return "\",\" as in Sentence terminator (comma)"; break;
		case 5: return "\".\" as in Sentence terminator (period)"; break;
		case 6: return "\"?\" as in Sentence terminator (question mark)"; break;
		case 7: return "\"_\" as in Silence (underscore)"; break;
		case 8: return "\"1\" as in Primary stress"; break;
		case 9: return "\"2\" as in Secondary stress"; break;
		case 10: return "\"aa\" as in father"; break;
		case 11: return "\"ae\" as in cat"; break;
		case 12: return "\"ah\" as in cut"; break;
		case 13: return "\"ao\" as in dog"; break;
		case 14: return "\"aw\" as in foul"; break;
		case 15: return "\"ax\" as in ago"; break;
		case 16: return "\"ay\" as in bite"; break;
		case 17: return "\"b\" as in big"; break;
		case 18: return "\"ch\" as in chin"; break;
		case 19: return "\"d\" as in dig"; break;
		case 20: return "\"dh\" as in then"; break;
		case 21: return "\"eh\" as in pet"; break;
		case 22: return "\"er\" as in fur"; break;
		case 23: return "\"ey\" as in ate"; break;
		case 24: return "\"f\" as in fork"; break;
		case 25: return "\"g\" as in gut"; break;
		case 26: return "\"h\" as in help"; break;
		case 27: return "\"ih\" as in fill"; break;
		case 28: return "\"iy\" as in feel"; break;
		case 29: return "\"jh\" as in joy"; break;
		case 30: return "\"k\" as in cut"; break;
		case 31: return "\"l\" as in lid"; break;
		case 32: return "\"m\" as in mat"; break;
		case 33: return "\"n\" as in no"; break;
		case 34: return "\"ng\" as in sing"; break;
		case 35: return "\"ow\" as in go"; break;
		case 36: return "\"oy\" as in toy"; break;
		case 37: return "\"p\" as in put"; break;
		case 38: return "\"r\" as in red"; break;
		case 39: return "\"s\" as in sit"; break;
		case 40: return "\"sh\" as in she"; break;
		case 41: return "\"t\" as in talk"; break;
		case 42: return "\"th\" as in thin"; break;
		case 43: return "\"uh\" as in book"; break;
		case 44: return "\"uw\" as in too"; break;
		case 45: return "\"v\" as in vat"; break;
		case 46: return "\"w\" as in with"; break;
		case 47: return "\"y\" as in yard"; break;
		case 48: return "\"z\" as in zap"; break;
		case 49: return "\"zh\" as in pleasure"; break;
		default: return "undef"; break;
	}
}