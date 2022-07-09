

#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Base::Base(std::string type)
   : type(type)
   , finished(true)
{
}


Base::~Base()
{
}


void Base::set_finished(bool finished)
{
   this->finished = finished;
}


std::string Base::get_type()
{
   return type;
}


bool Base::get_finished()
{
   return finished;
}


void Base::start()
{
   return;
}

void Base::update()
{
   return;
}

void Base::render()
{
   return;
}

void Base::advance()
{
   return;
}
} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


