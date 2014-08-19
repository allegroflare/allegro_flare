

#include <allegro_flare/drawing_interface.h>




DrawingInterface::DrawingInterface(std::string drawing_mode_name)
	: drawing_mode_name(drawing_mode_name)
{}



DrawingInterface::~DrawingInterface()
{}



std::string DrawingInterface::get_mode_name()
{
	return drawing_mode_name;
}




