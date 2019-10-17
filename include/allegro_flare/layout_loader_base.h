#pragma once



#include <string>
#include <allegro_flare/widget.h>




class UILayoutLoaderBase
{
protected:
   UIWidget *parent;
   std::string content;

public:
   UILayoutLoaderBase(UIWidget *parent, std::string content);
   virtual ~UILayoutLoaderBase();

   virtual bool load_file() = 0;
};




