


#include <allegro_flare/allegro_flare.h>






int WIDTH = 700;
int PADDING = 20;








std::vector<std::size_t> traverse_and_mark_strings(std::string text)
{
   std::vector<std::size_t> positions;

   for (unsigned i=0; i<text.size(); i++)
   {
      if (text[i] == '\\')
      {
         i++; // skip the next character
         continue;
      }
      else if (text[i] == '\"')
      {
         positions.push_back(i);
      }
   }

   return positions;
}



std::string get_marked_string(std::vector<std::size_t> positions)
{
   std::string str;
   if (positions.empty()) return str;

   str.resize(positions.back(), ' ');
   for (unsigned i=0; i<positions.size(); i++)
   {
      str = str.replace(positions[i], 1, "^");
   }
   return str;
}




std::vector<std::string> extract_arg_tokens(std::string tokens_str)
{
   // remove strings


   // remove strings
   std::vector<std::string> tokens = php::explode(",", tokens_str);
   for (unsigned i=0; i<tokens.size(); i++)
   {
      tokens[i]  = php::trim(tokens[i]);
   }
   return tokens;
}





std::string extract_function_token(std::string line)
{
   line = php::trim(line);
   std::string opening_token = "(";
   std::size_t string_token_start = line.find(opening_token);
   if (string_token_start == std::string::npos) return "";
   return line.substr(0, string_token_start);
}




std::string supplant_strings(std::string line, std::vector<std::size_t> positions)
{
   for (unsigned i=1; i<positions.size(); i+=2)
   {
      std::size_t distance_between_positions = positions[i] - positions[i-1] + 1;
      line = line.replace(positions[i-1], distance_between_positions, std::string(distance_between_positions, '#'));
   }
   return line;
}





std::string extract_args_token(std::string line)
{
      //return_text << "> parse out strings" << "\n";




      std::string opening_token = "(";
      std::string closing_token = ")";


      std::size_t string_token_start = line.find(opening_token);
      while(string_token_start != std::string::npos)
      {
         std::size_t string_token_end = line.rfind(closing_token);
         if (string_token_end == std::string::npos)
         {
            //return_text << ">> ! error, no matching \" found." << "\n";
            //break;
            return "";
         }
         else
         {
            return line.substr(string_token_start+1, string_token_end-string_token_start-1);
            //return return_text.str();
            //std::vector<std::string> tokens = php::explode(",", return_text.str());
            /*
            return_text << ">> string found" << "\n";
            return_text << text << "\n";
            return_text << get_pointing_string(string_token_END, string_token_START) << "\n";
            std::size_t replacement_len = string_token_START-string_token_END-1;
            text = text.replace(string_token_END, replacement_len, std::string(replacement_len, '#'));
            return_text << text << "\n";
            */
         }

         string_token_start = line.find(opening_token);
      }


      return "";

}







class Func
{
private:
   static std::vector<Func *> funcs;
public:
   std::string identifier;
   std::string (*func)(std::vector<std::string> args);
   Func(std::string identifier, std::string (*func)(std::vector<std::string> args))
      : identifier(identifier)
      , func(func)
   {}
   std::string call(std::vector<std::string> args)
   {
      return func(args);
   }
   static bool function_exists(std::string identifier)
   {
      for (unsigned i=0; i<funcs.size(); i++)
         if (funcs[i]->identifier == identifier) return true;
      return false;
   }
};
std::vector<Func *> Func::funcs;







class FuncArgs
{
private:
   int type;
   std::string line;

   std::string function;
   std::vector<std::string> args;

   std::string parse_error;
public:
   FuncArgs(std::string line)
      : type(0)
      , line(line)
      , function("")
      , args()
      , parse_error("")
   {
      parse();
   }
   std::string parse()
   {
      std::stringstream return_text;



      function = extract_function_token(line);
      return_text << "function: " << function << "\n";
      std::string arg_parts_token = extract_args_token(line);
      return_text << "args: " << arg_parts_token << "\n";

      std::vector<std::string> arg_tokens = extract_arg_tokens(arg_parts_token);
      for (unsigned i=0; i<arg_tokens.size(); i++)
      {
         return_text << "arg[" << i << "]: " << arg_tokens[i] << "\n";
      }



      std::vector<std::size_t> positions = traverse_and_mark_strings(line);
      return_text << get_marked_string(positions) << "\n";
      std::string supplanted_string = supplant_strings(line, positions);



      return return_text.str();
   }
   bool parsed_correctly()
   {
      //TODO this function
      return false;
   }
   std::string get_parse_error()
   {
      //TODO this function
      return "";
   }
   std::string get_result()
   {
      //TODO this function
      return "";
   }
};





class Variable
{
public:
   std::string identifier;
   std::string value;
   std::string type;
};






class VirtualMemory
{
public:
   std::vector<Variable *> variables;
   bool exists(std::string const &identifier)
   {
      for (unsigned i=0; i<variables.size(); i++)
         if (variables[i]->identifier == identifier) return true;
      return false;
   }
   std::string get_value(std::string const &identifier)
   {
      for (unsigned i=0; i<variables.size(); i++)
         if (variables[i]->identifier == identifier) return "";
      return ""; // << wtf?  maybe this whole VirtualMemory thing was improved in a different implementation
   }
};





#include <string>


class Project : public UIScreen
{
public:
   class Input : public UITextInput
   {
   public:
      Input(UIWidget *parent)
         : UITextInput(parent, PADDING, PADDING, WIDTH, 40, "function(arg1, \"this is a string\")")
      {
         place.align.x = 0;
         place.align.y = 0;
      }
   };

   class Output : public UITextArea
   {
   public:
      Output(UIWidget *parent)
         : UITextArea(parent, PADDING, PADDING + 80, WIDTH, 400, "")
      {
         place.align.x = 0;
         place.align.y = 0;
      }
      void on_draw() override
      {
         al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::white, 0.1));
         UITextArea::on_draw();
      }
   };

   Input *input;
   Output *output;

   std::string get_pointing_string(std::size_t point1, std::size_t point2)
   {
      std::stringstream ss;
      for (unsigned i=0; i<=std::max(point1, point2); i++)
      {
         if (i == point1) ss << "^";
         else if (i == point2) ss << "^";
         else ss << " ";
      }
      return ss.str();
   }

private:
   static std::vector<std::string> keyword_table;

   void register_keyword(std::string keyword)
   {
      keyword_table.push_back(keyword);
   }

   std::string parse_input(std::string text)
   {
      std::stringstream return_text;
      return_text << text << "\n";



      return_text << "function: " << extract_function_token(text) << "\n";
      std::string arg_parts_token = extract_args_token(text);
      return_text << "args: " << arg_parts_token << "\n";

      std::vector<std::string> arg_tokens = extract_arg_tokens(arg_parts_token);
      for (unsigned i=0; i<arg_tokens.size(); i++)
      {
         return_text << "arg[" << i << "]: " << arg_tokens[i] << "\n";
      }



      return_text << text << "\n";
      std::vector<std::size_t> positions = traverse_and_mark_strings(text);
      return_text << get_marked_string(positions) << "\n";
      return_text << supplant_strings(text, positions) << "\n";




      return return_text.str();
   }

public:
   Project(Display *display)
      : UIScreen(display)
      , input(new Input(this))
      , output(new Output(this))
   {}
   void on_timer() override
   {
      output->set_text(parse_input(input->get_text()));
   }
};









int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(WIDTH + PADDING*2, 600, false);

   Project *proj = new Project(display);

   Framework::run_loop();

   return 0;
}
