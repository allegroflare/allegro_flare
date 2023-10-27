

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


void ChapterIndex::set_chapters(std::map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> chapters)
{
   this->chapters = chapters;
}


std::map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> &ChapterIndex::get_chapters_ref()
{
   return chapters;
}


int ChapterIndex::num_chapters()
{
   return chapters.size();
}

std::vector<std::string> ChapterIndex::get_chapter_names()
{
   std::vector<std::string> result;
   for (auto &chapter : chapters)
   {
      result.push_back(chapter.first);
   }
   return result;
}

void ChapterIndex::add_chapter(std::string name, AllegroFlare::DialogSystem::Chapters::Base* chapter)
{
   if (!((!chapter_exists_by_name(name))))
   {
      std::stringstream error_message;
      error_message << "[ChapterIndex::add_chapter]: error: guard \"(!chapter_exists_by_name(name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterIndex::add_chapter: error: guard \"(!chapter_exists_by_name(name))\" not met");
   }
   chapters[name] = chapter;
}

bool ChapterIndex::chapter_exists_by_name(std::string name)
{
   return (chapters.find(name) != chapters.end());
}

AllegroFlare::DialogSystem::Chapters::Base* ChapterIndex::find_chapter_by_name(std::string name)
{
   if (!(chapter_exists_by_name(name)))
   {
      std::stringstream error_message;
      error_message << "[ChapterIndex::find_chapter_by_name]: error: guard \"chapter_exists_by_name(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChapterIndex::find_chapter_by_name: error: guard \"chapter_exists_by_name(name)\" not met");
   }
   // TODO: This guard results in a double lookup. Might be faster to integrate it below.
   if (chapters.find(name) == chapters.end()) return nullptr;
   return chapters[name];
}


} // namespace DialogSystem
} // namespace AllegroFlare


