#include <WickedDemos/InventoryControlStrategy.hpp>


InventoryControlStrategy::InventoryControlStrategy(FunzDemo *funz_demo)
   : ControlStrategyBase("InventoryControlStrategy")
   , funz_demo(funz_demo)
{}
void InventoryControlStrategy::on_activate() {}
void InventoryControlStrategy::on_deactivate() {}
void InventoryControlStrategy::key_up_func(ALLEGRO_EVENT *ev)
{
   // nothing
}
void InventoryControlStrategy::key_down_func(ALLEGRO_EVENT *ev)
{
   // nothing
}
void InventoryControlStrategy::key_char_func(ALLEGRO_EVENT *ev)
{
   if (!funz_demo) throw std::runtime_error("[InventoryControlStrategy::key_char_func] error: funz_demo cannot be nullptr");
   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;

   switch(ev->keyboard.keycode)
   {
   case ALLEGRO_KEY_UP:
   case ALLEGRO_KEY_K:
      funz_demo->inventory.move_cursor_up();
      funz_demo->cursor_brush_id = funz_demo->inventory.get_item_in_details_pane();
      if (funz_demo->menu_cursor_move_click_sound) funz_demo->menu_cursor_move_click_sound->stop(); funz_demo->menu_cursor_move_click_sound->play();
      break;
   case ALLEGRO_KEY_DOWN:
   case ALLEGRO_KEY_J:
      funz_demo->inventory.move_cursor_down();
      funz_demo->cursor_brush_id = funz_demo->inventory.get_item_in_details_pane();
      if (funz_demo->menu_cursor_move_click_sound) funz_demo->menu_cursor_move_click_sound->stop(); funz_demo->menu_cursor_move_click_sound->play();
      break;
   case ALLEGRO_KEY_LEFT:
   case ALLEGRO_KEY_H:
      funz_demo->inventory.move_cursor_left();
      funz_demo->cursor_brush_id = funz_demo->inventory.get_item_in_details_pane();
      if (funz_demo->menu_cursor_move_click_sound) funz_demo->menu_cursor_move_click_sound->stop(); funz_demo->menu_cursor_move_click_sound->play();
      break;
   case ALLEGRO_KEY_RIGHT:
   case ALLEGRO_KEY_L:
      funz_demo->inventory.move_cursor_right();
      funz_demo->cursor_brush_id = funz_demo->inventory.get_item_in_details_pane();
      if (funz_demo->menu_cursor_move_click_sound) funz_demo->menu_cursor_move_click_sound->stop(); funz_demo->menu_cursor_move_click_sound->play();
      break;
   }
}
void InventoryControlStrategy::primary_timer_func() {}
