#include <allegro5/allegro.h>
#include <iostream>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
//#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>
#include <AllegroFlare/EventNames.hpp>


bool abort_dialog = false;
AllegroFlare::DialogTree::Node *current_dialog_node = nullptr;
int current_dialog_node_page_num = 0;
AllegroFlare::DialogTree::NodeBank node_bank;


void clear_terminal()
{
    std::cout << "\033[2J\033[1;1H";
}






#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/EventEmitter.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeOptionActivator
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::DialogTree::NodeBank* node_bank;
         AllegroFlare::DialogTree::Node* currently_active_node;
         int selection_choice;

      protected:


      public:
         NodeOptionActivator(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::DialogTree::NodeBank* node_bank=nullptr, AllegroFlare::DialogTree::Node* currently_active_node=nullptr, int selection_choice=0);
         ~NodeOptionActivator();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank);
         void set_currently_active_node(AllegroFlare::DialogTree::Node* currently_active_node);
         void set_selection_choice(int selection_choice);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::DialogTree::NodeBank* get_node_bank() const;
         AllegroFlare::DialogTree::Node* get_currently_active_node() const;
         int get_selection_choice() const;
         void activate();
      };
   }
}




//#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


NodeOptionActivator::NodeOptionActivator(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::DialogTree::NodeBank* node_bank, AllegroFlare::DialogTree::Node* currently_active_node, int selection_choice)
   : event_emitter(event_emitter)
   , node_bank(node_bank)
   , currently_active_node(currently_active_node)
   , selection_choice(selection_choice)
{
}


NodeOptionActivator::~NodeOptionActivator()
{
}


void NodeOptionActivator::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void NodeOptionActivator::set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank)
{
   this->node_bank = node_bank;
}


void NodeOptionActivator::set_currently_active_node(AllegroFlare::DialogTree::Node* currently_active_node)
{
   this->currently_active_node = currently_active_node;
}


void NodeOptionActivator::set_selection_choice(int selection_choice)
{
   this->selection_choice = selection_choice;
}


AllegroFlare::EventEmitter* NodeOptionActivator::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::DialogTree::NodeBank* NodeOptionActivator::get_node_bank() const
{
   return node_bank;
}


AllegroFlare::DialogTree::Node* NodeOptionActivator::get_currently_active_node() const
{
   return currently_active_node;
}


int NodeOptionActivator::get_selection_choice() const
{
   return selection_choice;
}


void NodeOptionActivator::activate()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"event_emitter\" not met");
   }
   if (!(node_bank))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"node_bank\" not met");
   }
   if (!(currently_active_node))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"currently_active_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"currently_active_node\" not met");
   }
   if (!((selection_choice >= 0)))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"(selection_choice >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"(selection_choice >= 0)\" not met");
   }
   if (!((selection_choice < currently_active_node->num_options())))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"(selection_choice < currently_active_node->num_options())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"(selection_choice < currently_active_node->num_options())\" not met");
   }
   AllegroFlare::DialogTree::NodeOptions::Base* node_option =
      currently_active_node->get_option_num(selection_choice).second;
   std::string node_option_type = node_option->get_type();

   std::map<std::string, std::function<void()>> types_map = {
      { AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE, [this, node_option]() {
         AllegroFlare::DialogTree::NodeOptions::ExitDialog* as_exit_dialog_node_option =
            static_cast<AllegroFlare::DialogTree::NodeOptions::ExitDialog*>(node_option);
         event_emitter->emit_dialog_close_event();
      }},
      { AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE, [this, node_option]() {
         // TODO: Test this case
         AllegroFlare::DialogTree::NodeOptions::GoToNode* as_go_to_node_dialog_node_option =
            static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(node_option);
         std::string target_node_name = as_go_to_node_dialog_node_option->get_target_node_name();
         event_emitter->emit_dialog_open_event(target_node_name);
      }},
   };

   // locate and call the function to handle the item
   if (types_map.count(node_option_type) == 0)
   {
      // item not found
      std::stringstream error_message;
      error_message << "[DialogTree::NodeOptionActivator::activate]: error: Cannot activate a node with the "
                    << "node_option_type \"" << node_option_type << "\", a handling for that type does not exist.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      // call the item
      types_map[node_option_type]();
   }

   return;
}


} // namespace DialogTree
} // namespace AllegroFlare



#include <sstream> // For std::istringstream

