#pragma once


#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class Node
      {
      private:
         std::string speaker;
         std::vector<std::string> pages;
         std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> options;

      protected:


      public:
         Node();
         ~Node();

         void set_speaker(std::string speaker);
         void set_pages(std::vector<std::string> pages);
         void set_options(std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> options);
         std::string get_speaker() const;
         std::vector<std::string> get_pages() const;
         std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> get_options() const;
      };
   }
}



