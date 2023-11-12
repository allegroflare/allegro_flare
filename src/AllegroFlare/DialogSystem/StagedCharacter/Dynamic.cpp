

#include <AllegroFlare/DialogSystem/StagedCharacter/Dynamic.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace StagedCharacter
{


Dynamic::Dynamic(std::string expression, AllegroFlare::Placement3D placement)
   : expression(expression)
   , placement(placement)
   , expression_bitmap(nullptr)
   , opacity(1.0f)
   , state(STATE_NORMAL)
   , state_is_busy(false)
   , state_changed_at(0.0f)
{
}


Dynamic::~Dynamic()
{
}


void Dynamic::set_expression(std::string expression)
{
   this->expression = expression;
}


void Dynamic::set_placement(AllegroFlare::Placement3D placement)
{
   this->placement = placement;
}


void Dynamic::set_expression_bitmap(ALLEGRO_BITMAP* expression_bitmap)
{
   this->expression_bitmap = expression_bitmap;
}


void Dynamic::set_opacity(float opacity)
{
   this->opacity = opacity;
}


std::string Dynamic::get_expression() const
{
   return expression;
}


AllegroFlare::Placement3D Dynamic::get_placement() const
{
   return placement;
}


ALLEGRO_BITMAP* Dynamic::get_expression_bitmap() const
{
   return expression_bitmap;
}


float Dynamic::get_opacity() const
{
   return opacity;
}


void Dynamic::update()
{
   update_state();
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
   if (!expression_bitmap) return;
   {
      placement.start_transform();
      ALLEGRO_COLOR tint{opacity, opacity, opacity, opacity};
      al_draw_tinted_bitmap(expression_bitmap, tint, 0, 0, 0);
      placement.restore_transform();
   }
   return;
}

void Dynamic::enter()
{
   set_state(STATE_ENTERING);
   return;
}

void Dynamic::exit()
{
   set_state(STATE_HIDING);
   return;
}

void Dynamic::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::set_state: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_ENTERING:
      break;

      case STATE_NORMAL:
         opacity = 1.0f;
      break;

      case STATE_HIDING:
      break;

      case STATE_HIDDEN:
         opacity = 0.0f;
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void Dynamic::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::update_state: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_ENTERING:
         opacity += 0.05f;
         if (opacity >= 1)
         {
            opacity = 1.0f;
            set_state(STATE_NORMAL);
         }
      break;

      case STATE_NORMAL:
      break;

      case STATE_HIDING:
         opacity -= 0.05f;
         if (opacity <= 0.0)
         {
            set_state(STATE_HIDDEN);
         }
      break;

      case STATE_HIDDEN:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

bool Dynamic::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_ENTERING,
      STATE_NORMAL,
      STATE_HIDING,
      STATE_HIDDEN,
   };
   return (valid_states.count(state) > 0);
}

bool Dynamic::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float Dynamic::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}


} // namespace StagedCharacter
} // namespace DialogSystem
} // namespace AllegroFlare


