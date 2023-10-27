#pragma once


#include <AllegroFlare/DialogSystem/Chapter.hpp>
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
         std::map<std::string, AllegroFlare::DialogSystem::Chapter> chapters;

      protected:


      public:
         ChapterIndex();
         ~ChapterIndex();

         void set_chapters(std::map<std::string, AllegroFlare::DialogSystem::Chapter> chapters);
         std::map<std::string, AllegroFlare::DialogSystem::Chapter> &get_chapters_ref();
         int num_chapters();
         std::vector<std::string> get_chapter_names();
         void add_chapter(std::string name="[unset-name]", AllegroFlare::DialogSystem::Chapter chapter={});
         bool chapter_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogSystem::Chapter find_chapter_by_name(std::string name="[unset-name]");
      };
   }
}



