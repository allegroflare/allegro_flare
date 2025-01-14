#pragma once


#include <functional>
#include <set>
#include <vector>


namespace AllegroFlare
{
   namespace CollisionObservers
   {
      class Simple
      {
      private:
         void* subject;
         std::set<void*> collidables;
         std::function<bool(void*, void*)> on_test_collide;
         std::set<void*> currently_colliding;
         std::vector<void*> entered;
         std::vector<void*> exited;
         std::vector<void*> stayed_out;
         std::vector<void*> stayed_in;

      protected:


      public:
         Simple();
         ~Simple();

         void set_subject(void* subject);
         void set_collidables(std::set<void*> collidables);
         void set_on_test_collide(std::function<bool(void*, void*)> on_test_collide);
         void set_currently_colliding(std::set<void*> currently_colliding);
         void* get_subject() const;
         std::set<void*> get_collidables() const;
         std::function<bool(void*, void*)> get_on_test_collide() const;
         std::set<void*> get_currently_colliding() const;
         std::vector<void*> get_entered() const;
         std::vector<void*> get_exited() const;
         std::vector<void*> get_stayed_out() const;
         std::vector<void*> get_stayed_in() const;
         std::vector<void*> &get_entered_ref();
         std::vector<void*> &get_exited_ref();
         std::vector<void*> &get_stayed_out_ref();
         std::vector<void*> &get_stayed_in_ref();
         void clear();
         bool currently_colliding_is_empty();
         bool is_subject_currently_colliding_with(void* other=nullptr);
         void passively_add_to_currently_colliding(void* collidable=nullptr);
         void process();
      };
   }
}



