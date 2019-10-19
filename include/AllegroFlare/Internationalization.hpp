#pragma once



#include <map>
#include <string>
#include <vector>




namespace allegro_flare
{
   class Internationalization
   {
   private:
      Internationalization();
      ~Internationalization();

      static Internationalization *get_instance();
      static Internationalization *instance;

      std::string languages_folder;
      std::string current_language_code;
      std::string current_language_name;
      std::string current_language_filename;
      std::map<std::string, std::string> lines;

   public:
      static bool initialize(std::string folder="data/languages/");
      static bool destruct();
      static bool set_languages_folder(std::string folder="data/languages/");
      static std::string get_languages_folder();
      static bool set_language(std::string language_code);
      static bool load_language_file(std::string as_language_code, std::string as_language_name, std::string filename);
      static std::string get_language();
      static std::string get_language_name();
      static bool t_exists(std::string text_label);
      static std::string t(std::string text_label);
      static std::string tf(std::string text_label, ...);
      static std::vector<std::string> get_language_filenames();
      static std::string find_language_file(std::string language_code);
   };
}



