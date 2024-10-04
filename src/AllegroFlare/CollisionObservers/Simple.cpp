

#include <AllegroFlare/CollisionObservers/Simple.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CollisionObservers
{


Simple::Simple()
   : subject(nullptr)
   , collidables({})
   , on_test_collide({})
   , currently_colliding({})
   , entered({})
   , exited({})
   , stayed_out({})
   , stayed_in({})
{
}


Simple::~Simple()
{
}


void Simple::set_subject(void* subject)
{
   this->subject = subject;
}


void Simple::set_collidables(std::set<void*> collidables)
{
   this->collidables = collidables;
}


void Simple::set_on_test_collide(std::function<bool(void*, void*)> on_test_collide)
{
   this->on_test_collide = on_test_collide;
}


void Simple::set_currently_colliding(std::set<void*> currently_colliding)
{
   this->currently_colliding = currently_colliding;
}


void* Simple::get_subject() const
{
   return subject;
}


std::set<void*> Simple::get_collidables() const
{
   return collidables;
}


std::function<bool(void*, void*)> Simple::get_on_test_collide() const
{
   return on_test_collide;
}


std::set<void*> Simple::get_currently_colliding() const
{
   return currently_colliding;
}


std::vector<void*> Simple::get_entered() const
{
   return entered;
}


std::vector<void*> Simple::get_exited() const
{
   return exited;
}


std::vector<void*> Simple::get_stayed_out() const
{
   return stayed_out;
}


std::vector<void*> Simple::get_stayed_in() const
{
   return stayed_in;
}


bool Simple::currently_colliding_is_empty()
{
   return currently_colliding.empty();
}

void Simple::process()
{
   if (!(subject))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CollisionObservers::Simple::process]: error: guard \"subject\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CollisionObservers::Simple::process]: error: guard \"subject\" not met");
   }
   if (!(on_test_collide))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CollisionObservers::Simple::process]: error: guard \"on_test_collide\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CollisionObservers::Simple::process]: error: guard \"on_test_collide\" not met");
   }
   // Clear from our previous pass
   entered.clear();
   exited.clear();
   stayed_out.clear();
   stayed_in.clear();

   // Build up a list of entities that are colliding in this frame
   std::set<void*> now_colliding;

   for (auto &collidable : collidables)
   {
      bool colliding = on_test_collide(subject, collidable);
      if (colliding) now_colliding.insert(collidable);
   }

   // Process enter, exit, stayed_in, stayed_out collisions
   for (auto &collidable : collidables)
   {
      bool in_previous = currently_colliding.find(collidable) != currently_colliding.end();
      bool in_current = now_colliding.find(collidable) != now_colliding.end();

      if (in_previous && in_current) stayed_in.push_back(collidable);
      else if (!in_previous && in_current) entered.push_back(collidable);
      else if (in_previous && !in_current) exited.push_back(collidable);
      else stayed_out.push_back(collidable);
   }

   // Include in "exited" the entities that are not in collidables, but are in currently_colliding. This may
   // be unexpected behavior in some circumstances, if the pointer has been deleted, for example.
   for (auto &collidable : currently_colliding)
   {
      if (collidables.find(collidable) == collidables.end()) exited.push_back(collidable);
   }

   currently_colliding = now_colliding;

   return;
}


} // namespace CollisionObservers
} // namespace AllegroFlare


