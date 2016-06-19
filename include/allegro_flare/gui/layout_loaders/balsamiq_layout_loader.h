#ifndef __AF_BALSAMIQ_LAYOUT_LOADER_HEADER
#define __AF_BALSAMIQ_LAYOUT_LOADER_HEADER




#include <allegro_flare/gui/layout_loader_base.h>
#include <allegro_flare/gui/widget.h>




class BalsamiqLayoutLoader : public UILayoutLoaderBase
{
private:
   std::string version;

public:
   bool load_file(UIWidget *parent, std::string filename) override;
   std::string get_version();
};




#endif
