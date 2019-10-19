

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Clipboard
#include <boost/test/unit_test.hpp>




#include <allegro_flare/gui_tool_layout_loader.h>
#include <allegro_flare/box.h>
#include <iostream>
#include <fstream>




using namespace allegro_flare;




std::string layout_content = R"CONTENT({"widgets":[{"name":"widget1","position.x":374,"position.y":491,"size.x":222,"size.y":230,"align.x":0.25,"align.y":0.62,"scale.x":1.20685,"scale.y":-1.20685,"rotation":130},{"name":"widget2","position.x":433,"position.y":862,"size.x":136,"size.y":136,"align.x":0.25,"align.y":0.62,"scale.x":-0.673549,"scale.y":0.673549,"rotation":-135},{"name":"widget3","position.x":151,"position.y":333,"size.x":204,"size.y":200,"align.x":0.25,"align.y":0.62,"scale.x":0.940549,"scale.y":-0.940549,"rotation":138},{"name":"widget4","position.x":343,"position.y":414,"size.x":256,"size.y":220,"align.x":0.25,"align.y":0.62,"scale.x":0.718278,"scale.y":-0.718278,"rotation":156}]})CONTENT";




BOOST_AUTO_TEST_CASE(adds_the_expected_number_of_children_to_the_parent)
{
   UIWidget *parent = new UIWidget(nullptr, "UIWidget", new UISurfaceAreaBox(0, 0, 300, 200));

   GUIToolLayoutLoader layout_loader(parent, layout_content);
   layout_loader.load_file();

   BOOST_CHECK_EQUAL(4, parent->num_descendants());
}




