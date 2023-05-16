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
         std::vector<std::string> pages;
         std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> options;

      protected:


      public:
         Node();
         ~Node();

         void set_pages(std::vector<std::string> pages);
         void set_options(std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> options);
         std::vector<std::string> get_pages() const;
         std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> get_options() const;
      };
   }
}



