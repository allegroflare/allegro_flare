#pragma once



#include <map>
#include <string>
#include <vector>




namespace AllegroFlare
{
   class Internationalization
   {
   private:
      std::string languages_folder;
      std::string current_language_code;
      std::string current_language_name;
      std::string current_language_filename;
      std::map<std::string, std::string> lines;

   public:
      Internationalization(std::string folder="data/languages/");
      ~Internationalization();

      bool set_languages_folder(std::string folder="data/languages/");
      std::string get_languages_folder();
      bool set_language(std::string language_code);
      bool load_language_file(std::string as_language_code, std::string as_language_name, std::string filename);
      std::string get_language();
      std::string get_language_name();
      bool t_exists(std::string text_label);
      std::string t(std::string text_label);
      std::string tf(std::string text_label, ...);
      std::vector<std::string> get_language_filenames();
      std::string find_language_file(std::string language_code);
   };
}



