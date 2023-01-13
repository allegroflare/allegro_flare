

#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{


FilterMatrix::FilterMatrix()
   : matrix()
   , axis(std::make_pair(0, 0))
{
}


FilterMatrix::~FilterMatrix()
{
}


void FilterMatrix::resize(int width, int height)
{
   if (!((width > 1)))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::resize]: error: guard \"(width > 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::resize: error: guard \"(width > 1)\" not met");
   }
   if (!((height > 1)))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::resize]: error: guard \"(height > 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::resize: error: guard \"(height > 1)\" not met");
   }
   matrix.resize(height);
   for (auto &row : matrix)
   {
      row.resize(width, 0);
   }
   return;
}

int FilterMatrix::get_width() const
{
   if (matrix.empty()) return 0;
   return matrix[0].size();
}

int FilterMatrix::get_height() const
{
   return matrix.size();
}

void FilterMatrix::set_tile(int x, int y, int tile_value)
{
   if (!((x < get_width())))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::set_tile]: error: guard \"(x < get_width())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::set_tile: error: guard \"(x < get_width())\" not met");
   }
   if (!((y < get_height())))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::set_tile]: error: guard \"(y < get_height())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::set_tile: error: guard \"(y < get_height())\" not met");
   }
   if (!((x >= 0)))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::set_tile]: error: guard \"(x >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::set_tile: error: guard \"(x >= 0)\" not met");
   }
   if (!((y >= 0)))
   {
      std::stringstream error_message;
      error_message << "[FilterMatrix::set_tile]: error: guard \"(y >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FilterMatrix::set_tile: error: guard \"(y >= 0)\" not met");
   }
   matrix[y][x] = tile_value;
}


} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


