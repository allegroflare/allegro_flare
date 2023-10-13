

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElements
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


float Base::calculate_width()
{
   return 0.0f;
}

float Base::calculate_height()
{
   return 0.0f;
}

void Base::update()
{
   return;
}

void Base::render()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace CarouselElements
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


