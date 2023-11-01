

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

void Base::on_deactivate()
{
   // Rename this to "on_switch_out"
   return;
}

void Base::on_render()
{
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


