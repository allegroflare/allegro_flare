#include <thread>
//#include <mutext>

#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Timeline/Actor.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <AllegroFlare/Color.hpp>


ALLEGRO_FONT *icon_font = nullptr;


class MotionEdit : public AllegroFlare::Screens::Base
{
private:
   std::vector<AllegroFlare::Timeline::Actor*> actors;
public:
   MotionEdit()
      : AllegroFlare::Screens::Base()
   {}
   ~MotionEdit() {}

   virtual void primary_timer_func() override
   {
      for (auto &actor : actors)
      {
         //TrackView track_view(actor);
      }
   }
};



void framework_main()
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   icon_font = framework.get_font_bin_ref()[""];

   MotionEdit motion_edit;
   framework.register_screen("motion_edit", &motion_edit);
   framework.activate_screen("motion_edit");

   framework.run_loop();
}


void network_main()
{
   for (unsigned i=0; i<5; i++)
   {
      std::cout << "NETWORK_MAIN() count: " << i << std::endl;
      sleep(1);
   }
}



int main(int argc, char **argv)
{
   std::thread first(framework_main);
   std::thread second(network_main);

   first.join();
   second.join();

   std::cout << "executed_expectedly." << std::endl;
}



