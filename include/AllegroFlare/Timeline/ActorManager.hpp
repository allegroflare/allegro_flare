#pragma once


#include <string>
#include <vector>
#include <AllegroFlare/Timeline/Actors/Base.hpp>


namespace AllegroFlare
{
   namespace Timeline
   {
      class ActorManager
      {
      protected:
         std::vector<Actors::Base *> actors;

      public:
         ActorManager();

         void set_actors(std::vector<Actors::Base *> actors={});
         std::vector<Actors::Base *> get_actors();

         //Actor *create_actor2d(std::string identifier, ALLEGRO_BITMAP *bitmap);
         bool register_actor(Actors::Base *actor);
         bool unregister_actor(Actors::Base *actor);

         Actors::Base *get_actor_by_id(const char *id);
         void render(double time);
      };
   }
}



