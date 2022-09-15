#pragma once


#include <WickedDemos/FunzDemo.hpp>



class InventoryControlStrategy : public ControlStrategyBase
{
private:
   FunzDemo *funz_demo;

public:
   InventoryControlStrategy(FunzDemo *funz_demo=nullptr);

   virtual void on_activate() override;
   virtual void on_deactivate() override;

   virtual void key_up_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_down_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_char_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void primary_timer_func() override;
};



