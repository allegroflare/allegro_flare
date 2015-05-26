

#include <allegro_flare/clipboard.h>




Clipboard::Clipboard()
	: __text()
{}



Clipboard *Clipboard::get_instance()
{
	if (!instance) instance = new Clipboard();
	return instance;
}



void Clipboard::set(std::string text)
{
	Clipboard::get_instance()->__text = text;
}



std::string Clipboard::get()
{
	return Clipboard::get_instance()->__text;
}



Clipboard *Clipboard::instance = NULL;



