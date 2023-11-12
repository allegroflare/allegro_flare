

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace CharacterStagingLayouts
{


Dynamic::Dynamic(AllegroFlare::BitmapBin* bitmap_bin)
   : AllegroFlare::DialogSystem::CharacterStagingLayouts::Base(AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE)
   , bitmap_bin(bitmap_bin)
   , staged_characters()
   , staged_character_expressions_db()
   , surface_width(1920)
   , surface_height(1080)
   , hidden(false)
{
}


Dynamic::~Dynamic()
{
}


void Dynamic::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Dynamic::set_staged_characters(std::vector<std::pair<std::string, AllegroFlare::DialogSystem::StagedCharacter::Dynamic>> staged_characters)
{
   this->staged_characters = staged_characters;
}


void Dynamic::set_staged_character_expressions_db(std::map<std::pair<std::string, std::string>, std::string> staged_character_expressions_db)
{
   this->staged_character_expressions_db = staged_character_expressions_db;
}


void Dynamic::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void Dynamic::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


AllegroFlare::BitmapBin* Dynamic::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::vector<std::pair<std::string, AllegroFlare::DialogSystem::StagedCharacter::Dynamic>> Dynamic::get_staged_characters() const
{
   return staged_characters;
}


std::map<std::pair<std::string, std::string>, std::string> Dynamic::get_staged_character_expressions_db() const
{
   return staged_character_expressions_db;
}


int Dynamic::get_surface_width() const
{
   return surface_width;
}


int Dynamic::get_surface_height() const
{
   return surface_height;
}


bool Dynamic::get_hidden() const
{
   return hidden;
}


void Dynamic::update(float time_now)
{
   for (auto &staged_character : staged_characters)
   {
      staged_character.second.update();
   }

   // NOTE: Nothing to be done here at this time
   return;
}

void Dynamic::show(float time_now)
{
   hidden = false;
   return;
}

void Dynamic::hide(float time_now)
{
   hidden = true; // TODO: Consider more elegant alternative to this "hard stop" on rendering
   return;
}

void Dynamic::clear()
{
   staged_characters.clear();
   return;
}

int Dynamic::num_staged_characters()
{
   return staged_characters.size();
}

bool Dynamic::staged_character_exists(std::string staged_character_identifier)
{
   return (find_staged_character(staged_character_identifier) != nullptr);
}

AllegroFlare::DialogSystem::StagedCharacter::Dynamic* Dynamic::find_staged_character(std::string staged_character_identifier)
{
   for (auto &staged_character : staged_characters)
   {
      if (staged_character.first == staged_character_identifier) return &staged_character.second;
   }
   return nullptr;
}

bool Dynamic::staged_character_expression_exists(std::string staged_character_identifier, std::string expression)
{
   std::string _default = "[unfound-staged_character_expression_bitmap_identifier]";
   return find_staged_character_expression_bitmap_identifier(staged_character_identifier, expression) != _default;
}

std::string Dynamic::find_staged_character_expression_bitmap_identifier(std::string staged_character_identifier, std::string expression)
{
   if (staged_character_expressions_db.count(std::make_pair(staged_character_identifier, expression)) == 0)
      return "[unfound-staged_character_expression_bitmap_identifier]";
   return staged_character_expressions_db[std::make_pair(staged_character_identifier, expression)];
}

void Dynamic::add_staged_character(std::string staged_character_identifier, AllegroFlare::DialogSystem::StagedCharacter::Dynamic staged_character)
{
   if (!((!staged_character_exists(staged_character_identifier))))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::add_staged_character]: error: guard \"(!staged_character_exists(staged_character_identifier))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::add_staged_character: error: guard \"(!staged_character_exists(staged_character_identifier))\" not met");
   }
   staged_characters.push_back({ staged_character_identifier, staged_character });
   return;
}

void Dynamic::set_staged_character_expression(std::string staged_character_identifier, std::string expression, float time_now)
{
   if (!staged_character_exists(staged_character_identifier))
   {
      std::stringstream error_message;
      error_message << "Possible names include [";
      for (auto &staged_character : staged_characters)
      {
         error_message << "\"" << staged_character.first << "\", ";
      }
      error_message << "]";
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::set_staged_character_expression",
         "staged_character with identifier \"" + staged_character_identifier + "\" does not exist. "
            + error_message.str()
      );
   }
   find_staged_character(staged_character_identifier)->set_expression(expression);
   // TODO: Assign bitmap here?
   return;
}

