

#include <AllegroFlare/DialogSystemDrivers/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystemDrivers
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


void Base::on_switch_in()
{
   return;
}

void Base::on_deactivate()
{
   // Rename this to "on_switch_out"
   return;
}

void Base::on_render()
{
   return;
}

bool Base::activate_dialog_node_by_name(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string active_dialog_node_name, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node, void* user_data)
{
   return false;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


