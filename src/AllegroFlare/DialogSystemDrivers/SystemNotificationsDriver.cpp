

#include <AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystemDrivers
{


SystemNotificationsDriver::SystemNotificationsDriver()
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::TYPE)
{
}


SystemNotificationsDriver::~SystemNotificationsDriver()
{
}


bool SystemNotificationsDriver::load_node_bank_func(std::string filename, AllegroFlare::DialogTree::NodeBank* node_bank, void* user_data)
{
   if (!(node_bank))
   {
      std::stringstream error_message;
      error_message << "[SystemNotificationsDriver::load_node_bank_func]: error: guard \"node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SystemNotificationsDriver::load_node_bank_func: error: guard \"node_bank\" not met");
   }
   // TODO: Just fill this with some standard dialog nodes
   return true;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