void Dynamic::set_staged_character_placement(std::string staged_character_identifier, AllegroFlare::Placement3D placement)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::set_staged_character_placement]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::set_staged_character_placement: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   find_staged_character(staged_character_identifier)->set_placement(placement);
   return;
}

void Dynamic::move_staged_character_to_front(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::move_staged_character_to_front]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::move_staged_character_to_front: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   // TODO
   return;
}

void Dynamic::move_staged_character_to_back(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::move_staged_character_to_back]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::move_staged_character_to_back: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   // TODO
   return;
}

void Dynamic::move_staged_character_forward(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::move_staged_character_forward]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::move_staged_character_forward: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   // TODO
   return;
}

void Dynamic::move_staged_character_backward(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::move_staged_character_backward]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::move_staged_character_backward: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   // TODO
   return;
}

void Dynamic::hide_characters_not_of(std::string staged_character_identifier)
{
   // TODO: Modify the passed in value to be a list
   for (auto &staged_character : staged_characters)
   {
      if (staged_character.first == staged_character_identifier) continue;
      find_staged_character(staged_character_identifier)->hide();
   }
   return;
}

void Dynamic::show_character(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::show_character]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::show_character: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   find_staged_character(staged_character_identifier)->show();
   return;
}

void Dynamic::hide_character(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::hide_character]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::hide_character: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   find_staged_character(staged_character_identifier)->hide();
   return;
}

void Dynamic::enter_character(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::enter_character]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::enter_character: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   find_staged_character(staged_character_identifier)->enter();
   return;
}

void Dynamic::exit_character(std::string staged_character_identifier)
{
   if (!(staged_character_exists(staged_character_identifier)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::exit_character]: error: guard \"staged_character_exists(staged_character_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::exit_character: error: guard \"staged_character_exists(staged_character_identifier)\" not met");
   }
   find_staged_character(staged_character_identifier)->exit();
   return;
}

void Dynamic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::render: error: guard \"bitmap_bin\" not met");
   }
   if (hidden) return;

   for (int i=staged_characters.size()-1; i>=0; i--)
   //for (auto &staged_character : staged_characters)
   {
      auto &staged_character = staged_characters[i];
      std::string bitmap_identifier = staged_character.second.get_expression();

      // TODO: Note somewhere that an empty db will default to use the "expression" as the bitmap identifier
      if (!staged_character_expressions_db.empty())
      {
         std::string character_identifier = staged_character.first;
         //std::string character_expression = staged_character.second.expression);
         bitmap_identifier = find_staged_character_expression_bitmap_identifier(
            character_identifier,
            bitmap_identifier
         );
      }

      ALLEGRO_BITMAP *bitmap = bitmap_bin->auto_get(bitmap_identifier);
      if (!bitmap) continue;

      
      staged_character.second.set_expression_bitmap(bitmap);
      staged_character.second.render();

      //AllegroFlare::Placement3D placement = staged_character.second.get_placement();
      //float opacity = staged_character.second.get_opacity();
      //AllegroFlare::Placement2D character_bitmap_placement_transform(
         //surface_width * 0.5,
         //surface_height * 1.0,
         //al_get_bitmap_width(bitmap),
         //al_get_bitmap_height(bitmap)
      //);
      //character_bitmap_placement_transform.scale_to_fit_height(surface_height * 2);
      //placement.start_transform();
      //ALLEGRO_COLOR tint{1.0, 1.0, 1.0, 1.0}; // TODO: Use motion effects for introducing different characters
      //al_draw_tinted_bitmap(bitmap, tint, 0, 0, 0);
      //placement.restore_transform();
   }
   return;
}

void Dynamic::set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap, float time_now)
{
   // TODO: Test this method
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::set_speaking_character_bitmap",
      "This method is not implemented in this derived class"
   );

   //if (speaking_character_bitmap == this->speaking_character_bitmap) return;
   //this->speaking_character_bitmap = speaking_character_bitmap;
   //speaking_character_bitmap_changed_at = time_now;
   return;
}


} // namespace CharacterStagingLayouts
} // namespace DialogSystem
} // namespace AllegroFlare


