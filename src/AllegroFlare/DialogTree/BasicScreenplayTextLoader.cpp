

#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>

#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


BasicScreenplayTextLoader::BasicScreenplayTextLoader(std::string text)
   : text(text)
   , node_bank({})
   , loaded(false)
{
}


BasicScreenplayTextLoader::~BasicScreenplayTextLoader()
{
}


bool BasicScreenplayTextLoader::get_loaded() const
{
   return loaded;
}


void BasicScreenplayTextLoader::set_text(std::string text)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::set_text]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::set_text: error: guard \"(!loaded)\" not met");
   }
   this->text = text;
   return;
}

AllegroFlare::DialogTree::NodeBank BasicScreenplayTextLoader::get_node_bank()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::get_node_bank]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::get_node_bank: error: guard \"loaded\" not met");
   }
   return node_bank;
}

void BasicScreenplayTextLoader::load_file(std::string filename)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::load_file]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::load_file: error: guard \"(!loaded)\" not met");
   }
   if (!((AllegroFlare::php::file_exists(filename))))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::load_file]: error: guard \"(AllegroFlare::php::file_exists(filename))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::load_file: error: guard \"(AllegroFlare::php::file_exists(filename))\" not met");
   }
   // TODO: Test this method
   // TODO: Remove "file_exists" using php as dependency, consider alternative that outputs name of missing file
   text = AllegroFlare::php::file_get_contents(filename);
   load();
}

const AllegroFlare::DialogTree::NodeBank& BasicScreenplayTextLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::load: error: guard \"(!loaded)\" not met");
   }
   std::vector<std::string> chunks = split(text, "\n\n");
   int node_id = 0;

   // TODO: Process the chunks and create nodes
   for (auto &chunk : chunks)
   {
      std::vector<std::string> sub_chunks = split(chunk, "\n");
      if (sub_chunks.size() == 0)
      {
         std::cout << "Parsing line with no sub_chunks" << std::endl;
      }
      else if (sub_chunks.size() == 1)
      {
         std::cout << "Skipping parsing on one-line chunk: \"" << sub_chunks[0] << "\"" << std::endl;
      }
      else if (sub_chunks.size() >= 2)
      {
         if (sub_chunks[0].empty()) continue;

         std::string node_name = "dialog_node_" + std::to_string(node_id); // TODO: Extract this to a function
         std::string next_node_name = "dialog_node_" + std::to_string(node_id+1);
         std::string speaker = sub_chunks.front();
         std::vector<std::string> dialog_pages = split(sub_chunks.back(), " / ");

         AllegroFlare::DialogTree::Nodes::MultipageWithOptions *result_node =
            new AllegroFlare::DialogTree::Nodes::MultipageWithOptions;


         //std::cout << "- speaker: " << speaker << std::endl;
         //std::cout << "    pages: " << dialog_pages.size() << std::endl;
         //int page_num = 1;
         //for (auto &dialog_page : dialog_pages)
         //{
            //std::cout << "     page " << page_num << ": " << dialog_page << std::endl;
            //page_num++;
         //}
         //std::cout << std::endl;

         result_node->set_speaker(speaker);
         result_node->set_pages(dialog_pages);
         result_node->set_options({
            { "next", create_GoToNode_option(next_node_name), 0 },
         });

         node_bank.add_node(node_name, result_node);

         node_id++;
      }
   }

   // Add an ExitDialog node at the end
   std::string node_name = "dialog_node_" + std::to_string(node_id); // TODO: Extract this to a function
   node_bank.add_node(node_name, new AllegroFlare::DialogTree::Nodes::ExitDialog());

   loaded = true;
   return node_bank;
}

AllegroFlare::DialogTree::NodeOptions::GoToNode* BasicScreenplayTextLoader::create_GoToNode_option(std::string node_target_name)
{
   AllegroFlare::DialogTree::NodeOptions::GoToNode* result = new AllegroFlare::DialogTree::NodeOptions::GoToNode;
   result->set_target_node_name(node_target_name);
   return result;
}

std::vector<std::string> BasicScreenplayTextLoader::split(std::string input, std::string delimiter)
{
   std::vector<std::string> tokens;
   size_t start = 0, end = 0;
   while ((end = input.find(delimiter, start)) != std::string::npos)
   {
      tokens.push_back(input.substr(start, end - start));
      start = end + delimiter.length();
   }
   tokens.push_back(input.substr(start));
   return tokens;
}


} // namespace DialogTree
} // namespace AllegroFlare


