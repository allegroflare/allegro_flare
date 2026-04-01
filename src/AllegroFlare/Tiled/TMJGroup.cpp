

#include <AllegroFlare/Tiled/TMJGroup.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Tiled
{


TMJGroup::TMJGroup()
   : id(0)
   , name("[unset-name]")
   , offset_x(0.0f)
   , offset_y(0.0f)
   , opacity(1.0f)
   , num_rows(-1)
   , num_columns(-1)
   , tilelayers_tile_data({})
   , objects({})
{
}


TMJGroup::~TMJGroup()
{
}


void TMJGroup::for_each_object(std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function, void* user_data)
{
   for (auto &object : objects)
   {
      function(&object, user_data);
   }
   return;
}

std::vector<int> TMJGroup::get_tilelayer_data_by_name(std::string tilelayer_name)
{
   if (!(tilelayer_exists(tilelayer_name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name]: error: guard \"tilelayer_exists(tilelayer_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name]: error: guard \"tilelayer_exists(tilelayer_name)\" not met");
   }
   // TODO: Test this
   // TODO: Test guards
   // TODO: Improve non-existent layer name error message
   return tilelayers_tile_data[tilelayer_name];
}

std::vector<std::vector<int>> TMJGroup::get_tilelayer_data_by_name_as_2d_vector(std::string tilelayer_name)
{
   if (!(tilelayer_exists(tilelayer_name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"tilelayer_exists(tilelayer_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"tilelayer_exists(tilelayer_name)\" not met");
   }
   if (!((num_rows >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"(num_rows >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"(num_rows >= 1)\" not met");
   }
   if (!((num_columns >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"(num_columns >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJGroup::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"(num_columns >= 1)\" not met");
   }
   // TODO: Test this
   // TODO: Test guards
   // TODO: Improve non-existent layer name error message
   std::vector<std::vector<int>> result;
   std::vector<int> &tilelayer_data = tilelayers_tile_data[tilelayer_name];
   for (int y=0; y<num_rows; y++)
   {
      result.push_back(std::vector<int>(num_columns));

      for (int x=0; x<num_columns; x++)
      {
         result.back()[x] = tilelayer_data[x + y * num_columns];
      }
   }
   return result;
}

bool TMJGroup::tilelayer_exists(std::string tilelayer_name)
{
   return tilelayers_tile_data.find(tilelayer_name) != tilelayers_tile_data.end();
}


} // namespace Tiled
} // namespace AllegroFlare


