

#include <AllegroFlare/Screens/Subscreen/PaneFactory.hpp>




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


AllegroFlare::Screens::Subscreen::Panes::Inventory* PaneFactory::create_inventory_pane()
{
   AllegroFlare::Screens::Subscreen::Panes::Inventory *result =
      new AllegroFlare::Screens::Subscreen::Panes::Inventory;
   // TODO: Setup the result
   return result;
}


} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


