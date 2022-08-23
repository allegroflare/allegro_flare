

#include <AllegroFlare/Timeline/ActorManager.hpp>



namespace AllegroFlare
{
namespace Timeline
{


      ActorManager::ActorManager()
      {}



      void ActorManager::set_actors(std::vector<Actors::Base *> actors)
      {
         this->actors = actors;
      }



      std::vector<Actors::Base *> ActorManager::get_actors()
      {
         return actors;
      }


      //Actor *ActorManager::create_actor2d(std::string identifier, ALLEGRO_BITMAP *bitmap)
      //{
      //	actors.push_back(new Actor2D(identifier, bitmap));
      //	return actors.back();
      //}




      bool ActorManager::register_actor(Actors::Base *actor)
      {
         if (get_actor_by_id(actor->identifier.c_str())) return false;

         actors.push_back(actor);
         return true;
      }




      bool ActorManager::unregister_actor(Actors::Base *actor)
      {
         // this could be optimized
         for (unsigned i=0; i<actors.size(); i++)
            if (actors[i]->identifier == actor->identifier)
            {
               actors.erase(actors.begin()+i);
               return true;
            }
         return false;
      }




      Actors::Base *ActorManager::get_actor_by_id(const char *id)
      {
         for (unsigned i=0; i<actors.size(); i++)
            if (actors[i]->identifier == id) return actors[i];
         return NULL;
      }




      void ActorManager::render(double time)
      {
         for (unsigned i=0; i<actors.size(); i++)
            actors[i]->render(time);
      }



} // namespace Timeline
} // namespace AllegroFlare


