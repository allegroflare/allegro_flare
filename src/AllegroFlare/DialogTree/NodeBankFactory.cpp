

#include <AllegroFlare/DialogTree/NodeBankFactory.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>


namespace AllegroFlare
{
namespace DialogTree
{


NodeBankFactory::NodeBankFactory()
{
}


NodeBankFactory::~NodeBankFactory()
{
}


AllegroFlare::DialogTree::NodeBank NodeBankFactory::build_common_system_dialogs_node_bank()
{
   // TODO: Find out where to place constants
   AllegroFlare::DialogTree::NodeBank node_bank;

   node_bank.add_node(
         "wait_before_exit_program",
         new AllegroFlare::DialogTree::Nodes::Wait(1.0, "exit_program")
      );
   node_bank.add_node("exit_program", new AllegroFlare::DialogTree::Nodes::ExitProgram());
   node_bank.add_node(
         "confirm_exit_program",
         new AllegroFlare::DialogTree::Nodes::MultipageWithOptions
         (
            "system",
            { "Are you sure you want to exit?" },
            { 
               //{ "Yes", new AllegroFlare::DialogTree::NodeOptions::GoToNode("exit_program") },
               { "Yes", new AllegroFlare::DialogTree::NodeOptions::GoToNode("wait_before_exit_program") },
               { "No",  new AllegroFlare::DialogTree::NodeOptions::ExitDialog() },
            }
         )
      );

   return node_bank;
}


} // namespace DialogTree
} // namespace AllegroFlare


