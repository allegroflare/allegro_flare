#pragma once




#include <allegro_flare/layout_loader_base.h>




namespace allegro_flare
{
   class GUIToolLayoutLoader : public UILayoutLoaderBase
   {
   public:
      GUIToolLayoutLoader(UIWidget *parent, std::string content);
      bool load_file();
   };
}



