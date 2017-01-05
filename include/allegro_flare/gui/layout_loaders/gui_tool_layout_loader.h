#pragma once




#include <allegro_flare/gui/layout_loaders/layout_loader_base.h>




class GUIToolLayoutLoader : public UILayoutLoaderBase
{
public:
   GUIToolLayoutLoader(UIWidget *parent, std::string filename);
   bool load_file();
};




