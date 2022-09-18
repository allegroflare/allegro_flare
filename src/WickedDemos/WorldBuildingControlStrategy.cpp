#include <WickedDemos/WorldBuildingControlStrategy.hpp>
#include <WickedDemos/FunzDemo.hpp>

#include <WickedDemos/globals.hpp>


WorldBuildingControlStrategy::WorldBuildingControlStrategy(FunzDemo *funz_demo)
   : ControlStrategyBase("WorldBuildingControlStrategy")
   , funz_demo(funz_demo)
{}

void WorldBuildingControlStrategy::move_cursor_to_entity_id(int id)
{
   funz_demo->cursor_over_entity_id = id;
   if (funz_demo->cursor_over_entity_id > Entity::get_last_id()) funz_demo->cursor_over_entity_id = 0;
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (entity)
   {
      funz_demo->camera_target_position = entity->place.position;
      if (funz_demo->cursor_move) { funz_demo->cursor_move->stop(); funz_demo->cursor_move->play(); }
   }
}

void WorldBuildingControlStrategy::move_cursor_to_next_entity()
{
   funz_demo->cursor_over_entity_id++;
   if (funz_demo->cursor_over_entity_id > Entity::get_last_id()) funz_demo->cursor_over_entity_id = 0;
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (entity)
   {
      funz_demo->camera_target_position = entity->place.position;
      if (funz_demo->cursor_move) { funz_demo->cursor_move->stop(); funz_demo->cursor_move->play(); }
   }
}

void WorldBuildingControlStrategy::move_cursor_to_previous_entity()
{
   funz_demo->cursor_over_entity_id--;
   if (funz_demo->cursor_over_entity_id < 0) funz_demo->cursor_over_entity_id = Entity::get_last_id();
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (entity)
   {
      funz_demo->camera_target_position = entity->place.position;
      if (funz_demo->cursor_move) { funz_demo->cursor_move->stop(); funz_demo->cursor_move->play(); }
   }
}

void WorldBuildingControlStrategy::rotate_currently_selected_entity()
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;

   entity->place.rotation.y += (0.25 / 2);
   if (funz_demo->rotate_selection_sound) { funz_demo->rotate_selection_sound->stop(); funz_demo->rotate_selection_sound->play(); }
}

void WorldBuildingControlStrategy::ascend_currently_selected_entity(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.y += distance;
}

void WorldBuildingControlStrategy::descend_currently_selected_entity(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.y -= distance;
}

void WorldBuildingControlStrategy::move_currently_selected_entity_up(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.z -= distance;
}

void WorldBuildingControlStrategy::move_currently_selected_entity_down(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.z += distance;
}

void WorldBuildingControlStrategy::move_currently_selected_entity_left(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.x += distance;
}

void WorldBuildingControlStrategy::move_currently_selected_entity_right(float distance)
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity) return;
   entity->place.position.x -= distance;
}

void WorldBuildingControlStrategy::create_entity_into_scene()
{
   std::string type = inventory_index_id_to_factory_identifier(funz_demo->cursor_brush_id);
   Entity *created_entity = funz_demo->entity_factory.create_by_type(type);
   if (created_entity)
   {
      created_entity->place.position = funz_demo->camera_target_position;
      funz_demo->entities.push_back(created_entity);
      int created_entity_id = created_entity->get_id();
      move_cursor_to_entity_id(created_entity_id);
   }
   if (!created_entity) throw std::runtime_error("FFFAAaauur");
}

