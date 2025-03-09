

#include <AllegroFlare/SavingAndLoading/StandardSavesPath.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


StandardSavesPath::StandardSavesPath()
{
}


StandardSavesPath::~StandardSavesPath()
{
}


std::string StandardSavesPath::build_standard_path(std::string data_folder_path)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   return data_folder_path + "saves/";
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


