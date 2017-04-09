#pragma once



#include <allegro_flare/framework.h>



class UserEventEmitter
{
private:
   ALLEGRO_EVENT_SOURCE event_source;
   static UserEventEmitter *instance;
   static UserEventEmitter *get_instance();

   UserEventEmitter();
   ~UserEventEmitter();

public:
   static void emit_event(int32_t event_type, intptr_t data1=0, intptr_t data2=0);
};



