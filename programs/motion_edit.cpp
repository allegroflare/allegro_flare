#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>



class MotionEdit : public AllegroFlare::Screens::Base
{
public:
   MotionEdit()
      : AllegroFlare::Screens::Base()
   {}
   ~MotionEdit() {}

   virtual void primary_timer_func() override
   {
   }
};



int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   MotionEdit motion_edit;
   framework.register_screen("motion_edit", &motion_edit);
   framework.activate_screen("motion_edit");

   framework.run_loop();
}



