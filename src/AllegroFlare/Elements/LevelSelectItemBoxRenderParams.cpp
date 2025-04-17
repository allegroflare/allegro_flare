

#include <AllegroFlare/Elements/LevelSelectItemBoxRenderParams.hpp>




namespace AllegroFlare
{
namespace Elements
{


LevelSelectItemBoxRenderParams::LevelSelectItemBoxRenderParams(std::string menu_item_identifier, std::string label, int row, int column, float x, float y, float width, float height, bool locked, bool completed)
   : menu_item_identifier(menu_item_identifier)
   , label(label)
   , row(row)
   , column(column)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , locked(locked)
   , completed(completed)
{
}


LevelSelectItemBoxRenderParams::~LevelSelectItemBoxRenderParams()
{
}




} // namespace Elements
} // namespace AllegroFlare


