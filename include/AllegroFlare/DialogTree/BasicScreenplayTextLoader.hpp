#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class BasicScreenplayTextLoader
      {
      private:
         std::string text;
         AllegroFlare::DialogTree::NodeBank node_bank;
         bool loaded;

      protected:


      public:
         BasicScreenplayTextLoader(std::string text="[unset-text]");
         ~BasicScreenplayTextLoader();

         bool get_loaded() const;
         void set_text(std::string text="[unset-text]");
         AllegroFlare::DialogTree::NodeBank get_node_bank();
         AllegroFlare::DialogTree::NodeBank load();
         static std::vector<std::string> split(std::string input="[unset-input]", std::string delimiter="__");
      };
   }
}



