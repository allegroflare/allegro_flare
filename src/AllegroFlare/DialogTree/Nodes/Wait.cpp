

#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>

#include <AllegroFlare/Time.hpp>


namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


Wait::Wait(float duration_sec, float started_at)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::Wait::TYPE)
   , duration_sec(duration_sec)
   , started_at(started_at)
{
}


Wait::~Wait()
{
}


float Wait::get_duration_sec() const
{
   return duration_sec;
}


float Wait::get_started_at() const
{
   return started_at;
}


void Wait::initialize(float time_now)
{
   started_at = time_now;
   if (AllegroFlare::Time::calculate_age(started_at, time_now) >= duration_sec) set_is_finished(true);
   else set_is_finished(false);
   return;
}

void Wait::update(float time_now)
{
   if (AllegroFlare::Time::calculate_age(started_at, time_now) >= duration_sec) set_is_finished(true);
   else set_is_finished(false);
   return;
}


} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


