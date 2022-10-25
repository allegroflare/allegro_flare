

#include <AllegroFlare/InventoryDictionaryItems/WithAttributes.hpp>




namespace AllegroFlare
{
namespace InventoryDictionaryItems
{


WithAttributes::WithAttributes(std::string property)
   : AllegroFlare::InventoryDictionaryItems::Base(AllegroFlare::InventoryDictionaryItems::WithAttributes::TYPE)
   , property(property)
{
}


WithAttributes::~WithAttributes()
{
}


std::string WithAttributes::get_property() const
{
   return property;
}


bool WithAttributes::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace InventoryDictionaryItems
} // namespace AllegroFlare


