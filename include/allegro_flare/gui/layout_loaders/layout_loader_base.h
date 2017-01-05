#pragma once



#include <string>
#include <allegro_flare/gui/widget.h>




class UILayoutLoaderBase
{
private:
   UIWidget *parent;
   std::string content;

public:
   UILayoutLoaderBase(UIWidget *parent, std::string content);
   virtual ~UILayoutLoaderBase();

   virtual bool load_file() = 0;
};




