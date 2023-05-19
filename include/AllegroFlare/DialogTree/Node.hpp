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
         std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options;

      protected:


      public:
         Node(std::string speaker="[unset-speaker]", std::vector<std::string> pages={"[unset-pages]"}, std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options={});
         ~Node();

         void set_speaker(std::string speaker);
         void set_pages(std::vector<std::string> pages);
         void set_options(std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options);
         std::string get_speaker() const;
         std::vector<std::string> get_pages() const;
         std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> get_options() const;
         std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> get_option_num(int option_num=0);
         std::vector<std::string> build_options_as_text();
         int num_options();
      };
   }
}



