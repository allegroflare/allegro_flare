

#include <AllegroFlare/DialogSystem/ChapterIndex.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{


ChapterIndex::ChapterIndex()
   : chapters({})
{
}


ChapterIndex::~ChapterIndex()
{
}


void ChapterIndex::set_chapters(tsl::ordered_map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> chapters)
{
   this->chapters = chapters;
}


tsl::ordered_map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> &ChapterIndex::get_chapters_ref()
{
   return chapters;
}


int ChapterIndex::num_chapters()
{
   return chapters.size();
}

std::vector<std::string> ChapterIndex::get_chapter_identifiers()
{
   std::vector<std::string> result;
   for (auto &chapter : chapters)
   {
      result.push_back(chapter.first);
   }
   return result;
}

void ChapterIndex::add_chapter(std::string identifier, AllegroFlare::DialogSystem::Chapters::Base* chapter)
{
   if (!((!chapter_exists_by_identifier(identifier))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::ChapterIndex::add_chapter]: error: guard \"(!chapter_exists_by_identifier(identifier))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::ChapterIndex::add_chapter]: error: guard \"(!chapter_exists_by_identifier(identifier))\" not met");
   }
   chapters[identifier] = chapter;
}

bool ChapterIndex::chapter_exists_by_identifier(std::string identifier)
{
   return (chapters.find(identifier) != chapters.end());
}

AllegroFlare::DialogSystem::Chapters::Base* ChapterIndex::find_chapter_by_identifier(std::string identifier)
{
   if (!(chapter_exists_by_identifier(identifier)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::ChapterIndex::find_chapter_by_identifier]: error: guard \"chapter_exists_by_identifier(identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::ChapterIndex::find_chapter_by_identifier]: error: guard \"chapter_exists_by_identifier(identifier)\" not met");
   }
   // TODO: This guard results in a double lookup. Might be faster to integrate it below.
   if (chapters.find(identifier) == chapters.end()) return nullptr;
   return chapters[identifier];
}


} // namespace DialogSystem
} // namespace AllegroFlare