void WorldBuildingControlStrategy::delete_currently_selected_entity()
{
   Entity *entity = funz_demo->find_by_id(funz_demo->cursor_over_entity_id);
   if (!entity)
   {
      if (funz_demo->input_bonk_sound) { funz_demo->input_bonk_sound->stop(); funz_demo->input_bonk_sound->play(); }
      return;
   }

   for (unsigned i=0; i<funz_demo->entities.size(); i++)
   {
      if (funz_demo->entities[i] == entity)
      {
         delete entity;
         funz_demo->entities.erase(funz_demo->entities.begin() + i);
         break;
      }
   }

   if (funz_demo->delete_item_sound) { funz_demo->delete_item_sound->stop(); funz_demo->delete_item_sound->play(); }
}
void WorldBuildingControlStrategy::on_activate() {}
void WorldBuildingControlStrategy::on_deactivate() {}
void WorldBuildingControlStrategy::key_up_func(ALLEGRO_EVENT *ev)
{
   // nothing
}
void WorldBuildingControlStrategy::key_down_func(ALLEGRO_EVENT *ev)
{
   // nothing
}
void WorldBuildingControlStrategy::key_char_func(ALLEGRO_EVENT *ev)
{
   if (!funz_demo) throw std::runtime_error("[WorldBuildingControlStrategy::key_char_func] error: funz_demo cannot be nullptr");

   //ALLEGRO_EVENT *ev = Framework::current_event; //key_down_func();
   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;

   float distance_to_move = 0.5;
   if (shift) distance_to_move = 5.0;

   switch(ev->keyboard.keycode)
   {
   case ALLEGRO_KEY_ENTER:
      create_entity_into_scene();
      break;
   case ALLEGRO_KEY_BACKSPACE:
      delete_currently_selected_entity();
      break;
   case ALLEGRO_KEY_CLOSEBRACE:
   case ALLEGRO_KEY_N:
      move_cursor_to_next_entity();
      break;
   case ALLEGRO_KEY_OPENBRACE:
   case ALLEGRO_KEY_P:
      move_cursor_to_previous_entity();
      break;
   case ALLEGRO_KEY_EQUALS:
      if (!shift) funz_demo->light_target_time_of_day += 0.1f;
      else funz_demo->light_target_spin += 0.1f;
      break;
   case ALLEGRO_KEY_MINUS:
      if (!shift) funz_demo->light_target_time_of_day -= 0.1f;
      else funz_demo->light_target_spin -= 0.1f;
      break;
   case ALLEGRO_KEY_A:
      funz_demo->camera_target_position.x -= distance_to_move;
      break;
   case ALLEGRO_KEY_D:
      funz_demo->camera_target_position.x += distance_to_move;
      break;
   case ALLEGRO_KEY_W:
      funz_demo->camera_target_position.z -= distance_to_move;
      break;
   case ALLEGRO_KEY_S:
      funz_demo->camera_target_position.z += distance_to_move;
      break;
   case ALLEGRO_KEY_R:
      rotate_currently_selected_entity();
      break;
   case ALLEGRO_KEY_E:
      funz_demo->camera_target_position.y += distance_to_move;
      break;
   case ALLEGRO_KEY_C:
      funz_demo->camera_target_position.y -= distance_to_move;
      break;
   case ALLEGRO_KEY_U:
      ascend_currently_selected_entity(distance_to_move);
      break;
   case ALLEGRO_KEY_J:
      descend_currently_selected_entity(distance_to_move);
      break;
   case ALLEGRO_KEY_UP:
      move_currently_selected_entity_up(distance_to_move);
      break;
   case ALLEGRO_KEY_DOWN:
      move_currently_selected_entity_down(distance_to_move);
      break;
   case ALLEGRO_KEY_RIGHT:
      move_currently_selected_entity_left(distance_to_move);
      break;
   case ALLEGRO_KEY_LEFT:
      move_currently_selected_entity_right(distance_to_move);
      break;
   case ALLEGRO_KEY_PAD_6:
      funz_demo->camera_spinning = false;
      funz_demo->camera_target_spin -= 0.2f;
      break;
   case ALLEGRO_KEY_PAD_4:
      funz_demo->camera_spinning = false;
      funz_demo->camera_target_spin += 0.2f;
      break;
   case ALLEGRO_KEY_PAD_2:
      funz_demo->camera_target_stepout_z += 2.0f;
      break;
   case ALLEGRO_KEY_PAD_8:
      funz_demo->camera_target_stepout_z -= 2.0f;
      break;
   case ALLEGRO_KEY_PAD_PLUS:
      if (funz_demo->camera_target_zoom >= funz_demo->max_zoom) break;
      else { funz_demo->camera_target_zoom += 0.2f; }
      break;
   case ALLEGRO_KEY_PAD_MINUS:
      if (funz_demo->camera_target_zoom <= funz_demo->min_zoom) break;
      else { funz_demo->camera_target_zoom -= 0.2f; }
      break;
   };
}
void WorldBuildingControlStrategy::primary_timer_func() {}

