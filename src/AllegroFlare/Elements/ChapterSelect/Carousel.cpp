

#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


Carousel::Carousel(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
   : elements(elements)
{
}


Carousel::~Carousel()
{
}


void Carousel::set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
{
   this->elements = elements;
}


std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> Carousel::get_elements() const
{
   return elements;
}


void Carousel::update()
{
   for (auto &element : elements) element->update();
   return;
}

void Carousel::render()
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer renderer;
   for (auto &element : elements) renderer.render(element);
   return;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