std::string formatTextInBox2(const std::string& speaker, const std::string& text, int boxWidth, int boxHeight)
{
    boxHeight = boxHeight - 1;
    std::string corner = "+";
    std::string horizontalLine = "-";
    std::string verticalLine = "|";
    std::string emptySpace = " ";

    std::string formattedText = "";

    // Top border (with speaker name)
    std::string borderLine = corner + std::string(2, horizontalLine[0]) + " " + speaker + " ";
    int remainingWidth = boxWidth - borderLine.length() - 1;
    formattedText += borderLine + std::string(remainingWidth, horizontalLine[0]) + corner + '\n';

    // Content
    std::istringstream iss(text);
    std::string word;
    std::string line = verticalLine + " ";
    while (iss >> word) {
        if (line.length() + word.length() + 1 > boxWidth - 3) { // Adjusting for the verticalLine and spaces
            formattedText += line + std::string(boxWidth - line.length() - 2, emptySpace[0]) + verticalLine + '\n';
            line = verticalLine + " ";
        }
        line += word + " ";
    }
    if (!line.empty()) {
        formattedText += line + std::string(boxWidth - line.length() - 2, emptySpace[0]) + verticalLine + '\n';
    }

    // Remaining empty lines if height is larger than the text lines
    int remainingLines = boxHeight - (formattedText.length() / (boxWidth - 2)) - 2; // Adjusting for top and bottom borders
    for (int i = 0; i < remainingLines; ++i) {
        formattedText += verticalLine + std::string(boxWidth - 2, emptySpace[0]) + verticalLine + '\n';
    }

    // Bottom border
    formattedText += corner + std::string(boxWidth - 2, horizontalLine[0]) + corner + '\n';

    return formattedText;
}




std::string formatTextInBox(std::string speaker, const std::string text, int boxWidth, int boxHeight)
{
    boxHeight = boxHeight - 1;
    std::string corner = "+";
    std::string horizontalLine = "-";
    std::string verticalLine = "|";
    std::string emptySpace = " ";

    std::string formattedText = "";

    // Top border (with speaker name)
    std::string borderLine = corner + std::string(2, horizontalLine[0]) + " " + speaker + " ";
    int remainingWidth = boxWidth - borderLine.length() - 1;
    formattedText += borderLine + std::string(remainingWidth, horizontalLine[0]) + corner + '\n';

    // Top border (without speaker name)
    //formattedText += corner + std::string(boxWidth-2, horizontalLine) + corner + '\n';

    // Content
    std::string::size_type pos = 0;
    while (pos < text.length()) {
        std::string line = text.substr(pos, boxWidth - 2);
        line = verticalLine + std::string(" ") + line;
        line += std::string(boxWidth - line.length() - 1, emptySpace[0]) + verticalLine;
        formattedText += line + '\n';

        pos += line.length() - 3; // -3 to account for verticalLine, space, and the subsequent verticalLine
    }

    // Remaining empty lines if height is larger than the text lines
    int remainingLines = boxHeight - (text.length() / (boxWidth - 2)) - 2; // -2 to account for top and bottom borders
    for (int i = 0; i < remainingLines; ++i) {
        formattedText += verticalLine + std::string(boxWidth - 2, emptySpace[0]) + verticalLine + '\n';
    }

    // Bottom border
    formattedText += corner + std::string(boxWidth-2, horizontalLine[0]) + corner + '\n';

    return formattedText;
}


void confirm_advance()
{
    std::string userInput;
    std::cout << "                           press ENTER to continue >";
    std::getline(std::cin, userInput);

    //if (userInput.empty()) {
        //std::cout << "Confirmed!" << std::endl;
    //} else {
        //std::cout << "Input not confirmed." << std::endl;
    //}
}


int select_answer(std::vector<std::string> answers)
{
   // Question 1
   for (int i = 0; i < answers.size(); ++i) {
       std::cout << i + 1 << ". " << answers[i] << std::endl;
   }

   int choice1;
   std::cout << std::endl;
   std::cout << "Enter your choice (1-" << answers.size() << "): ";

   // Validation loop
   while (true) {
       std::cin >> choice1;

       if (std::cin.fail()) {
           std::cin.clear();
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           std::cout << "Invalid input! Please enter a number." << std::endl;
           continue;
       }

       if (choice1 < 1 || choice1 > answers.size()) {
           std::cout << "Invalid choice! Please enter a valid number." << std::endl;
           continue;
       }

       break;
   }

   std::cout << "You selected: " << answers[choice1 - 1] << std::endl;

   return (choice1 - 1);
}


