

#include <AllegroFlare/DialogSystemDrivers/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystemDrivers
{


Base::Base(std::string type)
   : type(type)
   , activate_dialog_node_type_unhandled_func()
   , activate_dialog_node_type_unhandled_func_user_data(nullptr)
{
}


Base::~Base()
{
}


void Base::set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func)
{
   this->activate_dialog_node_type_unhandled_func = activate_dialog_node_type_unhandled_func;
}


void Base::set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data)
{
   this->activate_dialog_node_type_unhandled_func_user_data = activate_dialog_node_type_unhandled_func_user_data;
}


std::string Base::get_type() const
{
   return type;
}


std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> Base::get_activate_dialog_node_type_unhandled_func() const
{
   return activate_dialog_node_type_unhandled_func;
}


void* Base::get_activate_dialog_node_type_unhandled_func_user_data() const
{
   return activate_dialog_node_type_unhandled_func_user_data;
}


void Base::on_switch_in()
{
   return;
}

void Base::on_switch_out()
{
   // Rename this to "on_switch_out"
   return;
}

void Base::on_render()
{
   return;
}

void Base::on_before_spawn_basic_dialog(std::string speaking_character_identifier)
{
   // TODO: This method, modify speaking character
   return;
}

void Base::on_before_spawn_choice_dialog(std::string speaking_character_identifier)
{
   // TODO: This method, modify speaking character
   return;
}

void Base::on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string activating_node_name, AllegroFlare::DialogTree::Nodes::Base* activating_node, void* user_data)
{
   // TODO: Consider renaming this for clarity
   // TODO: Consider if this method needs to be removed or modififed
   return;
}

void Base::on_raw_script_line_finished(AllegroFlare::DialogSystem::DialogSystem* dialog_system, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node)
{
   // TODO: Consider renaming this for clarity
   // TODO: Consider if this method needs to be removed or modififed
   return;
}

std::string Base::decorate_speaking_character_name(std::string speaking_character_identifier)
{
   return speaking_character_identifier;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


