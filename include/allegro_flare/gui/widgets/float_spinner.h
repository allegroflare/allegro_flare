#ifndef __FGUI_FLOAT_SPINNER_HEADER
#define __FGUI_FLOAT_SPINNER_HEADER



#include <allegro_flare/gui/widgets/spinner.h>



class FGUIFloatSpinner : public FGUISpinner
{
private:
   float val;
   float increment_amount;

public:
   FGUIFloatSpinner(FGUIWidget *parent, float x, float y, float w, float h);

   void set_val(std::string strval) override;
   void set_increment(float increment_amount=0.1);
   void increment() override;
   void decrement() override;

   float get_val();
};





#endif

