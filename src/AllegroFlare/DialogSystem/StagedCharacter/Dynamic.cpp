

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


Dynamic::Dynamic()
   : expression("[unset-bitmap_identifier]")
   , expression_bitmap(nullptr)
   , placement()
   , placement_destination()
   , opacity(1.0f)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
{
}


Dynamic::~Dynamic()
{
}


void Dynamic::update()
{
   update_state();
   return;
}

void Dynamic::render()
{
   if (!expression_bitmap) return;
   {
      placement.start_transform();
      al_draw_bitmap(expression_bitmap, 0, 0, 0);
      placement.restore_transform();
   }
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
      case STATE_SHOWING:
      break;

      case STATE_NORMAL:
      break;

      case STATE_HIDING:
      break;

      case STATE_HIDDEN:
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
      case STATE_SHOWING:
      break;

      case STATE_NORMAL:
      break;

      case STATE_HIDING:
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
      STATE_SHOWING,
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


