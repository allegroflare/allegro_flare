#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class ChapterTitle : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/ChapterTitle";

         private:
            std::string title_text;

         protected:


         public:
            ChapterTitle(std::string title_text="[unset-title_text]");
            ~ChapterTitle();

            std::string get_title_text() const;
         };
      }
   }
}



