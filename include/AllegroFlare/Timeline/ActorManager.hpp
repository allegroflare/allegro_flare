#pragma once


#include <string>
#include <vector>
#include <AllegroFlare/Timeline/Actor.hpp>


namespace AllegroFlare
{
   namespace Timeline
   {
      class ActorManager
      {
      protected:
         std::vector<Actor *> actors;

      public:
         ActorManager();

         //Actor *create_actor2d(std::string identifier, ALLEGRO_BITMAP *bitmap);
         bool register_actor(Actor *actor);
         bool unregister_actor(Actor *actor);

         Actor *get_actor_by_id(const char *id);
         void render(double time);
      };
   }
}



