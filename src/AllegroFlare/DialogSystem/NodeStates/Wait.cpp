

#include <AllegroFlare/DialogSystem/NodeStates/Wait.hpp>

#include <AllegroFlare/Time.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace NodeStates
{


Wait::Wait(AllegroFlare::DialogTree::Nodes::Wait* wait_node)
   : AllegroFlare::DialogSystem::NodeStates::Base(AllegroFlare::DialogSystem::NodeStates::Wait::TYPE)
   , wait_node(wait_node)
   , started_at(0.0f)
   , is_finished(false)
{
}


Wait::~Wait()
{
}


AllegroFlare::DialogTree::Nodes::Wait* Wait::get_wait_node() const
{
   return wait_node;
}


float Wait::get_started_at() const
{
   return started_at;
}


bool Wait::get_is_finished() const
{
   return is_finished;
}


void Wait::initialize(float time_now)
{
   if (!(wait_node))
   {
      std::stringstream error_message;
      error_message << "[Wait::initialize]: error: guard \"wait_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Wait::initialize: error: guard \"wait_node\" not met");
   }
   started_at = time_now;
   if (AllegroFlare::Time::calculate_age(time_now, started_at) >= wait_node->get_duration_sec()) is_finished = true;
   return;
}

void Wait::update(float time_now)
{
   if (!(wait_node))
   {
      std::stringstream error_message;
      error_message << "[Wait::update]: error: guard \"wait_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Wait::update: error: guard \"wait_node\" not met");
   }
   if (is_finished) return;
   if (AllegroFlare::Time::calculate_age(time_now, started_at) >= wait_node->get_duration_sec()) is_finished = true;
   return;
}


} // namespace NodeStates
} // namespace DialogSystem
} // namespace AllegroFlare


