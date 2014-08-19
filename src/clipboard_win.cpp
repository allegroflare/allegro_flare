



#include <allegro_flare/clipboard_win.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_windows.h>
#include <iostream>



void WinClipboard::set(std::string text)
{
	if ( !OpenClipboard(NULL) )
	{
		//AfxMessageBox( _T("Cannot open the Clipboard") );
		std::cout << "WinClipboard.set(): Cannot open the Clipboard" << std::endl;
		return;
	}
	// Remove the current Clipboard contents 
	if( !EmptyClipboard() )
	{
		std::cout << "WinClipboard.set(): Cannot empty the Clipboard" << std::endl;
		return;
	}
	// Get the currently selected data
	//std::cout << "this is causing a crash somewhere: sizeof(text):" << sizeof(text) << " text.length():" << text.length();
	HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, text.size()+1);
	//strcpy_s((char*)hGlob, 64, text.c_str());
	if (!hGlob)
	{
		std::cout << "WinClipboard.set(): could not allocate hGlob" << std::endl;
		CloseClipboard();
		return;
	}

	memcpy(GlobalLock(hGlob),text.c_str(),text.size()+1);
	GlobalUnlock(hGlob);

	// For the appropriate data formats... 
	if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
	{
		std::cout << "WinClipboard.set(): Unable to set Clipboard data, error: " << GetLastError() << std::endl;
		//CString msg;
		//msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		//AfxMessageBox( msg );
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}




std::string WinClipboard::get()
{
	// Try opening the clipboard
	if (! OpenClipboard(NULL))
	{
		std::cout << "WinClipboard.get(): Cannot open the Clipboard" << std::endl;
		return "";
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == NULL) // NULL was nullptr, but was changed for compatability
	{
		std::cout << "WinClipboard.get(): Cannot get the clipboard handle" << std::endl;
		return "";
	}

	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>( GlobalLock(hData) );
	if (pszText == NULL) // NULL was nullptr, but was changed for compatability
	{
		std::cout << "WinClipboard.get(): Cannot lock the handle" << std::endl;
		return "";
	}

	// Save text in a string class instance
	std::string text( pszText );

	// Release the lock
	GlobalUnlock( hData );

	// Release the clipboard
	CloseClipboard();

	return text;
}


