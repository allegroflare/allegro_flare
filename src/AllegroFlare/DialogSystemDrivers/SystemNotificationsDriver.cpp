

#include <AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
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


bool SystemNotificationsDriver::load_node_bank_func(std::string filename, AllegroFlare::DialogTree::NodeBank* node_bank_to_fill, void* user_data)
{
   if (!(node_bank_to_fill))
   {
      std::stringstream error_message;
      error_message << "[SystemNotificationsDriver::load_node_bank_func]: error: guard \"node_bank_to_fill\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SystemNotificationsDriver::load_node_bank_func: error: guard \"node_bank_to_fill\" not met");
   }
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node("wait_before_exit_program", new AllegroFlare::DialogTree::Nodes::Wait(1.0, "exit_program"));
   node_bank.add_node("exit_program", new AllegroFlare::DialogTree::Nodes::ExitProgram());
   node_bank.add_node(
      "confirm_exit_program",
      new AllegroFlare::DialogTree::Nodes::MultipageWithOptions
         (
            "system",
            { "Are you sure you want to exit?" },
            { 
               { "Yes", new AllegroFlare::DialogTree::NodeOptions::GoToNode("wait_before_exit_program") },
               { "No",  new AllegroFlare::DialogTree::NodeOptions::ExitDialog() },
            }
         )
      );

   *node_bank_to_fill = node_bank;
   return true;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


