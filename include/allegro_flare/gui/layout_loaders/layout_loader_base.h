#pragma once



#include <string>
#include <allegro_flare/gui/widget.h>




class UILayoutLoaderBase
{
private:
   UIWidget *parent;
   std::string filename;

public:
   UILayoutLoaderBase(UIWidget *parent, std::string filename);
   virtual ~UILayoutLoaderBase();

   virtual bool load_file() = 0;
};




