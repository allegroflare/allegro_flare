

#include <AllegroFlare/DialogTree/Nodes/Base.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


Base::Base(std::string type)
   : type(type)
   , is_finished(true)
{
}


Base::~Base()
{
}


void Base::set_is_finished(bool is_finished)
{
   this->is_finished = is_finished;
}


std::string Base::get_type() const
{
   return type;
}


bool Base::get_is_finished() const
{
   return is_finished;
}


void Base::initialize(float time_now)
{
   return;
}

void Base::update(float time_now)
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


