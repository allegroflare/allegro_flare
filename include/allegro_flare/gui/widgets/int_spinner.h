#ifndef __FGUI_INT_SPINNER_HEADER
#define __FGUI_INT_SPINNER_HEADER



#include <allegro_flare/gui/widgets/spinner.h>



class FGUIIntSpinner : public FGUISpinner
{
private:
   int val;

public:
   FGUIIntSpinner(FGUIWidget *parent, float x, float y, float w, float h);

   void set_val(std::string strval) override;
   void increment() override;
   void decrement() override;

   int get_val();
};





#endif

