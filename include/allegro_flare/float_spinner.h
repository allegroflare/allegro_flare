#ifndef __UI_FLOAT_SPINNER_HEADER
#define __UI_FLOAT_SPINNER_HEADER




#include <allegro_flare/spinner_base.h>




namespace allegro_flare
{
   class UIFloatSpinner : public UISpinnerBase
   {
   private:
      float val;
      float increment_amount;

   public:
      UIFloatSpinner(UIWidget *parent, float x, float y, float w, float h);

      void set_val(std::string strval) override;
      void set_increment(float increment_amount=0.1);
      void increment() override;
      void decrement() override;

      float get_val();
   };
}




#endif
