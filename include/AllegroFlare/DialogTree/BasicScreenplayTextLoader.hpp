#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class BasicScreenplayTextLoader
      {
      private:
         std::string filename;
         AllegroFlare::DialogTree::NodeBank node_bank;
         bool loaded;

      protected:


      public:
         BasicScreenplayTextLoader(std::string filename="[unset-filename]");
         ~BasicScreenplayTextLoader();

         bool get_loaded() const;
         void set_filename(std::string filename="[unset-filename]");
         AllegroFlare::DialogTree::NodeBank get_node_bank();
      };
   }
}



