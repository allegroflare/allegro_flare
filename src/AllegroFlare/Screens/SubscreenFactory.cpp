

#include <AllegroFlare/Screens/SubscreenFactory.hpp>

#include <AllegroFlare/Screens/Subscreen/PaneFactory.hpp>


namespace AllegroFlare
{
namespace Screens
{


SubscreenFactory::SubscreenFactory()
{
}


SubscreenFactory::~SubscreenFactory()
{
}


AllegroFlare::Screens::Subscreen::Screen* SubscreenFactory::create_basic_subscreen()
{
   throw std::runtime_error("AllegroFlare::Screens::SubscreenFactory::create_basic_subscreen: "
      "This method is not developed");
   /*
   AllegroFlare::Screens::Subscreen::PaneFactory pane_factory;

   AllegroFlare::Screens::Subscreen::Screen *result = new AllegroFlare::Screens::Subscreen::Screen;

   AllegroFlare::Screens::Subscreen::Element *subscreen_element = new AllegroFlare::Screens::Subscreen::Element;
   subscreen_element->set_panes({
      pane_factory.create_inventory_pane()
   });

   // TODO: Setup the deps here
   //result->set_event_emitter(get_framework_event_emitter());
   //result->set_bitmap_bin(get_framework_bitmap_bin());
   //result->set_font_bin(get_framework_font_bin());
   result->set_subscreen_element(subscreen_element);
   //result->set_subscreen_element(
   return result;
   */
}


} // namespace Screens
} // namespace AllegroFlare


