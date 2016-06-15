#ifndef __AF_BALSAMIQ_LAYOUT_LOADER_HEADER
#define __AF_BALSAMIQ_LAYOUT_LOADER_HEADER




#include <allegro_flare/gui/layout_loader_base.h>




class BalsamiqLayoutLoader : public UILayoutLoaderBase
{
public:
   UIWidget *load_file(std::string filename) override;
};




#endif
