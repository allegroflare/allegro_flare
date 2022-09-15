

#include <WickedDemos/ControlStrategyBase.hpp>


ControlStrategyBase::ControlStrategyBase(std::string type) : type(type) {}
ControlStrategyBase::~ControlStrategyBase() {}

void ControlStrategyBase::on_activate() {}
void ControlStrategyBase::on_deactivate() {}

void ControlStrategyBase::key_up_func(ALLEGRO_EVENT *ev) {}
void ControlStrategyBase::key_down_func(ALLEGRO_EVENT *ev) {}
void ControlStrategyBase::key_char_func(ALLEGRO_EVENT *ev) {}
void ControlStrategyBase::primary_timer_func() {}



