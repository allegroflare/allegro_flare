#ifndef __AF_WIN_CLIPBOARD_HEADER
#define __AF_WIN_CLIPBOARD_HEADER





#include <string>

class WinClipboard
{
public:
	static void set(std::string text);
	static std::string get();
};






#endif