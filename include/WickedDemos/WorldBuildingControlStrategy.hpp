#pragma once

#include <WickedDemos/ControlStrategyBase.hpp>

class FunzDemo;

class WorldBuildingControlStrategy : public ControlStrategyBase
{
private:
   FunzDemo *funz_demo;

public:
   WorldBuildingControlStrategy(FunzDemo *funz_demo=nullptr);

   void move_cursor_to_entity_id(int id);
   void move_cursor_to_next_entity();
   void move_cursor_to_previous_entity();
   void rotate_currently_selected_entity();
   void ascend_currently_selected_entity(float distance);
   void descend_currently_selected_entity(float distance);
   void move_currently_selected_entity_up(float distance);
   void move_currently_selected_entity_down(float distance);
   void move_currently_selected_entity_left(float distance);
   void move_currently_selected_entity_right(float distance);
   void create_entity_into_scene();
   void delete_currently_selected_entity();

   virtual void on_activate() override;
   virtual void on_deactivate() override;

   virtual void key_up_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_down_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_char_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void primary_timer_func() override;
};

