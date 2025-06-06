

#include <AllegroFlare/Elements/LevelSelectItemBoxRenderParams.hpp>




namespace AllegroFlare
{
namespace Elements
{


LevelSelectItemBoxRenderParams::LevelSelectItemBoxRenderParams(int list_item_num_0_indexed, std::string identifier, std::string label, int row, int column, float x, float y, float width, float height, bool locked, bool completed)
   : list_item_num_0_indexed(list_item_num_0_indexed)
   , identifier(identifier)
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


