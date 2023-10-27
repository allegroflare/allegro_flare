

#include <AllegroFlare/DialogSystem/Chapters/Basic.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace Chapters
{


Basic::Basic(std::string title, std::string chapter_select_image_identifier)
   : AllegroFlare::DialogSystem::Chapters::Base(AllegroFlare::DialogSystem::Chapters::Basic::TYPE)
   , title(title)
   , chapter_select_image_identifier(chapter_select_image_identifier)
{
}


Basic::~Basic()
{
}




} // namespace Chapters
} // namespace DialogSystem
} // namespace AllegroFlare


