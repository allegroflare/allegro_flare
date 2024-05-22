

#include <AllegroFlare/Screens/Subscreen/PaneFactory.hpp>

#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{


PaneFactory::PaneFactory()
{
}


PaneFactory::~PaneFactory()
{
}


void PaneFactory::create_inventory_pane()
{
   throw std::runtime_error("AllegroFlare::Screens::Subscreen::PaneFactory::create_inventory_pane: "
      "This method is not developed");
   /*
   AllegroFlare::Screens::Subscreen::Panes::Inventory *result =
      new AllegroFlare::Screens::Subscreen::Panes::Inventory;
   // TODO: Setup the result
   return result;
   */
}


} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