void activate_selection(
      AllegroFlare::EventEmitter *event_emitter = nullptr,
      AllegroFlare::DialogTree::NodeBank *node_bank = nullptr,
      AllegroFlare::DialogTree::Node *current_dialog_node = nullptr,
      int selection_at_index=0
   )
{
   if (!event_emitter) throw std::runtime_error("event_emitter cannot be nullptr");
   if (!node_bank) throw std::runtime_error("node_bank cannot be nullptr");
   if (!current_dialog_node) throw std::runtime_error("current_dialog_node cannot be nullptr");
   if (!(selection_at_index >= 0 && selection_at_index < current_dialog_node->num_options())) throw std::runtime_error("selection choice must be valid");

   // TODO: perform ellaborate logic here

   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;
   node_option_activator.set_event_emitter(event_emitter);
   node_option_activator.set_node_bank(node_bank);
   node_option_activator.set_currently_active_node(current_dialog_node);
   node_option_activator.set_selection_choice(selection_at_index);

   node_option_activator.activate();
}


void process_dialog_event(
      AllegroFlare::EventEmitter *event_emitter = nullptr,
      ALLEGRO_EVENT_QUEUE *event_queue = nullptr
   )
{
   if (!event_emitter) throw std::runtime_error("event_emitter cannot be nullptr");
   if (!event_queue) throw std::runtime_error("event_queue cannot be nullptr");

   ALLEGRO_EVENT this_event;
   if (!al_get_next_event(event_queue, &this_event))
   {
      throw std::runtime_error("Expecting event");
   }

   switch(this_event.type)
   {
      case ALLEGRO_FLARE_EVENT_DIALOG_OPEN: {

         std::string *data = (std::string *)this_event.user.data1;
         std::string node_name_to_open = *data;
         current_dialog_node = node_bank.find_node_by_name(node_name_to_open);
         current_dialog_node_page_num = 0;
         delete data;
      } break;

      case ALLEGRO_FLARE_EVENT_DIALOG_ADVANCE: {
         // TODO: This logic
         current_dialog_node_page_num++;
         if (current_dialog_node_page_num >= current_dialog_node->num_pages())
         {
            event_emitter->emit_dialog_close_event();
         }
      } break;

      case ALLEGRO_FLARE_EVENT_DIALOG_CLOSE: {
         abort_dialog = true;
      } break;
   }
}


int main(int argc, char **argv)
{
   al_init();

   std::string dialog_filename = "/Users/markoates/Repos/allegro_flare/bin/data/dialogs/dialog.yml";

   ALLEGRO_EVENT_QUEUE *event_queue;
   event_queue = al_create_event_queue();

   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   yaml_loader.load_file(dialog_filename);
   node_bank = yaml_loader.get_node_bank();


   current_dialog_node = node_bank.find_node_by_name("start_node");
   current_dialog_node_page_num = 0;


   while (!abort_dialog)
   {
      clear_terminal();

      std::string node_pages_speaker = current_dialog_node->get_speaker();
      std::vector<std::string> node_pages = current_dialog_node->get_pages();
      std::vector<std::string> node_options_as_text = current_dialog_node->build_options_as_text();

      // output dialog pages
      //for (auto &node_page : node_pages)
      //{
         std::string formatted_dialog_pages = formatTextInBox2(node_pages_speaker, node_pages[current_dialog_node_page_num], 64, 6);
         std::cout << formatted_dialog_pages << std::endl;
      //}

      //bool at_last_page = (current_dialog_node->num_pages() == 0) || (current_dialog_node->num_pages() - 1);
      bool at_last_page = (current_dialog_node_page_num + 1) >= current_dialog_node->num_pages();
      if (at_last_page)
      {
         bool only_one_option = node_options_as_text.size() == 1;
         int selected_answer = 0;
         if (only_one_option)
         {
            confirm_advance();
         }
         else
         {
            selected_answer = select_answer(node_options_as_text);
         }
         activate_selection(&event_emitter, &node_bank, current_dialog_node, selected_answer);
         process_dialog_event(&event_emitter, event_queue);
      }
      else
      {
         confirm_advance();
         event_emitter.emit_dialog_advance_event();
         process_dialog_event(&event_emitter, event_queue);
         // TODO: Prompt user to advance page
      }
   }

   std::cout << "Info: Dialog closed" << std::endl;


   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
   al_uninstall_system();

   return 0;
}



