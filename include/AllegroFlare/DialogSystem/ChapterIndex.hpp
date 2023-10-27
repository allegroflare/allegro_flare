#pragma once


#include <AllegroFlare/DialogSystem/Chapters/Base.hpp>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class ChapterIndex
      {
      private:
         std::map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> chapters;

      protected:


      public:
         ChapterIndex();
         ~ChapterIndex();

         void set_chapters(std::map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> chapters);
         std::map<std::string, AllegroFlare::DialogSystem::Chapters::Base*> &get_chapters_ref();
         int num_chapters();
         std::vector<std::string> get_chapter_identifiers();
         void add_chapter(std::string identifier="[unset-identifier]", AllegroFlare::DialogSystem::Chapters::Base* chapter=nullptr);
         bool chapter_exists_by_identifier(std::string identifier="[unset-identifier]");
         AllegroFlare::DialogSystem::Chapters::Base* find_chapter_by_identifier(std::string identifier="[unset-identifier]");
      };
   }
}



