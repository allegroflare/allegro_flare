

#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace Characters
{


Basic::Basic(std::string display_name)
   : AllegroFlare::DialogSystem::Characters::Base(AllegroFlare::DialogSystem::Characters::Basic::TYPE)
   , display_name(display_name)
   , feature_description("[unset-feature_description]")
   , avatar_thumbnail_identifier("[unset-avatar_thumbnail_identifier]")
   , avatar_portrait_identifier("[unset-avatar_portrait_identifier]")
   , expressions({})
{
}


Basic::~Basic()
{
}


void Basic::set_display_name(std::string display_name)
{
   this->display_name = display_name;
}


void Basic::set_feature_description(std::string feature_description)
{
   this->feature_description = feature_description;
}


void Basic::set_avatar_thumbnail_identifier(std::string avatar_thumbnail_identifier)
{
   this->avatar_thumbnail_identifier = avatar_thumbnail_identifier;
}


void Basic::set_avatar_portrait_identifier(std::string avatar_portrait_identifier)
{
   this->avatar_portrait_identifier = avatar_portrait_identifier;
}


void Basic::set_expressions(std::map<std::string, std::string> expressions)
{
   this->expressions = expressions;
}


std::string Basic::get_feature_description() const
{
   return feature_description;
}


std::string Basic::get_avatar_thumbnail_identifier() const
{
   return avatar_thumbnail_identifier;
}


std::string Basic::get_avatar_portrait_identifier() const
{
   return avatar_portrait_identifier;
}


std::map<std::string, std::string> Basic::get_expressions() const
{
   return expressions;
}


std::string Basic::get_display_name()
{
   return display_name;
}

void Basic::add_expression(std::string expression_name, std::string image_identifier)
{
   if (!((!expression_exists(expression_name))))
   {
      std::stringstream error_message;
      error_message << "[Basic::add_expression]: error: guard \"(!expression_exists(expression_name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::add_expression: error: guard \"(!expression_exists(expression_name))\" not met");
   }
   if (!((!image_identifier.empty())))
   {
      std::stringstream error_message;
      error_message << "[Basic::add_expression]: error: guard \"(!image_identifier.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::add_expression: error: guard \"(!image_identifier.empty())\" not met");
   }
   // TODO: Consider improving the error message if a node does not exist
   expressions[expression_name] = image_identifier;
   return;
}

void Basic::remove_expression(std::string expression_name)
{
   if (!((!expression_exists(expression_name))))
   {
      std::stringstream error_message;
      error_message << "[Basic::remove_expression]: error: guard \"(!expression_exists(expression_name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::remove_expression: error: guard \"(!expression_exists(expression_name))\" not met");
   }
   // TODO: Consider improving the error message if a node does not exist
   expressions.erase(expression_name);
   return;
}

void Basic::clear_expressions()
{
   expressions.clear();
}

bool Basic::expression_exists(std::string expression_name)
{
   return expressions.count(expression_name) != 0;
}

std::string Basic::find_expression(std::string expression_name)
{
   if (!expression_exists(expression_name)) return "";
   return expressions[expression_name];
}


} // namespace Characters
} // namespace DialogSystem
} // namespace AllegroFlare


