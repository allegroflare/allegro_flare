#include <allegro5/allegro.h>
#include <iostream>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>
#include <AllegroFlare/EventNames.hpp>


bool abort_dialog = false;
AllegroFlare::DialogTree::Node *current_dialog_node = nullptr;
int current_dialog_node_page_num = 0;
AllegroFlare::DialogTree::NodeBank node_bank;


void clear_terminal()
{
    std::cout << "\033[2J\033[1;1H";
}



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



