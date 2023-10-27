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
         std::vector<std::string> get_chapter_names();
         void add_chapter(std::string name="[unset-name]", AllegroFlare::DialogSystem::Chapters::Base* chapter=nullptr);
         bool chapter_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogSystem::Chapters::Base* find_chapter_by_name(std::string name="[unset-name]");
      };
   }
}



