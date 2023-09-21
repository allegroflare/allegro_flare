#pragma once


#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class MultipageWithOptions : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/MultipageWithOptions";

         private:
            std::string speaker;
            std::vector<std::string> pages;
            std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options;

         protected:


         public:
            MultipageWithOptions(std::string speaker="[unset-speaker]", std::vector<std::string> pages={"[unset-pages]"}, std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options={});
            ~MultipageWithOptions();

            void set_speaker(std::string speaker);
            void set_pages(std::vector<std::string> pages);
            void set_options(std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options);
            std::string get_speaker() const;
            std::vector<std::string> get_pages() const;
            std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> get_options() const;
            std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> get_option_num(int option_num=0);
            std::vector<std::string> build_options_as_text();
            int num_pages();
            int num_options();
         };
      }
   }
}



