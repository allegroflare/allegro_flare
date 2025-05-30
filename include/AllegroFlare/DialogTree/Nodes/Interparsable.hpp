#pragma once


#include <AllegroFlare/BitFlags.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class Interparsable : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/Interparsable";

         public:

            enum OptionFlags
            {
               FLAG_NONE = 0x0000,
               FLAG_CURSOR_HERE_ON_SPAWN = 0x0001,
               FLAG_DISABLED = 0x0002,
            };
         private:
            std::string speaker;
            std::vector<std::string> pages;
            std::vector<std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>> options;

         protected:


         public:
            Interparsable(std::string speaker="[unset-speaker]", std::vector<std::string> pages={"[unset-pages]"}, std::vector<std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>> options={});
            ~Interparsable();

            void set_speaker(std::string speaker);
            void set_pages(std::vector<std::string> pages);
            void set_options(std::vector<std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>> options);
            std::string get_speaker() const;
            std::vector<std::string> get_pages() const;
            std::vector<std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>> get_options() const;
            std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>> get_option_num(int option_num=0);
            std::vector<std::string> build_options_as_text();
            int num_pages();
            int num_options();
            bool has_options();
            bool has_no_options();
            bool option_is_selectable(int option_num=0);
            int infer_cursor_position_on_spawn();
         };
      }
   }
}



