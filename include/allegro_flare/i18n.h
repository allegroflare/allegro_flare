#ifndef __AF_I18N_HEADER
#define __AF_I18N_HEADER




#include <map>
#include <string>
#include <vector>




class I18n
{
private:
   I18n();
   ~I18n();

   static I18n *get_instance();
   static I18n *instance;

   std::string languages_folder;
   std::string current_language_designator;
   std::string current_language_name;
   std::string current_language_filename;
   std::map<std::string, std::string> lines;

public:
   static bool initialize(std::string folder="data/languages/");
   static bool destruct();
   static bool set_languages_folder(std::string folder="data/languages/");
   static std::string get_languages_folder();
   static bool set_language(std::string language_designator);
   static bool load_language_file(std::string as_language, std::string as_language_name, std::string filename);
   static std::string get_language();
   static std::string get_language_name();
   static bool t_exists(std::string text_label);
   static std::string t(std::string text_label);
   static std::string tf(std::string text_label, ...);
   static std::vector<std::string> get_language_filenames();
   static std::string find_language_file(std::string language_designator);
};




#endif
